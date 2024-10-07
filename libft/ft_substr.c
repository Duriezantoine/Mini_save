/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:40:22 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/02 16:29:25 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	char	*ret;

	j = 0;
	i = 0;
	if (src == NULL)
		return (NULL);
	i = ft_strlen(src);
	if (i > n)
		i = n;
	ret = (char *)ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (j < i)
	{
		ret[j] = src[j];
		j++;
	}
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	zero;

	zero = 0;
	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start > size)
		return (ft_strdup(&zero));
	if (size - start < len)
		len = size - start;
	return (ft_strndup(s + start, len));
}
