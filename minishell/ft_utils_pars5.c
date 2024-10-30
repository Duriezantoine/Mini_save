/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pars5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:14:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 12:29:10 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *dest, char src)
{
	char	*original_dest;

	original_dest = dest;
	while (*dest != '\0')
	{
		dest++;
	}
	*dest = src;
	dest++;
	*dest = '\0';
	return (original_dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	char	*original_dest;

	original_dest = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (original_dest);
}

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
