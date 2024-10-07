/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstring_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:49:45 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/01 04:50:08 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstring.h"
#include "dstring_utils.h"

struct s_string	string_new_from_cstr(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	return ((struct s_string){
		.unowned = false,
		.ptr = s,
		.len = len,
		.capacity = len,
	});
}

struct s_string	string_new(char *s, size_t len)
{
	return ((struct s_string){
		.unowned = false,
		.ptr = s,
		.len = len,
		.capacity = len,
	});
}

struct s_string	string_new_with_capacity(size_t capa)
{
	char	*ptr;

	string_error(true, STRING_SUCCESS);
	ptr = ft_realloc(NULL, 0, capa);
	if (!ptr)
	{
		string_error(true, STRING_MALLOC_ERROR);
		return ((struct s_string){0});
	}
	return ((struct s_string){
		.unowned = false,
		.ptr = ptr,
		.len = 0,
		.capacity = capa,
	});
}

struct s_string	string_new_u_from_cstr(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	return ((struct s_string){
		.unowned = true,
		.ptr = s,
		.len = len,
		.capacity = len,
	});
}

struct s_string	string_new_u(char *s, size_t len)
{
	return ((struct s_string){
		.unowned = true,
		.ptr = s,
		.len = len,
		.capacity = len,
	});
}
