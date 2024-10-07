/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:43:22 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/03 20:49:24 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		j;
	char	*ret;

	j = 0;
	i = 0;
	while (src[i++])
		;
	ret = (char *)ft_calloc(i, sizeof(char));
	if (!ret)
		i = -1;
	while (j < i)
	{
		ret[j] = src[j];
		j++;
	}
	return (ret);
}
