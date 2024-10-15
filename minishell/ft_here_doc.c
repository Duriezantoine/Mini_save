/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:32:48 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/15 10:36:31 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
volatile sig_atomic_t signal_recu = 0;

void ft_init_signaux(struct sigaction *action, char **write_here_do)
{
	signal_recu = 0;
	// here_doc = 0;
	action->sa_handler = ft_manager_sig;
	sigemptyset(&action->sa_mask);
	action->sa_flags = 0;
	sigaction(SIGINT, action, NULL);
	sigaction(SIGTSTP, action, NULL); // Ajoutez SIGTSTP si vous voulez gérer ce signal aussi
	*write_here_do = malloc(sizeof(char) * 1023);
	// Ne pas oublier de mettre une conditions pour proteger le malloc
}

void ft_manager_sig(int sig)
{
	if (sig == SIGINT)
	{
		// printf("\nttt\n");
		signal_recu = -2;
	}
	else if (sig == SIGTSTP)
	{
		// printf("Je viens de contrôler z\n");
	}
	else
	{
		// printf("est ce ");
		signal_recu = sig;
	}
	return;
}
char *create_file_name(char *temp_file_name, t_data *data, char *write_here_do)
{
	temp_file_name = malloc(256);
	if (temp_file_name == NULL) 
	{
		perror("malloc");
		free(write_here_do);
		exit(EXIT_FAILURE);
	}
	ft_strcpy(temp_file_name, "bbw");
	ft_strcat(temp_file_name, data->count);
	return (temp_file_name);

}

int 	open_file_here_doc(int tmp_fd, char *temp_file_name, char *write_here_do)
{
    tmp_fd = open(temp_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (tmp_fd == -1) {
        perror("open");
        free(temp_file_name);
        free(write_here_do);
        exit(EXIT_FAILURE);
    }
	return (tmp_fd);
}
t_here_doc_data init_here_doc_data() 
{
    t_here_doc_data data;
    data.write_here_do = NULL;
    data.ret = 0;
    data.test = 0;
    data.temp_file_name = NULL;
    data.tmp_fd = 0;
    return data;
}

void free_here_doc_data(t_here_doc_data *data)
{
    if (data->write_here_do) {
        free(data->write_here_do);
    }
    if (data->temp_file_name) {
        free(data->temp_file_name);
    }
}

void setup_here_doc_files(t_here_doc_data *here_doc_data, t_data *data, t_node *list, char *write_here_do) {
    if (list->cmd->cmd != 0)
    {
        here_doc_data->temp_file_name = create_file_name(here_doc_data->temp_file_name, data, write_here_do);
        here_doc_data->tmp_fd = open_file_here_doc(here_doc_data->tmp_fd, here_doc_data->temp_file_name, write_here_do);
    }
}

void initialize_here_doc_input(t_here_doc_data *here_doc_data) 
{
    ft_init_signaux(&here_doc_data->action, &here_doc_data->write_here_do);
    tcgetattr(STDIN_FILENO, &here_doc_data->term_attr);
    here_doc_data->ret = read(0, here_doc_data->write_here_do, 1023);
    here_doc_data->write_here_do[here_doc_data->ret] = '\n';
}

char *handle_write_error(t_here_doc_data *here_doc_data)
{
    if (write(here_doc_data->tmp_fd, here_doc_data->write_here_do, here_doc_data->ret) == -1) {
        perror("write");
        free(here_doc_data->write_here_do);
        return "erreur";
    }
    return NULL;
}

void read_input(t_here_doc_data *here_doc_data)
{
    here_doc_data->ret = read(0, here_doc_data->write_here_do, 1023);
    here_doc_data->write_here_do[here_doc_data->ret] = '\0';
}

char *close_and_return_temp_file(t_here_doc_data *here_doc_data)
{
    close(here_doc_data->tmp_fd);
    if (here_doc_data->write_here_do) {
        free(here_doc_data->write_here_do);
    }
    return here_doc_data->temp_file_name;//Pourquoi je retourne le nom
}

void handle_signal_recu(int signal_recu, t_node *list, t_data *data, t_here_doc_data *here_doc_data)
{
    (void)here_doc_data;

	if (signal_recu == -2) {
        free_here_doc_data(here_doc_data);//Je ne comprends pas apparement il se free deja
        shell_loop(list, &data, &list->env);
    }
}

char *ft_here_doc(t_data *data, t_node *list, char *limiteur)
{
    t_here_doc_data here_doc_data = init_here_doc_data();
    //iL manque free
    setup_here_doc_files(&here_doc_data, data, list, here_doc_data.write_here_do);
    initialize_here_doc_input(&here_doc_data);
    while (1) 
	{
        here_doc_data.test = strncmp(here_doc_data.write_here_do, limiteur, ft_strlen(limiteur));
        if (here_doc_data.ret == 0 || here_doc_data.test == 0)
            break;
        handle_signal_recu(signal_recu, list, data, &here_doc_data);
        if (signal_recu == -2) 
            break;
       if (list->cmd->cmd != 0) 
	   	{
            char *error = handle_write_error(&here_doc_data);
            if (error) 
                return error;
        }
        //printf("write=|%s|demande=|%s|test_delimiteur |%d|",here_doc_data.write_here_do, limiteur, here_doc_data.test );
        read_input(&here_doc_data);
    }
    if (list->cmd->cmd != 0)
        return close_and_return_temp_file(&here_doc_data);
    free_here_doc_data(&here_doc_data);
    return "No_tmp_name";
}

