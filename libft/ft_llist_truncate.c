/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_truncate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:23:27 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/10 20:33:14 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

struct s_llist_node	*ft_llist_truncate(struct s_llist *list)
{
	struct s_llist_node	*ret;

	if (list->size > 0)
		list->size--;
	ret = ft_llist_get(list, list->size);
	if (list->size == 0)
		list->head = NULL;
	else
		ft_llist_get(list, list->size - 1)->next = NULL;
	return (ret);
}
