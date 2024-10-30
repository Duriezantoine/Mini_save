/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:44:24 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 11:07:01 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_env(char *save, t_env ***env)
{
	t_env	*tmp;
	char	cwd[1024];

	tmp = **env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", 6) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(save);
		}
		if (ft_strncmp(tmp->key, "PWD", 3) == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				free(tmp->value);
				tmp->value = ft_strdup(cwd);
			}
		}
		tmp = tmp->next;
	}
	free(save);
}

char	*new_path_cd(char *s, t_env **env)
{
	char	*dest;
	int		i;
	int		x;

	x = 0;
	i = 0;
	dest = NULL;
	while (s[i])
	{
		if (s[i] == '~')
			break ;
		i++;
	}
	dest = ft_execute_cd_home(env, 1);
	x = ft_strlen(dest);
	while (s[++i])
	{
		dest[x++] = s[i];
	}
	dest[x] = '\0';
	return (dest);
}

char	*ft_execute_cd_home(t_env **env, int i)
{
	t_env	*tmp;
	char	*dest;
	char	*save;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp("HOME", tmp->key, 4) == 0)
		{
			if (i == 0)
			{
				save = save_pwd(env);
				if (chdir(tmp->value) != 0)
					ft_putstr_fd("Failed to enter directory", 2);
				ft_change_env(save, &env);
				return (NULL);
			}
			dest = ft_strdup(tmp->value);
			return (dest);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_no_cd_(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && str1[i] != '\0' && str2[i] != '\0'
		&& str1[i] == str2[i])
		i++;
	return (((unsigned char)str1[i]) - ((unsigned char)str2[i]));
}
