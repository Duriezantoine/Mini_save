/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:41:37 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/01 18:02:35 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strlcat_copy_loop(char **dst, char **src, size_t *capa)
{
	while (**src)
	{
		if (*capa != 1)
		{
			**dst = **src;
			(*dst)++;
			(*capa)--;
		}
		else
			break ;
		(*src)++;
	}
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*src_cp;
	char	*dst_cp;
	size_t	size_cp;
	size_t	dest_len;
	size_t	n;

	src_cp = (char *)src;
	dst_cp = dst;
	size_cp = size;
	while (size_cp-- != 0 && *dst_cp != 0)
		dst_cp++;
	dest_len = dst_cp - dst;
	n = size - dest_len;
	if (n == 0)
		return (dest_len + ft_strlen(src));
	ft_strlcat_copy_loop(&dst_cp, &src_cp, &n);
	*dst_cp = 0;
	return (dest_len + ft_strlen(src));
}
