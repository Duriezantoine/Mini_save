/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:37:56 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 16:31:09 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_empty_input(char *input, t_data *data)
{
	if (ft_search_quot(input) == 0)
	{
		ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
		free(input);
		return (1);
	}
	if (ft_search_inputs(input) == 0)
	{
		free(input);
		return (1);
	}
	if (ft_orga_verif_input(input))
	{
		add_history(input);
		free(input);
		data->exit_code = 2;
		return (1);
	}
	return (0);
}

int	process_input(char *input, t_node *list, t_data *data, t_env *env)
{
	if (ft_strlen(input) == 0 || ft_white_spaces(input) == 0)
	{
		free(input);
		return (1);
	}
	if (ft_parsing(list, data, input, env) == 1)
	{
		free(input);
		return (2);
	}
	return (0);
}

void	execute_commands(t_node *list, t_data *data)
{
	lexer(list);
	if (lexer_cmd(list, data) == 0)
		data->exit_code = ft_exceve(list, data, &list->env);
	ft_free_return_loop(list);
}

char	*ft_read_input(t_data *data)
{
	char	*input;

	setup_signals();
	input = readline("minishell$ ");
	if (g_signal_recu == SIGINT)
		data->exit_code = 130;
	if (input == NULL)
	{
		write(1, "exit\n", 5);
		return (NULL);
	}
	return (input);
}

int	ft_process_command(char *input, t_node *list, t_data *data, t_env *env)
{
	int	status;

	ft_init_data(data);
	add_history(input);
	input = ft_change_input(input, env, data);
	status = process_input(input, list, data, env);
	if (status != 0)
	{
		if (status == 2)
			return (2);
		return (1);
	}
	free(input);
	execute_commands(list, data);
	return (0);
}
