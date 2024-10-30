/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:10:29 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 15:08:17 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_recu = sig;
		ft_putstr_fd("^C\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	ft_search_inputs(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
			{
				if (!ft_white_space(str[i++]))
					return (1);
			}
			if (str[i] == c)
				i++;
		}
		else if (!ft_white_space(str[i]))
			return (1);
		if (str[i] != 0)
			i++;
	}
	return (0);
}

int	ft_orga_verif_input(char *str)
{
	char	*tmp;

	tmp = ft_verif_input(str);
	if (ft_verif_tokens(tmp) == 1)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

void	ft_free_return_loop(t_node *list)
{
	free_node(list->next);
	list->next = NULL;
	ft_free_arg(list->arg);
	ft_free_cmd(list->cmd);
	list->arg = NULL;
	list->cmd = NULL;
	list->pipe[0] = -1;
}
