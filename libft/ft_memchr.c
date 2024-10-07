/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:52:23 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/01 18:14:47 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*scp;
	unsigned char	ccp;

	scp = (unsigned char *)s;
	ccp = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*scp == ccp)
			return ((void *)scp);
		i++;
		scp++;
	}
	return (NULL);
}
