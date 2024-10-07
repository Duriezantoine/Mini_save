/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:49:57 by tdelage           #+#    #+#             */
/*   Updated: 2024/10/07 22:52:19 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstring.h"
#include <stdlib.h>

enum e_string_error	string_error(bool set, enum e_string_error value)
{
	static enum e_string_error	string_error = STRING_SUCCESS;

	if (set)
		string_error = value;
	return (string_error);
}

void	string_destroy(struct s_string *s)
{
	if (s->unowned)
	{
		string_error(true, STRING_NO_FREE_UNOWNED);
		return ;
	}
	free(s->ptr);
	*s = (struct s_string){0};
}

bool	string_check(struct s_string self)
{
	string_error(true, STRING_SUCCESS);
	if (!self.ptr || self.capacity == 0)
	{
		string_error(true, STRING_EMPTY);
		return (false);
	}
	if (self.len > self.capacity)
	{
		string_error(true, STRING_CORRUPTED);
		return (false);
	}
	return (true);
}

struct s_string	string_copy(struct s_string self)
{
	char	*ptr;

	if (!string_check(self))
		return ((struct s_string){0});
	ptr = ft_calloc(self.len, sizeof(char));
	if (!ptr)
	{
		string_error(true, STRING_MALLOC_ERROR);
		return ((struct s_string){0});
	}
	ft_memcpy(ptr, self.ptr, self.len);
	return ((struct s_string){
		.unowned = false,
		.ptr = ptr,
		.capacity = self.len,
		.len = self.len,
	});
}
