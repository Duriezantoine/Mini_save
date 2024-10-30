/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:15:21 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 14:57:34 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit_code(char **save, t_data *data)
{
	char	*tampon;
	char	*new_val;

	tampon = ft_itoa(data->exit_code);
	if (!tampon)
		return (1);
	new_val = ft_strjoin(tampon, *save + 1);
	free(*save);
	free(tampon);
	if (!new_val)
		return (1);
	*save = new_val;
	return (0);
}

int	search_env_list(char **save, t_env *tmp)
{
	char	*tampon;

	while (tmp)
	{
		if (strequ((*save), tmp->key))
		{
			tampon = ft_strdup(tmp->value);
			if (!tampon)
				return (1);
			free((*save));
			(*save) = tampon;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_search_var_env(char **save, t_env *env, t_data *data)
{
	if ((*save)[0] == '?')
		return (handle_exit_code(save, data));
	return (search_env_list(save, env));
}

void	init_values(int *i, int *c, int *y, char *g)
{
	*y = 0;
	*i = 0;
	*c = 0;
	*g = 0;
}

void	process_quotes(char *str, int *i, int *c, int *y)
{
	*i += 2;
	*y = *i;
	while (str[*i] != '"')
	{
		(*i)++;
		(*c)++;
	}
}
