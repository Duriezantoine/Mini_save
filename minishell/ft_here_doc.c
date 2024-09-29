/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:32:48 by aduriez           #+#    #+#             */
/*   Updated: 2024/09/28 18:55:53 by aduriez          ###   ########.fr       */
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

void ft_here_doc(t_data *data, t_node *list, t_env **env, char *limiteur) // Il vat falloir mettre en place l'environnement
{
	printf("\nLimiteur = %s\n", limiteur);
	char *write_here_do;
	int ret;
	int test;
	struct sigaction action;
	struct termios term_attr;
	// void(data);
	(void)env;
	// void(list);
	ft_init_signaux(&action, &write_here_do);
	tcgetattr(STDIN_FILENO, &term_attr);
	ret = read(0, write_here_do, 1023);
	write_here_do[ret] = '\n';
	while (1)
	{
		printf("\nsignal recus = |%d|\n", signal_recu);
		test = strcmp(write_here_do, limiteur);
		if (ret == 0)
		{
			printf("AAA");
			break;
		}
		if (test - 10 == 0)
		{
			printf("BBB");
			break;
		}
		if (signal_recu == -2)
		{
			printf("CCC");
			shell_loop(list, &data, &list->env);
			break;
		}
		ret = read(0, write_here_do, 1023);
		write_here_do[ret] = '\0';
	}
}
