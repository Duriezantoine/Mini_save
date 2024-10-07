/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_node_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:12:39 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/10 20:15:24 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

struct s_llist_node	*ft_llist_node_create(void *data)
{
	struct s_llist_node	*node;

	node = ft_calloc(1, sizeof(struct s_llist_node));
	if (!node)
		return (NULL);
	node->data = data;
	return (node);
}
