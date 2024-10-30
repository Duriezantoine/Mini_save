/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:51:14 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/25 14:18:06 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_node(t_node **list, t_node *new_list)
{
	while ((*list)->next)
	{
		(*list) = (*list)->next;
	}
	new_list->prev = (*list);
	(*list)->next = new_list;
}

void	ft_inser_init_list_arg(t_node **list)
{
	t_node	*new_list;

	ft_init_data_list(&new_list);
	append_node(list, new_list);
	(*list) = (*list)->next;
}

void	init_t_save(t_save **save)
{
	if (save == NULL)
	{
		return ;
	}
	*save = NULL;
}

void	free_list(t_save *head)
{
	t_save	*current;
	t_save	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}
