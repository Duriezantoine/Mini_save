/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:18:44 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/10 20:22:27 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_llist_append(struct s_llist *list, struct s_llist_node *node)
{
	if (list->size == 0)
		list->head = node;
	else
		ft_llist_get(list, list->size - 1)->next = node;
	if (node)
		list->size++;
}
