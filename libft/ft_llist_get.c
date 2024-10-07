/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:34:45 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/10 20:38:04 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

struct s_llist_node	*ft_llist_get(struct s_llist *list, t_u64 idx)
{
	struct s_llist_node	*last;
	t_u64				index;

	if (idx >= list->size)
		return (NULL);
	last = list->head;
	index = 0;
	while (index != idx)
	{
		last = last->next;
		index++;
	}
	return (last);
}
