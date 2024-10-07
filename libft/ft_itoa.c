/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 05:43:32 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/15 14:19:41 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_sign(int n, int *sign, int *inc)
{
	if (n < 0)
	{
		*sign = 1;
		(*inc)++;
		return (-n);
	}
	*sign = 0;
	return (n);
}

static unsigned int	get_len(unsigned int nd)
{
	unsigned int	i;

	i = 0;
	while (nd)
	{
		nd /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				i;
	int				sign;
	unsigned int	nd;
	char			*ret;

	i = 0;
	sign = 0;
	nd = get_sign(n, &sign, &i);
	i += get_len(nd);
	if (n == 0)
		return (ft_strdup("0"));
	ret = (char *)ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	if (sign)
		ret[0] = '-';
	while (nd)
	{
		ret[--i] = nd % 10 + '0';
		nd /= 10;
	}
	return (ret);
}
