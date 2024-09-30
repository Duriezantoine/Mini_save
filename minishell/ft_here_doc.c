/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:32:48 by aduriez           #+#    #+#             */
/*   Updated: 2024/09/30 11:06:02 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static volatile sig_atomic_t signal_recu = 0;

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
		printf("\nttt\n");
		signal_recu = -2;
	}
	else if (sig == SIGTSTP)
	{
		printf("Je viens de contrôler z\n");
	}
	else
	{
		printf("est ce ");
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
char *ft_here_doc(t_data *data, t_node *list, t_env **env, char *limiteur) // Il vat falloir mettre en place l'environnement
{
	// printf("\nLimiteur = %s\n", limiteur);
	char *write_here_do = NULL;
	int ret;
	int test;
	struct sigaction action;
	struct termios term_attr;
	char *temp_file_name = NULL;
	int tmp_fd = 0;
	// void(data);
	(void)env;
	if(list->cmd->cmd != 0)
	{
		temp_file_name = create_file_name(temp_file_name, data, write_here_do);//Creation du nom du fichier special pour les pipes et ecrase autre here_doc
		tmp_fd = open_file_here_doc(tmp_fd, temp_file_name, write_here_do);//Il faut ouvrir  le fichier temporaire
		// printf("Nom du fichier temporaire|%s|", temp_file_name);
	}
	// void(list);
	ft_init_signaux(&action, &write_here_do);
	tcgetattr(STDIN_FILENO, &term_attr);
	ret = read(0, write_here_do, 1023);
	write_here_do[ret] = '\n';
	while (1)
	{
		// printf("\nsignal recus = |%d|\n", signal_recu);
		test = strcmp(write_here_do, limiteur);
		if (ret == 0)
		{
			// printf("AAA");
			break;
		}
		if (test - 10 == 0)
		{
			// printf("BBB");
			break;
		}
		if (signal_recu == -2)
		{
			// printf("CCC");
			shell_loop(list, &data, &list->env);
			break;
		}
        if (list->cmd->cmd != 0)
        {
            // Écrire dans le fichier temporaire
            // printf("Je dois ecrire dans le fichier temporaire ici");
            if (write(tmp_fd, write_here_do, ret) == -1) {
                perror("write");
                free(write_here_do);
                return("erreur");
            }
        }

			ret = read(0, write_here_do, 1023);
			write_here_do[ret] = '\0';
	}
	if (list->cmd->cmd != 0)
    {
        close(tmp_fd); // Fermer le fichier temporaire après avoir terminé l'écriture
    }
	if (list->cmd->cmd != 0)
    {
		return(temp_file_name);
	}
	return("No_tmp_name");
}
