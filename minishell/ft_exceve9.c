/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:52:29 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 11:41:38 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_exec(struct s_exec *execs, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free_exec(execs[i]);
		i++;
	}
	free(execs);
}

int	env_len(t_env *list)
{
	int	ret;

	ret = 0;
	while (list)
	{
		ret++;
		list = list->next;
	}
	return (ret);
}

void	real_strcat(char *dest, char *src)
{
	int	start;
	int	i;

	i = 0;
	start = ft_strlen(dest);
	while (i < (int)ft_strlen(src))
	{
		dest[start + i] = src[i];
		i++;
	}
	dest[start + i] = 0;
}

static char	*create_env_str(t_env *env)
{
	char	*ret;
	int		len;

	len = ft_strlen(env->key);
	if (env->value)
		len += ft_strlen(env->value) + 2;
	else
		len += 1;
	ret = ft_calloc(len, sizeof(char));
	if (!ret)
		return (NULL);
	real_strcat(ret, env->key);
	if (env->value)
	{
		ret[ft_strlen(env->key)] = '=';
		real_strcat(ret, env->value);
	}
	return (ret);
}

char	**get_env_cdt(t_env *env)
{
	char	**ret;
	int		i;
	t_env	*tmp;

	tmp = env;
	ret = ft_calloc(env_len(env) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (env)
	{
		ret[i] = create_env_str(env);
		if (!ret[i])
			return (NULL);
		i++;
		env = env->next;
	}
	return (ret);
}
