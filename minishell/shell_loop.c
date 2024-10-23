/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:31:12 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/23 17:31:17 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_signals(void)
{
	signal_recu = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

static int	handle_empty_input(char *input, t_data *data)
{
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

static int	process_input(char *input, t_node *list,
	t_data *data, t_env *env)
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

static void	execute_commands(t_node *list, t_data *data)
{
	lexer(list);
	if (lexer_cmd(list, data) == 0)
		data->exit_code = ft_exceve(list, data, &list->env);
	ft_free_return_loop(list);
}

int	shell_loop(t_node *list, t_data *data, t_env **env)
{
	char	*input;
	int		status;

	while (1)
	{
		setup_signals();
		input = readline("minishell$ ");
		if (signal_recu == SIGINT)
			data->exit_code = 130;
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (handle_empty_input(input, data))
			continue ;
		ft_init_data(data);
		add_history(input);
		input = ft_change_input(&input, *env, data);
		status = process_input(input, list, data, *env);
		if (status == 2)
			break ;
		if (status == 1)
			continue ;
		free(input);
		execute_commands(list, data);
	}
	ft_free_end(list, env);
	return (data->exit_code);
}