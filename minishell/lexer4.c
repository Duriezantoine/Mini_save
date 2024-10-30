/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:13:52 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 17:33:03 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*find_previous_node(t_arg *head, t_arg *current)
{
	t_arg	*previous;
	t_arg	*temp;

	previous = NULL;
	temp = head;
	while (temp != NULL && temp->next != current)
	{
		previous = temp;
		temp = temp->next;
	}
	return (previous);
}

void	delete_node(t_arg **head, t_arg *node_to_delete)
{
	t_arg	*previous;

	if (*head == NULL || node_to_delete == NULL)
		return ;
	previous = find_previous_node(*head, node_to_delete);
	if (previous != NULL)
		previous->next = node_to_delete->next;
	else
		*head = node_to_delete->next;
	if (node_to_delete->next != NULL)
		node_to_delete->next->prev = previous;
	free(node_to_delete);
}
