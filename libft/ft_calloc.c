/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:33:03 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/06 21:29:51 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

#define FT_CALLOC_MAX 0xEFFFFFFF

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0)
		if (nmemb > FT_CALLOC_MAX / size)
			return (NULL);
	if (nmemb != 0)
		if (size > FT_CALLOC_MAX / nmemb)
			return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
