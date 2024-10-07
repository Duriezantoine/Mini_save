/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstring_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:02 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/01 04:50:03 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstring.h"
#include "dstring_utils.h"

void	string_push(struct s_string *self, char c)
{
	if (self->unowned)
	{
		string_error(true, STRING_NO_MODIFY_UNOWNED);
		return ;
	}
	if (!string_check(*self))
		return ;
	if (self->len + 1 > self->capacity && !string_grow(self))
		return ;
	self->ptr[self->len++] = c;
}

char	string_pop(struct s_string *self)
{
	if (self->unowned)
	{
		string_error(true, STRING_NO_MODIFY_UNOWNED);
		return (0);
	}
	if (!string_check(*self))
		return (0);
	return (self->ptr[--(self->len)]);
}

void	string_push_front(struct s_string *self, char c)
{
	if (self->unowned)
	{
		string_error(true, STRING_NO_MODIFY_UNOWNED);
		return ;
	}
	if (!string_check(*self))
		return ;
	if (self->len + 1 > self->capacity && !string_grow(self))
		return ;
	ft_memmove(self->ptr + 1, self->ptr, self->len++);
	self->ptr[0] = c;
}

char	string_pop_front(struct s_string *self)
{
	char	ret;

	if (self->unowned)
	{
		string_error(true, STRING_NO_MODIFY_UNOWNED);
		return (0);
	}
	if (!string_check(*self))
		return (0);
	ret = self->ptr[0];
	ft_memmove(self->ptr, self->ptr + 1, --(self->len));
	return (ret);
}

bool	string_grow(struct s_string *self)
{
	self->capacity *= 2;
	self->ptr = ft_realloc(self->ptr, self->len, self->capacity);
	if (!self->ptr)
	{
		string_error(true, STRING_MALLOC_ERROR);
		return (false);
	}
	return (true);
}
