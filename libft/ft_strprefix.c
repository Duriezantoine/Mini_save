/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:54:13 by tdelage           #+#    #+#             */
/*   Updated: 2023/12/20 19:54:14 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strprefix(char *s, char *prefix)
{
	size_t	slen;
	size_t	plen;
	size_t	i;

	i = 0;
	if (s == NULL || prefix == NULL)
		return (0);
	slen = ft_strlen(s);
	plen = ft_strlen(prefix);
	if (plen > slen)
		return (0);
	while (i < plen)
	{
		if (s[i] != prefix[i])
			return (0);
		i++;
	}
	return (1);
}
