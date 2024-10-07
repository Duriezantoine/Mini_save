/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:16:57 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/05 18:11:24 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	sub_len;

	i = 0;
	sub_len = ft_strlen(sub);
	if (sub_len == 0 || sub == str)
		return ((char *)str);
	if (n == 0)
		return (NULL);
	while (str[i] != '\0' && i < n)
	{
		j = 0;
		while (str[i + j] != '\0' && sub[j] != '\0'
			&& str[i + j] == sub[j] && i + j < n)
			j++;
		if (j == sub_len)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
