/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pars9.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:02:25 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 16:41:36 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_end_of_input(char c, t_echo *data_echo, int *ss_quot, int *wt_quot)
{
	if (c == '\0')
	{
		data_echo->s_quot = *ss_quot;
		data_echo->w_quot = *wt_quot;
		return (1);
	}
	return (0);
}

char	*find_env_value(char *var, t_env *env)
{
	char	*tmp_save;

	while (env)
	{
		if (strequ(var, env->key))
		{
			tmp_save = ft_strdup(env->value);
			return (tmp_save);
		}
		env = env->next;
	}
	return (NULL);
}

int	ft_handle_quotes(char *input, int *i, int *wt_quot, char c)
{
	(*i)++;
	while (input[*i] != '\0' && input[*i] != c)
	{
		while (input[*i])
		{
			(*i)++;
			if (input[*i] == c)
				break ;
		}
		if (input[*i] == '\0' || ft_white_space(input[*i]))
			break ;
		while (((ft_isalnum(input[*i]) == 1) && input[*i] != '\0')
			&& input[*i] != '\'' && input[*i] != '"')
			(*i)++;
		(*i)++;
		if (input[*i] == '\0' || ft_white_space(input[*i]))
			break ;
		if (input[*i] == '\'' || input[*i] == '"')
		{
			c = input[*i];
			(*i)++;
		}
	}
	(*wt_quot)++;
	return (0);
}

void	ft_handle_alphanumeric(char *input, int *i, int *ss_quot, int x)
{
	char	c;

	if (x == 1)
		(*ss_quot)++;
	if (input[*i] == '\0' && ft_white_space(input[*i]))
		return ;
	if (((ft_isalnum(input[*i]) == 1) && input[*i] != '\0')
		&& (!ft_white_space(input[*i])))
	{
		while (((ft_isalnum(input[*i]) == 1)) && input[*i] != '\0'
			&& !ft_white_space(input[*i]))
		{
			if (input[*i] == '"' || input[*i] == '\'')
			{
				c = input[*i];
				(*i)++;
				while (input[*i] != c && input[*i] != '\0')
					(*i)++;
			}
			(*i)++;
		}
	}
	return ;
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}
