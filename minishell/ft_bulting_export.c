/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:56:21 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 14:07:12 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bulting_export(char **argv, char ***env)
{
	char	**tmp;
	int		x;

	tmp = argv;
	x = 1;
	while (tmp[x])
	{
		if (ft_verif_export(tmp[x]) == 1)
			return (1);
		if (ft_search_envp(*env, tmp[x]) == 2)
			ft_change_var(env, tmp[x], 0);
		else if (ft_search_envp(*env, tmp[x]) == 0)
			ft_delim_envp(env, tmp[x]);
		else
			ft_change_var(env, tmp[x], 1);
		x++;
	}
	return (0);
}

void	ft_search_and_change_envp(char *key, char *str, char ***envp)
{
	int		x;
	char	*key_envp;
	char	*tmp;

	x = 0;
	while ((*envp)[x])
	{
		key_envp = ft_copy_start((*envp)[x], '=');
		if (ft_strncmp(key_envp, key, ft_strlen(key)) == 0)
		{
			free((*envp)[x]);
			tmp = ft_strjoin(key, "=");
			(*envp)[x] = ft_strjoin(tmp, str);
			free(tmp);
			free(key_envp);
			break ;
		}
		free(key_envp);
		x++;
	}
}
