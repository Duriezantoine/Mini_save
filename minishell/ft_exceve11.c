/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:44:57 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 13:42:47 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env_var(char *var)
{
	char	*sep;

	ft_putstr_fd("declare -x ", 1);
	sep = ft_strchr(var, '=');
	if (sep)
	{
		*sep = '\0';
		ft_putstr_fd(var, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(sep + 1, 1);
		ft_putstr_fd("\"", 1);
		*sep = '=';
	}
	else
		ft_putstr_fd(var, 1);
	ft_putstr_fd("\n", 1);
}

int	ft_is_ignored_var(char *var)
{
	return (ft_strncmp(var, "_=", 2) == 0 || ft_strncmp(var, "_\0", 2) == 0);
}

void	ft_display_envp(char *copy_envp[])
{
	int	i;

	i = -1;
	sort_envp_ex(copy_envp);
	while (copy_envp[++i])
	{
		if (!ft_is_ignored_var(copy_envp[i]))
			ft_print_env_var(copy_envp[i]);
	}
}

void	ft_start_unset(struct s_exec **lst, t_node **list, int i)
{
	char	**old;

	bulting_unset(&lst[i]->envp, (*list)->cmd, (*list));
	old = lst[i]->envp;
	lst[i]->envp = get_env_cdt((*list)->env);
	ft_free_double_tab(old);
}

int	ft_choose_export(struct s_exec **lst, int i, int *ret)
{
	if ((*lst)->argv[1] == NULL)
		ft_display_envp((*lst)[i].envp);
	else if ((*lst)[i].nb_exec == 1)
		*ret = bulting_export((*lst)[i].argv, &(*lst)[i].envp);
	else
		return (1);
	return (0);
}
