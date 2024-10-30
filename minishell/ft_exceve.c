/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:35:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 13:26:52 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_double_tab(char **str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		free(str[x]);
		x++;
	}
	free(str);
}

char	*ft_getpath(char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

static char	*create_full_path(char **split_path, char *str, int i)
{
	char	*demi_path;
	char	*full_path;

	demi_path = ft_strjoin(split_path[i], "/");
	full_path = ft_strjoin(demi_path, str);
	free(demi_path);
	return (full_path);
}

char	*get_path(char *str, char **env)
{
	char	*path;
	char	**split_path;
	char	*full_path;
	int		i;

	path = ft_getpath(env);
	if (!path)
		return ("R");
	split_path = ft_split(path, ':');
	if (!split_path)
		return ("S");
	i = -1;
	while (split_path[++i])
	{
		full_path = create_full_path(split_path, str, i);
		if (access(full_path, F_OK) != -1)
		{
			ft_free_double_tab(split_path);
			return (full_path);
		}
		free(full_path);
	}
	ft_free_double_tab(split_path);
	return (NULL);
}

int	cdt_len(char **a)
{
	int	i;

	if (!a)
		return (0);
	i = 0;
	while (a[i])
		i++;
	return (i);
}
