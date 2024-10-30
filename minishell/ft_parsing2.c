/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:55:38 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 14:41:51 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_save_v2(t_save **save, t_env *env, t_data *data)
{
	t_save	*tmp;
	int		x;
	char	*save_tmp;

	(void)env;
	tmp = *save;
	while (tmp)
	{
		x = 0;
		while (tmp->str[x])
		{
			if (tmp->str[x] == '\'' || tmp->str[x] == '"')
			{
				save_tmp = ft_change_save_v3(tmp->str, env, tmp->str[x], data);
				free(tmp->str);
				tmp->str = ft_strdup(save_tmp);
				free(save_tmp);
				break ;
			}
			x++;
		}
		tmp = tmp->next;
	}
}

static void	process_tmp_list(t_node *list, t_echo *data_echo, t_save *save)
{
	t_save	*tmp;

	tmp = save;
	while (tmp)
	{
		list->arg = ft_init_list(list, data_echo, tmp);
		tmp = tmp->next;
	}
}

int	ft_parsing(t_node *list, t_data *data, char *input, t_env *env)
{
	int		i;
	t_save	*save;
	t_echo	data_echo;
	char	**tokens;

	i = 0;
	save = NULL;
	tokens = ft_parsing_init(data, input);
	while (i < data->nbr_command)
	{
		if (i != 0)
			ft_inser_init_list_arg(&list);
		if (ft_split_with_space(&data_echo, tokens[i]) == 1)
			return (1);
		save = NULL;
		ft_insert_new_data_with_data(&save, &data_echo, env);
		ft_change_save_v2(&save, env, data);
		process_tmp_list(list, &data_echo, save);
		free_list(save);
		ft_free_data_echo(&data_echo);
		i++;
	}
	free_tokens(tokens, data->nbr_command);
	return (0);
}

char	**ft_parsing_init(t_data *data, char *input)
{
	int		len;
	char	**tokens;

	if (data == NULL)
		ft_out_exit(5);
	tokens = split_string(input, &len);
	if (tokens == NULL)
		ft_out_exit(4);
	(*data).nbr_command = len;
	return (tokens);
}
