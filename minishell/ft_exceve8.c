/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:50:59 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 11:42:09 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab_error(char **env_tab, int i)
{
	while (--i >= 0)
		free(env_tab[i]);
	free(env_tab);
}

static void	free_clone(char **ret, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(ret[j]);
		j++;
	}
	free(ret);
}

char	**clone_cdt(char **table)
{
	char	**ret;
	int		len;
	int		i;

	len = cdt_len(table);
	ret = ft_calloc(len + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = ft_strdup(table[i]);
		if (!ret[i])
		{
			free_clone(ret, i);
			return (NULL);
		}
		i++;
	}
	return (ret);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	ft_replace_var(char **str, t_env *env)
{
	char	*tmp;

	while (env)
	{
		tmp = ft_strjoin("$", env->key);
		if (ft_strncmp(tmp, (*str), ft_strlen(tmp)) == 0)
		{
			free(str);
			(*str) = env->value;
			return (1);
		}
		env = env->next;
	}
	return (0);
}
