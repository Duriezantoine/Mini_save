/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:32:48 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/23 18:19:04 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
volatile sig_atomic_t signal_recu = 0;

char *create_file_name(char *temp_file_name, t_data *data, char *write_here_do)
{
	temp_file_name = malloc(256);
	if (temp_file_name == NULL) 
	{
		perror("malloc");
		free(write_here_do);
		exit(EXIT_FAILURE);
	}
	ft_strcpy(temp_file_name, "/tmp/heredoc");
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
    data.test = 0;
    data.ret = 1;
    data.temp_file_name = NULL;
    data.tmp_fd = 0;
    return (data);
}

void setup_here_doc_files(t_here_doc_data *here_doc_data, t_data *data, t_node *list, char *write_here_do) {
    if (list->cmd->cmd != 0)
    {
        here_doc_data->temp_file_name = create_file_name(here_doc_data->temp_file_name, data, write_here_do);
        here_doc_data->tmp_fd = open_file_here_doc(here_doc_data->tmp_fd, here_doc_data->temp_file_name, write_here_do);
    }
}

int handle_write_error(t_here_doc_data *here_doc_data)
{
    if (write(here_doc_data->tmp_fd, here_doc_data->write_here_do, here_doc_data->ret) == -1) {
        perror("write");
        free(here_doc_data->write_here_do);
        return 1;
    }
    return 0;
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
    return here_doc_data->temp_file_name;
}

t_here_doc_data *get_hd_data(void)
{
    static t_here_doc_data  data;

    return (&data);
}

void    heredoc_handle_sig(int signal)
{
    t_here_doc_data *here_doc_data;

    if (signal == SIGINT)
    {
        here_doc_data = get_hd_data();
        free(here_doc_data->temp_file_name);
        free(here_doc_data->write_here_do);
        ft_free_return_loop(here_doc_data->list);
        ft_free_end(here_doc_data->list, &(here_doc_data->list->env));
        ft_putstr_fd("\n", 2);
        exit(130);
    }
}

int	ft_putchar_fd(char c, int fd)
{
	int	tmp;

	tmp = write(fd, &c, 1);
	return (tmp);
}
int	ft_putendl_fd(char *str, int fd)
{
	int	ret;

	ret = ft_putstr_fd(str, fd);
	ret += ft_putchar_fd('\n', fd);
	return (ret);
}

static void	handle_end_of_file(char *limiteur)
{
	ft_putstr_fd("bash: warning: here-document at line 1 "
		"delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiteur, 2);
	ft_putendl_fd("\')", 2);
}

static void	clean_and_exit(t_here_doc_data *data, int exit_code)
{
	free(data->temp_file_name);
	free(data->write_here_do);
	ft_free_return_loop(data->list);
	ft_free_end(data->list, &(data->list->env));
    close(data->tmp_fd);
	exit(exit_code);
}

static int	check_heredoc_end(t_here_doc_data *data, char *limiteur)
{
	data->test = strncmp(data->write_here_do, limiteur,
		ft_strlen(limiteur));
	if (data->ret == 0 || data->test == 0)
	{
		if (data->ret == 0)
			handle_end_of_file(limiteur);
		return (1);
	}
	return (0);
}

static void	process_command(t_here_doc_data *data)
{
	int	error;

	if (data->list->cmd->cmd != 0)
	{
		error = handle_write_error(data);
		if (error)
			clean_and_exit(data, error);
	}
}

void	heredoc_process(t_here_doc_data here_doc_data, char *limiteur)
{
	signal(SIGQUIT, heredoc_handle_sig);
	signal(SIGINT, heredoc_handle_sig);
	here_doc_data.write_here_do = ft_calloc(sizeof(char), 1023);
	*(get_hd_data()) = here_doc_data;
	while (1)
	{
		if (check_heredoc_end(&here_doc_data, limiteur))
			break ;
		process_command(&here_doc_data);
		read_input(&here_doc_data);
	}
	clean_and_exit(&here_doc_data, 0);
}

char *ft_here_doc(t_data *data, t_node *list, char *limiteur, t_node *base_node)
{
    int heredoc_pid;
    t_here_doc_data here_doc_data = init_here_doc_data();
    here_doc_data.list = base_node;
    int status;
    
    setup_here_doc_files(&here_doc_data, data, list, here_doc_data.write_here_do);
    heredoc_pid = fork(); // todo protection
    if (heredoc_pid == 0)
    {
        heredoc_process(here_doc_data, limiteur);
        exit(1);
    }
    else
    {
        signal(SIGQUIT, handler_void);
        signal(SIGINT, handler_void);
        if (waitpid(heredoc_pid, &status, 0) == -1)
        {
            perror("waitpid");
            free(here_doc_data.temp_file_name);
            return (NULL);
        }
        if (WEXITSTATUS(status) == 130 || WEXITSTATUS(status) == 1)
        {
            free(here_doc_data.temp_file_name);
            return NULL;
        }
        //iL manque free
        // initialize_here_doc_input(&here_doc_data);
        if (list->cmd->cmd != 0)
        {
            return close_and_return_temp_file(&here_doc_data);
        }
       // free_here_doc_data(&here_doc_data);
        return "No_tmp_name";
    }
}

