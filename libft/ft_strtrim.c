/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:49:31 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/26 08:05:51 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_trimleft(char const *s, char const *set)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_inset(s[i], set))
		i++;
	return (i);
}

static size_t	ft_trimright(char const *s, char const *set)
{
	size_t	s_len;

	s_len = ft_strlen(s) - 1;
	while (s_len && ft_inset(s[s_len], set))
		s_len--;
	return (s_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	finish;
	size_t	new_len;
	char	*ns;

	if (!s1)
		return (NULL);
	if (!set || !set[0])
		return (ft_strdup((char *)s1));
	if (!s1[0])
		return (ft_strdup((char *)s1));
	start = ft_trimleft(s1, set);
	finish = ft_trimright(s1, set);
	if (finish == 0)
		return (ft_strdup(""));
	new_len = finish - start + 1;
	ns = (char *)ft_calloc(new_len + 1, sizeof(char));
	if (!ns)
		return (NULL);
	ft_memcpy(ns, s1 + start, new_len);
	ns[new_len] = 0;
	return (ns);
}
