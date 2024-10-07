/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsufix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:27:05 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/20 11:27:09 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strsufix(char *s, char *sufix)
{
	size_t	slen;
	size_t	sulen;

	if (s == NULL || sufix == NULL)
		return (0);
	slen = ft_strlen(s);
	sulen = ft_strlen(sufix);
	if (sulen > slen)
		return (0);
	while (sulen > 0)
	{
		if (s[slen - 1] != sufix[sulen - 1])
			return (0);
		slen--;
		sulen--;
	}
	return (1);
}
