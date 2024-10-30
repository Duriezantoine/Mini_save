/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:13:49 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/30 14:00:27 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *command)
{
	if (ft_strncmp(command, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(command, "env", 3) == 0)
		return (1);
	if (ft_strncmp(command, "unset", 4) == 0)
		return (1);
	if (ft_strncmp(command, "export", 6) == 0)
		return (1);
	if (ft_strncmp(command, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "exit", 4) == 0)
		return (1);
	return (0);
}

void	ft_check_bulting(t_cmd **cmd, t_arg *arg)
{
	t_arg	*tmp;

	tmp = arg;
	(void)cmd;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			if (is_builtin(tmp->str_command))
				(*cmd)->is_builtin = 1;
		}
		tmp = tmp->next;
	}
}

void	ft_check_iofile(t_node *list, t_arg *arg)
{
	t_arg		*tmp;
	t_iofile	*files;
	t_iofile	*new;
	
	tmp = arg;
	files = NULL;
	while (tmp)
	{
		if (tmp->type == INFILE || tmp->type == HEREDOC_INFILE
			|| tmp->type == OUTFILE || tmp->type == APPEND)
		{
			new = malloc(sizeof(t_iofile));
			new->type = tmp->type;
			new->file = ft_strdup(tmp->str_command);
			new->next = NULL;
			if (files == NULL)
				list->cmd->io_str = new;
			else
				files->next = new;
			files = new;
		}
		tmp = tmp->next;
	}
}

int	lexer_cmd(t_node *list, t_data *data)
{
	t_node	*base_node;

	(void)data;
	base_node = list;
	while (list)
	{
		ft_init_cmd(&list->cmd);
		ft_insert_double_tab(&list->cmd, list->arg);
		ft_verif_cmd(&list->cmd, list->arg);
		if (ft_insert_cmd_here_doc(list, list->arg, data, base_node) == 1)
			return (1);
		ft_check_bulting(&list->cmd, list->arg);
		ft_check_iofile(list, list->arg);
		// ft_check_outfile(list, &list->cmd, list->arg);
		// if (ft_check_infile_cmd(list, list->arg) == -1)
		// {
		// 	data->exit_code = 1;
		// 	return (1);
		// }
		data->count = data->count + 1;
		list = list->next;
	}
	return (0);
}
