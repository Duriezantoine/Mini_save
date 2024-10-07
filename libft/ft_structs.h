/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 22:57:08 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/01 01:11:49 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCTS_H
# define FT_STRUCTS_H

# include "ft_types.h"
# include <stddef.h>

struct					s_arena
{
	void				*ptr;
	void				*current;
	size_t				size;
	t_bool				is_free;
};

struct					s_complex
{
	t_f64				r;
	t_f64				i;
};

struct					s_llist_node
{
	void				*data;
	struct s_llist_node	*next;
};

struct					s_llist
{
	struct s_llist_node	*head;
	t_u64				size;
};

struct					s_double
{
	void				*a;
	void				*b;
};

#endif // STRUCTS_H
