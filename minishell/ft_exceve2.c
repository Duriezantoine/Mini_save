/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:19:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 13:39:48 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve_bin_child(t_exec_info *info, struct s_exec *lst, t_node *list)
{
	int	exit_code;

	if (info->i < info->len - 1)
		close(info->p[0]);
	exit_code = open_in_out(&lst[info->i]);
	if (exit_code == 0)
	{
		ft_execve_dup_io(info, lst);
		exit_code = exec(lst[info->i].exec, lst[info->i].argv,
				&lst[info->i].envp);
	}
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
	exit(exit_code);
}

void	ft_init_execve(t_exec_info *info, struct s_exec **lst, t_node *list,
		t_env **env)
{
	*lst = lst_to_execs(list, &(info->len));
	info->last_in = 0;
	info->ret = -1;
	info->env = env;
	signal(SIGQUIT, handler_void);
	signal(SIGINT, handler_void);
	info->i = -1;
}

int	ft_manage_pipe(t_exec_info *info, struct s_exec *lst)
{
	if (info->i < info->len - 1 && pipe(info->p) < 0)
	{
		ft_putstr_fd("Erreur: Échec de la création du pipe.\n", 2);
		return (1);
	}
	if (lst[info->i].in < 0)
		lst[info->i].in = info->last_in;
	if (lst[info->i].out < 0)
	{
		if (info->i < info->len - 1)
			lst[info->i].out = info->p[1];
		else
			lst[info->i].out = 1;
	}
	return (0);
}

int	ft_exec_cmd(t_exec_info *info, struct s_exec *lst, t_node *list,
		t_data *data)
{
	if (ft_exceve_bulting(lst[info->i].argv[0], info->len) == 0)
		ft_execve_built(info, lst, list, data);
	else
	{
		lst[info->i].pid = fork();
		if (lst[info->i].pid < 0)
		{
			write(2, "Erreur: Échec du fork.\n",
				ft_strlen("Erreur: Échec du fork.\n"));
			return (1);
		}
		else if (lst[info->i].pid == 0)
			ft_execve_bin_child(info, lst, list);
	}
	return (0);
}

int	ft_exceve(t_node *list, t_data *data, t_env **env)
{
	t_exec_info		info;
	struct s_exec	*lst;
	int				rete;

	ft_init_execve(&info, &lst, list, env);
	while (++info.i < info.len)
	{
		if (ft_manage_pipe(&info, lst) || ft_exec_cmd(&info, lst, list, data))
			break ;
		if (info.last_in > 0)
			close(info.last_in);
		if (info.i < info.len - 1)
		{
			close(info.p[1]);
			info.last_in = info.p[0];
		}
	}
	rete = ft_wait_all(lst, info.len);
	if (rete != -1)
		info.ret = rete;
	ft_free_env(&(list->env));
	list->env = ft_insert_env(lst[0].envp);
	free_all_exec(lst, info.len);
	return (info.ret);
}
