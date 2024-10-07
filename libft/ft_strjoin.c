/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:10:17 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/15 14:21:24 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	total_lenght;
	int	dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	total_lenght = dest_len + ft_strlen(src);
	while (i < dest_len)
		i++;
	while (i < total_lenght)
	{
		dest[i] = src[i - dest_len];
		i++;
	}
	dest[total_lenght] = 0;
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_malloc;
	char	*ret;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	len_malloc = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = (char *)ft_calloc(len_malloc, sizeof(char));
	if (!ret)
		return (NULL);
	return (ft_strcat(ft_strcat(ret, (char *)s1), (char *)s2));
}
