/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:08:28 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/10 20:12:05 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_llist_destroy(struct s_llist *list, t_lstdel_f del)
{
	while (list->head)
		ft_llist_node_destroy(ft_llist_truncate(list), del);
	list->size = 0;
	list->head = NULL;
}
