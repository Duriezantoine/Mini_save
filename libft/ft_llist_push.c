/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:28:08 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/10 20:30:21 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_llist_push(struct s_llist *list, struct s_llist_node *node)
{
	if (node)
	{
		node->next = list->head;
		list->head = node;
		list->size++;
	}
}
