/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:26:27 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 14:04:37 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arg(t_arg *arg)
{
	if (arg == NULL)
	{
		printf("t_arg is NULL\n");
		return ;
	}
	printf("t_arg:\n");
	printf("  str_command: %s\n", arg->str_command);
	printf("  type: %d\n", arg->type);
	printf("  prev: %p\n", (void *)arg->prev);
	printf("  next: %p\n", (void *)arg->next);
}

void	write_to_temp_file(int fd, char *buffer)
{
	write(fd, buffer, ft_strlen(buffer));
}

int	ft_search_arg(t_arg *list)
{
	int	x;

	x = 0;
	while (list)
	{
		if (list->type == CMD || list->type == ARG)
			x++;
		list = list->next;
	}
	return (x);
}

void	ft_init_cmd(t_cmd **list)
{
	(*list) = malloc(sizeof(t_cmd));
	(*list)->cmd_and_args = NULL;
	(*list)->is_builtin = -1;
	(*list)->prev = NULL;
	(*list)->next = NULL;
	(*list)->input_str = NULL;
	(*list)->output_str = NULL;
}

void	ft_insert_double_tab(t_cmd **list, t_arg *list_arg)
{
	t_arg	*args;
	int		count_arg;

	args = list_arg;
	count_arg = ft_search_arg(list_arg);
	(*list)->cmd_and_args = malloc((count_arg + 1) * sizeof(char *));
	count_arg = 0;
	while (args)
	{
		if (args->type == CMD || args->type == ARG)
		{
			(*list)->cmd_and_args[count_arg] = ft_strdup(args->str_command);
			count_arg++;
		}
		args = args->next;
	}
	(*list)->cmd_and_args[count_arg] = NULL;
}
