/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:30:42 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/10 20:34:20 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

struct s_llist_node	*ft_llist_pop(struct s_llist *list)
{
	struct s_llist_node	*ret;

	ret = list->head;
	if (ret)
		list->head = ret->next;
	else
		list->head = NULL;
	if (list->size > 0)
		list->size--;
	return (ret);
}
