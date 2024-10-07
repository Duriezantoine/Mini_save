/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_node_destroy.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:16:25 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/10 20:18:12 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

void	ft_llist_node_destroy(struct s_llist_node *node, t_lstdel_f del)
{
	if (!node)
		return ;
	del(node->data);
	free(node);
}
