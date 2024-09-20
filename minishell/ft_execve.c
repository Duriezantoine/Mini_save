/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:15:40 by aduriez           #+#    #+#             */
/*   Updated: 2024/06/29 17:26:53 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Verifier si il est possible d'utilise ca

static volatile sig_atomic_t	signal_recu = 0;

void	putstr_fd(char *s, int fd)
{
	int	count;

	count = 0;
	if (!s)
		return ;
	while (s[count] != '\0')
	{
		write(fd, &s[count], 1);
		count++;
	}
}

void	ft_fork_one(t_excev *base, char *envp[], t_data *data)
{
	int	fd;

	base->cmd++;
	fd = fork();
	base->pipe_filled = 1;
	if (fd < 0)
	{
		return ;
	}
	if (fd == 0)
	{
		if (base->nbr_pipe > 0 && data->outfile == 0)
		{
			dup2(base->fd_origin[1], STDOUT_FILENO);
			close(base->fd_origin[1]);
		}
		else if (data->outfile != 0)
		{
			putstr_fd("\nJe avec outfile arg1 \n", 2);
			dup2(data->outfile, STDOUT_FILENO);
			close(data->outfile);
		}
		if (base->open_file != STDIN_FILENO)
		{
			putstr_fd("\nJe passe ss outfile arg1 \n", 2);
			dup2(base->open_file, STDIN_FILENO);
			close(base->open_file);
		}
		// close(base->fd_origin[0]);
		execve(data->path, data->arg, envp);
		printf("La commande ne marche pas ");
		exit(EXIT_FAILURE);
	}
	if (data->outfile != 0)
	{
		close(data->outfile);
	}
	if (base->nbr_pipe > 0)
	{
		close(base->fd_origin[1]);
	}
	if (base->open_file != STDIN_FILENO)
	{
		close(base->open_file);
	}
	base->nbr_pipe--;
	// waitpid(0, &base.data_exit, 0);
}

void	ft_init_base(t_excev *base)
{
	base->open_file = STDIN_FILENO;
	base->open_outfile = STDOUT_FILENO;
	base->pipe_filled = 0;
	base->cmd = 0;
	base->infile_nbr = 0;
	// Il faut verifier la redirection
	// dup(base.all_pipe[base.init_pipe]);
	// base->save_fd = dup(0);
	// base->save_fd_origin = dup(1);
}

void	ft_fork_arg_pipe(t_excev *base, char *envp[], t_data *data)
{
	int	pfd;

	putstr_fd("\nft_frook_pipearg\n", 2);
	// while (base->arg[base->count_arg].verif == 0)
	// 	base->count_arg++;
	pfd = fork();
	if (pfd < 0)
	{
		printf("Il y a une erreur");
		return ;
	}
	if (pfd == 0)
	{
		dup2(base->fd_origin[0], STDIN_FILENO);
		close(base->fd_origin[0]);
		if (base->nbr_pipe > 0 && data->outfile == 0)
		{
			putstr_fd("\nJe passe SS OUTFILE\n", 2);
			dup2(base->fd[1], STDOUT_FILENO);
			close(base->fd[1]);
			close(base->fd[0]);
		}
		else if (data->outfile != 0)
		{
			putstr_fd("\nJEPASSEAVECOUTFILE\n", 2);
			dup2(data->outfile, STDOUT_FILENO);
			close(data->outfile);
		}
		execve(data->path, data->arg, envp);
		printf("Ca ne marche pas connard \n");
	}
	// Il va falloir faire une sortie d'erreur
	close(base->fd_origin[0]);
	if (data->outfile != 0)
	{
		close(data->outfile);
	}
	if (base->nbr_pipe > 0)
	{
		base->fd_origin[0] = base->fd[0];
		base->fd_origin[1] = base->fd[1];
		close(base->fd[1]);
	}
	base->nbr_pipe--;
	// waitpid(0, base.data_exit, 0);
	// Je viens de le retirer a verifier si on le retire
}
int	ft_check_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (data)
	{
		if (data->token == PIPE)
			i++;
		data = data->next;
	}
	return (i);
}
void	ft_init_open_file(t_excev *base, t_data *data)
{
	// printf("|DATAVALUE|%s|", data->value);
	base->open_file = open(data->value, O_RDONLY);
	base->infile_nbr++;
	if (base->open_file < 0)
	{
		printf("IL y a un probleme ca ne marche pas \n");
	}
	printf("\nFT|OPENFILE|\n");
}

void	ft_manager_sig(int sig)
{
	if (sig == SIGINT)
	{
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
	return ;
}
void	ft_init_signaux(struct sigaction *action, char **write_here_do)
{
	signal_recu = 0;
	// here_doc = 0;
	action->sa_handler = ft_manager_sig;
	sigemptyset(&action->sa_mask);
	action->sa_flags = 0;
	sigaction(SIGINT, action, NULL);
	*write_here_do = malloc(sizeof(char) * 1023);
	// Ne pas oublier de mettre une conditions pour proteger le malloc
}
void	ft_here_doc(char *value, t_data *data, char *envp[])
{
	char				*write_here_do;
	int					ret;
	int					test;
	struct sigaction	action;
	struct termios		term_attr;

	// char				write_here_do[1024];
	ft_init_signaux(&action, &write_here_do);
	tcgetattr(STDIN_FILENO, &term_attr);
	ret = read(0, write_here_do, 1023);
	write_here_do[ret] = '\n';
	while (1)
	{
		test = strcmp(write_here_do, value);
		if (ret == 0)
		{
			printf("ICIC");
			break ;
		}
		if (test - 10 == 0)
			break ;
		if (signal_recu == -2)
		{
			// free(envp);
			shell_loop(&data, envp);
			break ;
		}
		ret = read(0, write_here_do, 1023);
		write_here_do[ret] = '\0';
	}
}

void	ft_display_echo_arg_n(t_data *data)
{
	int	i;

	printf("\n");
	i = 1;
	while (data->arg[i])
		printf("%s", data->arg[i++]);
}

void	
ft_display_echo(t_data *data)
{
	int	i;

	i = 0;
	printf("\n");
	while (data->arg[i])
	{
		printf("%s", data->arg[i++]);
	}
	printf("\n");
}
char	*ft_get_current_dir(void)
{
	char	*cwd;
	size_t	size;

	size = 1024;
	cwd = malloc(size);
	if (cwd == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	if (getcwd(cwd, size) == NULL)
	{
		free(cwd);
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}

int	ft_directory_exist_not_path(char *save)
{
	DIR		*dir;
	char	*path;
	char	*new_path;

	// Il faut verfifier si on acces
	// Il faut ensuite verifier les frees
	path = ft_get_current_dir();
	dir = opendir(save);
	printf("\n|Directory_exist_not_path|\n");
	if (dir == NULL)
	{
		printf("|PATH_NOT_EXIST|\n");
		return (-1);
	}
	printf("|PATH_EXIST|\n");
	new_path = ft_strjoin(path, "/");
	new_path = ft_strjoin(new_path, save);
	if (chdir(new_path) == -1)
	{
		closedir(dir);
		printf("\n|CHDIRNOTACCES|\n");
		return (-1);
	}
	printf("|CHDORACCES|\n");
	closedir(dir);
	return (1);
}
int	ft_search_unset(char **copy_envp, char *search)
{
	int	i;

	i = 0;
	// Verrfifier que la variables existent dans envp
	while (copy_envp[i])
	{
		if (strstr(copy_envp[i], search) != NULL)
		{
			printf("|SEARCH_UNSET|");
			return (1);
		}
		i++;
	}
	return (0);
}
char	**new_tab_envp(char *copy_envp[], char *include_envp)
{
	int		i;
	char	**new_envp;

	// Compter tous les éléments du simple tableau de envp
	i = 0;
	while (copy_envp[i])
		i++;
	// Allouer de la mémoire pour le nouveau tableau de envp
	new_envp = malloc(sizeof(char *) * (i + 1 * 100));
	if (!new_envp)
		return (NULL);
	// Copier tous les éléments de la copy_envp
	i = 0;
	while (copy_envp[i])
	{
		new_envp[i] = copy_envp[i];
		i++;
	}
	// Allouer de la mémoire pour la chaîne de caractères include_envp
	new_envp[i] = malloc(sizeof(char) * (strlen(include_envp) + 1));
	if (!new_envp[i])
	{
		// Gérer l'erreur d'allocation mémoire
		free(new_envp);
		return (NULL);
	}
	// Copier la chaîne de caractères include_envp dans le nouveau tableau de envp
	strcpy(new_envp[i], include_envp);
	// Ajouter un élément NULL à la fin du nouveau tableau de envp
	new_envp[i + 1] = NULL;
	printf("\nJe suis la place dans le tableau inserer %d\n", i);
	// free(copy_envp);
	return (new_envp);
}
char **ft_reaplace_var(char**copy_envp, char *search)
{
	int i;
	int count ;
	int count_search ;
	i = 0;
	printf("\n|ft_replace_var|\n");
	while(copy_envp[i])
	{
		count =0;
		count_search  = 0 ;
		if(copy_envp[i][count] == search[count_search])
		{
			while(copy_envp[i][count]==search[count_search])
			{
				count++;
				count_search++;
				if(search[count_search] == '=')
				{
					//IL faut alors commence4r a remplacer la variable ici
					while(search[count_search] != '\0')
					{
						copy_envp[i][count] = search[count_search];
						count++;
						count_search++;
					}
					copy_envp[i][count] = '\0';
					printf("\n|VARIABLEEXIST|\n" );
					return(copy_envp);
				}
			}
		}
		i++;
	}
	return(copy_envp);

}
int	 ft_search_varible(char **copy_envp, char *search)
{
	int i;
	int count = 0;
	int count_search = 0;
	i = 0;
	while(copy_envp[i])
	{
		count =0;
		count_search  = 0 ;
		if(copy_envp[i][count] == search[count_search])
		{
			while(copy_envp[i][count]==search[count_search])
			{
				count++;
				count_search++;
				if(search[count_search] == '=')
				{
					//IL faut alors commence4r a remplacer la variable ici
					return(1);
					printf("\n|VARIABLEEXIST|\n" );
				}
			}
		}
		i++;
	}
	return(0);
}
char	**ft_display_envp_insert(t_data *data, char *copy_envp[])
{
	char	**tmp_env;

	tmp_env = NULL;
	printf("Je suis rentre dans|FT_DISPLAY_ENVP_INSERT|");
	// Il faut alors faire une conditions si celui d'apres est
	printf("\n\n|%s|\n\n", data->value);
	if (data->value != NULL)
	{
		printf("|NEW_VARIRABE EXPORT|VALUE|%s|", data->value);
		//Il faut commencer a verifier que la variable exist_ou_non
		if(ft_search_varible(copy_envp, data->value)==0)
			tmp_env = new_tab_envp(copy_envp, data->value);
		else
		{
			tmp_env = ft_reaplace_var(copy_envp, data->value);
			return(tmp_env);
		}
		// free(copy_envp);
		// IL  faut alors commencer a la mettre dans l'environnement a la suite dans la copy
	}
	return (tmp_env);
}
void	**ft_delete_unset(char **copy_envp, char *search)
{
	int	i;

	(void)search;
	i = 0;
	printf("\n|DELETEUNSET|\n");
	while (copy_envp[i])
	{
		printf("\n|%s|", copy_envp[i]);
		if (strncmp(copy_envp[i], search, strlen(search)) == 0)
		{
			printf("\n|DELEATE|\n%s\n|\n", copy_envp[i]);
			copy_envp[i] = NULL;
		}
		i++;
	}
	return (NULL);
}
void	sort_envp(char **copy_envp)
{
	char	*tmp;
	int		num_envp;

	int i, j;
	num_envp = 0;
	// Calculer le nombre d'éléments dans copy_envp
	while (copy_envp[num_envp] != NULL)
		num_envp++;
	// Tri à bulles (bubble sort) basé sur strcmp
	for (i = 0; i < num_envp - 1; i++)
	{
		for (j = 0; j < num_envp - i - 1; j++)
		{
			if (strcmp(copy_envp[j], copy_envp[j + 1]) > 0)
			{
				// Échanger les pointeurs
				tmp = copy_envp[j];
				copy_envp[j] = copy_envp[j + 1];
				copy_envp[j + 1] = tmp;
			}
		}
	}
}
void	ft_display_envp(char *copy_envp[])
{
	int	i;

	i = 0;
	sort_envp(copy_envp);
	printf("\n 1er|%s|\n", copy_envp[0]);
	while (copy_envp[i])
	{
		printf("declare -x %s\n", copy_envp[i]);
		i++;
	}
}
void	ft_verfife_outifile(t_data *data)
{
	int		i;
	char	*tmp;
	t_data	*full_tmp;

	printf("\nFTVERIF\n");
	i = 0;
	while (data)
	{
		if (data->token == CMD)
			full_tmp = data;
		if (data->token == PIPE)
			full_tmp = data;
		if (data->token == OUTFILE)
		{
			tmp = data->value;
			full_tmp->outfile = open(tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (data->outfile < 0)
			{
				printf("Erreur ca ne marche pas OUTFILE\n");
			}
			data = full_tmp;
			data = data->next->next;
			i++;
		}
		data = data->next;
	}
	// printf("NBR_INFI_INCLUDE|%d|", i);
	return ;
}
char 	*ft_deleate_str(char *str, char *deleate)
{
	char *result;
	int i;
	int b ;

	b = 0;
	i  = ft_strlen(deleate);
	result = malloc(sizeof(char*) * (ft_strlen(str) - i + 1));
	//Il vat falloir proteger le malloc
	while(str[i])
	{
		result[b] = str[i];
		i++;
		b++;
	}
	result[b] ='\0';
	printf("\nJe suis le resulta |%s|\n", result);
	return(result);

}

void 	ft_search_dollar(char *search, char *envp[])
{
	printf("\n|FT_search_dollar|\n");
	int i;
	i = 0;
	char *tmp;
	char *str;

	tmp = ft_strjoin(search, "=");
	(void)search;
	printf("\n|SEARCH=|%s|\n", tmp);
	while(envp[i] != NULL)
	{
		if (strncmp(envp[i], tmp, strlen(tmp)) == 0)
			{
				str = ft_deleate_str(envp[i], tmp);
				printf("\n\n|J'ai trouver la valeur qui corresponds|%s||\n", str);
				// free(tmp);
				return;
			}

		i++;
	}
	free(tmp);
}

char	**ft_execve(t_data *data, char *envp[])
{
	t_excev base;
	t_data *tmp;
	t_data *full_tmp;
	char **copy_envp;

	pid_t pidd;

	base.data_exit = 0;
	base.init_fd = 0;
	base.init_pipe = 0;
	copy_envp = envp;

	ft_init_base(&base);
	base.nbr_pipe = ft_check_pipe(data);
	if (pipe(base.fd_origin) == -1)
		printf("ERROR");
	(void)envp;
	while (data != NULL)
	{
		// printf("|datavalue|%s|", data->value);
		if (data->token == L_CHEV)
		{
			data = data->next;
			ft_init_open_file(&base, data);
		}
		if (data->token == CMD)
		{
			tmp = data;
			full_tmp = data;
			if (data->next != NULL)
				data = data->next;
			while (data != NULL && data->token == L_CHEV)
			{
				if (data->next->token == INFILE)
				{
					data = data->next;
					ft_init_open_file(&base, data);
				}
			}
			full_tmp = data;
			data = tmp;
			printf("\nFORKONE\n");
			ft_fork_one(&base, copy_envp, data);
			data = full_tmp;
		}
		if (data->token == PIPE)
		{
			if (pipe(base.fd) == -1)
				printf("ERROR");
			ft_fork_arg_pipe(&base, copy_envp, data);
		}
		if (data->token == OUTFILE)
		{
			printf("\n|OUTFILE|\n");
		}
		if (data->token == D_L_CHEV || data->token == HERE_DOC)
		{
			printf("\nHR\n");
			data = data->next;
			// ft_display_echo(data);
			ft_here_doc(data->value, data, copy_envp);
		}
		if (data->token == ECHO_CMD)
		{
			printf("\n|ECHOCMD|\n");
			base.pipe_filled = 0;
			if (ft_strcmp(data->arg[0], "-n") != 0)
				ft_display_echo_arg_n(data);
			else
				ft_display_echo(data);
		}
		if (data->token == CD)
		{
			if (ft_strcmp(data->value, "echo") != 0)
			{
				printf("\n|Data_value|%s|", data->value);
				if(ft_strcmp(data->value, "$") != 0)
				{
						printf("\nCa marche  \n");

					if(data->next != NULL)
					{
						data = data->next;
						data = data->next;

						ft_search_dollar(data->value, envp);
						printf("\nXXXX\n");
					}
					else
						printf("\n$_is_not_present\n");

				}
				else
				{
					printf("\n|endehor|\n");
					ft_display_echo(data);//Mis
				}
				//IL faut alors commencer a deplacer les nouvelles pour les mettre  dans la data.
			}	
			else
			{
				printf("\nJe passe la \n");
				data = data->next;
				ft_directory_exist_not_path(data->value);
			}
			printf("|Je suis a la fin de la fonction echo ||");
		}
		if(data->token == EXPORT)
		{
			printf("\nEmpty\n");
		}
		if (data->token == UNSET)
		{
			// IL permet d'enlever une variable la copy_envp
			printf("\n|UNSET|\n");
			data = data->next;
			printf("\n|DATAVALUE UNSET|%s|\n", data->value);
			if (ft_search_unset(copy_envp, data->value) == 1)
			{
				printf("\n|itsok|EXIST|\n");
				ft_delete_unset(copy_envp, data->value);
				// ft_display_envp(copy_envp);
			}
			else
			{
				// Il faut faire un exitcode
				printf("\n|itsnotok|NOTEXIST|\n");
			}
		}
		data = data->next;
	}
	// close(base.fd_origin[0]);
	// close(base.fd_origin[1]);
	// close(base.fd[0]);
	// close(base.fd[1]);

	// if (b > 0)
	// int status;
	while ((pidd = waitpid(-1, NULL, 0)) > 0)
	{
		        printf("Le premier argument est \n");

	}
	return (envp);
}