/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/29 08:50:40 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_split_datas(t_split_datas *data)
{
	data->in_quotes = 0;
	data->in_single_quotes = 0;
	data->j = 0;
	data->k = 0;
}

static void	handle_quotes(char c, t_split_datas *data)
{
	if (c == '"')
		data->in_quotes = !data->in_quotes;
	if (c == '\'')
		data->in_single_quotes = !data->in_single_quotes;
}

static void	handle_whitespace(char *temp, char **result, t_split_datas *data)
{
	temp[data->j] = '\0';
	result[data->k] = ft_strdup(temp);
	data->k += 1;
	data->j = 0;
}

void	split_string_d(char *str, char **result)
{
	t_split_datas	data;
	char			*temp;
	int				i;

	temp = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	if (!temp)
		return ;
	init_split_datas(&data);
	i = -1;
	while (str[++i])
	{
		handle_quotes(str[i], &data);
		if (ft_white_space(str[i]) && !data.in_quotes && !data.in_single_quotes)
			handle_whitespace(temp, result, &data);
		else
			temp[data.j++] = str[i];
	}
	temp[data.j] = '\0';
	result[data.k] = ft_strdup(temp);
	free(temp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_node	*list;

	(void)argv;
	(void)argc;
	rl_catch_signals = 0;
	data.exit_code = 0;
	if (argc == 2)
		ft_out_exit(1);
	list = ft_calloc(1, sizeof(t_node));
	if (list == NULL)
		ft_out_exit(3);
	list->pipe[0] = -1;
	list->env = ft_insert_env(envp);
	return (shell_loop(list, &data, &list->env));
}
