/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:31:12 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/30 15:03:03 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search_quot(char *input)
{
	int		x;
	char	c;
	int		i;

	x = 0;
	i = 0;
	while (input && input[x])
	{
		if (input[x] == '\'' || input[x] == '"')
		{
			c = input[x];
			i++;
			x++;
			while (input[x] && input[x] != c)
				x++;
			if (input[x])
				i++;
		}
		if (input[x])
			x++;
	}
	if (i % 2 != 0)
		return (0);
	return (1);
}

void	setup_signals(void)
{
	g_signal_recu = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

int	shell_loop(t_node *list, t_data *data, t_env **env)
{
	char	*input;
	int		status;

	while (1)
	{
		input = ft_read_input(data);
		if (!input)
			break ;
		if (handle_empty_input(input, data))
			continue ;
		status = ft_process_command(input, list, data, *env);
		if (status == 2)
			break ;
		if (status == 1)
			continue ;
	}
	ft_free_end(list, env);
	return (data->exit_code);
}
