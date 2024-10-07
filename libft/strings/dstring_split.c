/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstring_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:09 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/01 05:53:27 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstring.h"
#include "dstring_utils.h"

size_t	string_search(struct s_string hay, struct s_string needle)
{
	size_t	i;

	if (!string_check(hay) || !string_check(needle))
		return (0);
	if (needle.len > hay.len)
	{
		string_error(true, STRING_NEEDLE_TOO_LONG);
		return (0);
	}
	i = 0;
	while (i < hay.len - needle.len)
	{
		if (ft_strncmp(hay.ptr + i, needle.ptr, needle.len) == 0)
			return (i);
		i++;
	}
	string_error(true, STRING_NEEDLE_NOT_FOUNDED);
	return (0);
}

size_t	count_sub_string(struct s_string hay, struct s_string needle)
{
	size_t	i;
	size_t	count;
	bool	s;

	s = true;
	i = 0;
	count = 0;
	while (i < hay.len)
	{
		if (!s && string_contain(hay.ptr[i], needle))
			s = true;
		if (s && !string_contain(hay.ptr[i], needle))
		{
			count++;
			s = false;
		}
		i++;
	}
	return (count);
}

void	string_zero_split(size_t *s[4], bool *b)
{
	*b = true;
	*(s[0]) = -1;
	*(s[1]) = 0;
	*(s[2]) = 0;
	*(s[3]) = 0;
}

void	actual_string_split(struct s_string hay, struct s_string needles,
		struct s_string *ret)
{
	size_t	i;
	bool	s;
	size_t	len;
	size_t	offset;
	size_t	x;

	string_zero_split((size_t *[4]){&i, &len, &offset, &x}, &s);
	while (++i < hay.len)
	{
		if (!s && string_contain(hay.ptr[i], needles))
		{
			ret[x++] = string_new_u(hay.ptr + offset, len);
			s = true;
		}
		if (s && !string_contain(hay.ptr[i], needles))
		{
			len = 0;
			s = false;
			offset = i;
		}
		len++;
	}
	if (!s)
		ret[x] = string_new_u(hay.ptr + offset, len);
}

struct s_string	*string_split(struct s_string hay, struct s_string needles,
		size_t *count)
{
	struct s_string	*ret;

	if (!string_check(hay) || !string_check(needles))
		return (NULL);
	if (needles.len > hay.len)
	{
		string_error(true, STRING_NEEDLE_TOO_LONG);
		return (NULL);
	}
	*count = count_sub_string(hay, needles);
	ret = ft_calloc(*count, sizeof(struct s_string));
	if (!ret)
	{
		string_error(true, STRING_MALLOC_ERROR);
		return (NULL);
	}
	actual_string_split(hay, needles, ret);
	return (ret);
}
