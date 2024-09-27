/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:32:48 by aduriez           #+#    #+#             */
/*   Updated: 2024/09/27 10:37:41 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
static volatile sig_atomic_t	signal_recu = 0;


void	ft_here_doc(t_data *data, t_node *list , char **env, char *limiteur)//Il vat falloir mettre en place l'environnement
{
	char				*write_here_do;
	int					ret;
	int					test;
	struct sigaction	action;
	struct termios		term_attr;
	// void(data);
	// void(envp);
	// void(list);
	ft_init_signaux(&action, &write_here_do);
	tcgetattr(STDIN_FILENO, &term_attr);
	ret = read(0, write_here_do, 1023);
	write_here_do[ret] = '\n';
	while (1)
	{
		test = strcmp(write_here_do, limiteur);
		if (ret == 0)
		{
			break ;
		}
		if (test - 10 == 0)
			break ;
		if (signal_recu == -2)
		{
			shell_loop(list, &data, env);
			break ;
		}
		ret = read(0, write_here_do, 1023);
		write_here_do[ret] = '\0';
	}
}






