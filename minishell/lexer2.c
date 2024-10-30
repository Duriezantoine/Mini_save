/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:13:16 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 14:42:51 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_spec(t_arg *elem);
static void	set_file(t_arg *elem);
static void	set_cmd(t_arg *elem);
static void	set_arg(t_arg *elem);

void	lexer(t_node *list)
{
	while (list)
	{
		set_spec(list->arg);
		set_file(list->arg);
		set_cmd(list->arg);
		set_arg(list->arg);
		list = list->next;
	}
}

static void	set_spec(t_arg *elem)
{
	while (elem)
	{
		if (ft_strcmp(elem->str_command, "<<") == 0 && elem->quot == 2)
			elem->type = HEREDOC;
		else if (ft_strcmp(elem->str_command, "<") == 0 && elem->quot == 2)
			elem->type = INPUT;
		else if (ft_strcmp(elem->str_command, ">>") == 0 && elem->quot == 2)
			elem->type = APPEND;
		else if (ft_strcmp(elem->str_command, ">") == 0 && elem->quot == 2)
			elem->type = OUTPUT;
		elem = elem->next;
	}
}

static void	set_file(t_arg *elem)
{
	while (elem)
	{
		if (elem->prev && elem->prev->type == INPUT)
			elem->type = INFILE;
		else if (elem->prev && elem->prev->type == OUTPUT)
			elem->type = OUTFILE;
		else if (elem->prev && elem->prev->type == APPEND)
			elem->type = OUTFILE;
		else if (elem->prev && elem->prev->type == HEREDOC)
			elem->type = DELIM;
		elem = elem->next;
	}
}

static void	set_cmd(t_arg *elem)
{
	while (elem && elem->next)
		elem = elem->next;
	while (elem)
	{
		if (elem->type == -1 && (!elem->prev || elem->prev->type >= 0))
		{
			elem->type = CMD;
		}
		elem = elem->prev;
	}
}

static void	set_arg(t_arg *elem)
{
	t_arg	*tmp;
	int		cmd_count;

	tmp = elem;
	while (tmp)
	{
		if (tmp->type == -1 && tmp->str_command[0] == '-')
			tmp->type = ARG;
		else if (tmp->type == -1 && tmp->str_command[0] != '-')
			tmp->type = ARG;
		tmp = tmp->next;
	}
	cmd_count = 0;
	while (elem)
	{
		if (elem->type == CMD)
			cmd_count++;
		if (elem->type == CMD && cmd_count > 1)
			elem->type = ARG;
		elem = elem->next;
	}
}
