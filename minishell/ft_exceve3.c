/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:20:18 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/30 15:03:19 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve_built_exit(t_exec_info *info, t_exec *lst, t_node *list)
{
	ft_free_env(&(list->env));
	free_all_exec(lst, info->len);
	if (info->last_in > 0)
		close(info->last_in);
	if (info->i < info->len - 1)
	{
		close(info->p[1]);
		info->last_in = info->p[0];
	}
	ft_free_return_loop(list);
	ft_free_end(list, info->env);
	exit(info->ret);
}

void	ft_execve_dup_io(t_exec_info *info, t_exec *lst)
{
	if (lst[info->i].in != 0)
	{
		dup2(lst[info->i].in, 0);
		close(lst[info->i].in);
	}
	if (lst[info->i].out != 1)
	{
		dup2(lst[info->i].out, 1);
		close(lst[info->i].out);
	}
}

void	ft_execve_built(t_exec_info *info, t_exec *lst, t_node *list,
		t_data *data)
{
	int	stdout_copy;
	int	stdin_copy;

	if (open_in_out(&lst[info->i]) != 0)
		info->ret = 1;
	else
	{
		stdin_copy = dup(0);
		stdout_copy = dup(1);
		ft_execve_dup_io(info, lst);
		info->ret = ft_excev_butlin(&lst, &list, info->i, data);
		dup2(stdin_copy, 0);
		dup2(stdout_copy, 1);
		close(stdin_copy);
		close(stdout_copy);
		if (lst[info->i].argv[0] != NULL && strequ(lst[info->i].argv[0], "exit")
			&& info->len == 1)
		{
			if (info->ret == -1)
				info->ret = 1;
			else
				ft_execve_built_exit(info, lst, list);
		}
	}
}
