/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_export3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:17:05 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 14:07:12 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_search_and_concaten_envp(char *key, char *str, char ***envp)
{
	int		x;
	char	*key_envp;
	char	*value_envp;
	char	*new_value;
	char	*tmp;

	x = -1;
	while ((*envp)[++x])
	{
		key_envp = ft_copy_start((*envp)[x], '=');
		if (ft_strncmp(key_envp, key, ft_strlen(key)) == 0)
		{
			value_envp = ft_copy_end((*envp)[x], '=');
			new_value = ft_strjoin(value_envp, str);
			free((*envp)[x]);
			tmp = ft_strjoin(key_envp, "=");
			(*envp)[x] = ft_strjoin(tmp, new_value);
			free(tmp);
			free(key_envp);
			free(value_envp);
			free(new_value);
			break ;
		}
		free(key_envp);
	}
}

void	ft_change_var(char ***env, char *str, int x)
{
	char	*sep;

	sep = ft_strchr(str, '=');
	if (x == 1)
	{
		if (sep == NULL)
			return ;
		*sep = '\0';
		ft_search_and_change_envp(str, sep + 1, env);
	}
	else if (x == 0)
	{
		*(sep - 1) = '\0';
		ft_search_and_concaten_envp(str, sep + 1, env);
	}
}

void	ft_delim_envp(char ***env, char *str)
{
	char	*sep;

	sep = ft_strchr(str, '=');
	if (sep == NULL)
		ft_insert_envp(env, str, NULL);
	else
	{
		*sep = '\0';
		ft_insert_envp(env, str, sep + 1);
	}
}

void	ft_insert_envp(char ***env, char *key, char *value)
{
	char	*str;
	char	*tmp;

	if (value == NULL)
		*env = ft_add_string_to_array(*env, key);
	else
	{
		tmp = ft_strjoin(key, "=");
		str = ft_strjoin(tmp, value);
		free(tmp);
		*env = ft_add_string_to_array(*env, str);
		free(str);
	}
}

char	*ft_copy_end(char *str, char c)
{
	char	*dest;
	int		x;
	int		i;

	x = 0;
	i = 0;
	while (str[x])
	{
		if (str[x] == c)
			break ;
		x++;
	}
	dest = malloc((sizeof(char *) * (ft_strlen(str) - x + 1)));
	x++;
	while (str[x])
	{
		dest[i] = str[x];
		i++;
		x++;
	}
	dest[i] = '\0';
	return (dest);
}
