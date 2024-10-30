/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:51:31 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 15:21:18 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_start_var(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_' || c == '?');
}

static void	separate_env_var(char **var, int *x, t_env *env, t_data *data)
{
	char	*changed_str;
	char	*previous;

	(*var)[*x] = 0;
	previous = ft_strdup(*var);
	(*var)[*x] = '$';
	changed_str = *var + *x;
	*x += ft_change_var_environnement(&changed_str, env, data) - 1;
	free(*var);
	*var = ft_strjoin(previous, changed_str);
	free(previous);
	free(changed_str);
}

static void	ft_change_input_loop(char *var, t_env *env, t_data *data,
		char **save_tmp)
{
	int		x;
	char	*changed_str;
	char	c;

	x = 0;
	c = 0;
	while (ft_isalnum(var[x]) || (c != 0 && var[x] != 0))
	{
		if ((var[x] == '\'' || var[x] == '"') && (c == 0 || c == var[x]))
		{
			if (c == 0)
				c = var[x];
			else
				c = 0;
		}
		else if (c != '\'' && var[x] == '$'
			&& (c == 0 || ft_is_start_var(var[x + 1])))
			separate_env_var(&var, &x, env, data);
		x++;
	}
	changed_str = ft_strjoin(*save_tmp, var);
	free(*save_tmp);
	free(var);
	*save_tmp = ft_strjoin(changed_str, " ");
	free(changed_str);
}

char	*ft_change_input(char *str, t_env *env, t_data *data)
{
	char	**tmp;
	char	*save_tmp;
	int		x;
	char	*save;

	save_tmp = NULL;
	save = ft_strjoin(str, " ");
	while (count_dollars_outside_quotes(str) <= 0)
		break ;
	save_tmp = ft_strdup(" ");
	tmp = ft_split_d((save));
	free(save);
	x = -1;
	while (tmp[++x])
		ft_change_input_loop(tmp[x], env, data, &save_tmp);
	free(str);
	free(tmp[x]);
	free(tmp);
	return (save_tmp);
}
