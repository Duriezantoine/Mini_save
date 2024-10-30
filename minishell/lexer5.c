/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:30:22 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 13:26:44 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_tmp_file(char *tmp_file_name, t_arg *current, t_data *data,
		t_node *list)
{
	if (tmp_file_name == NULL)
	{
		free(tmp_file_name);
		data->exit_code = 130;
		return (1);
	}
	if (list->cmd->cmd != 0)
	{
		free(current->str_command);
		current->str_command = tmp_file_name;
		current->type = HEREDOC_INFILE;
	}
	return (0);
}

void	ft_free_tmp_file(char *tmp_file_name)
{
	if (ft_strncmp(tmp_file_name, "No_tmp_name",
			(size_t)(ft_strlen(tmp_file_name) == 0)))
		free(tmp_file_name);
}

int	ft_process_heredoc(t_arg *current, t_node *list, t_data *data,
		t_node *base_node)
{
	char	*tmp_file_name;

	current = current->next;
	tmp_file_name = ft_here_doc(data, list, current->str_command, base_node);
	if (ft_handle_tmp_file(tmp_file_name, current, data, list))
		return (1);
	ft_free_tmp_file(tmp_file_name);
	return (0);
}

int	ft_insert_cmd_here_doc(t_node *list, t_arg *list_arg, t_data *data,
		t_node *base_node)
{
	t_arg	*current;

	current = list_arg;
	while (current)
	{
		if (current->type == HEREDOC && current->next->type == DELIM)
		{
			if (ft_process_heredoc(current, list, data, base_node))
				return (1);
		}
		current = current->next;
	}
	return (0);
}

void	ft_verif_cmd(t_cmd **list, t_arg *list_arg)
{
	t_arg	*arg;
	int		count;

	arg = list_arg;
	count = 0;
	while (arg)
	{
		if (arg->type == CMD)
			count++;
		arg = arg->next;
	}
	(*list)->cmd = count;
}
