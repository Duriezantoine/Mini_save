/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:07:00 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/20 11:27:23 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	ret;

	ret = 0;
	while (s[ret++])
		;
	return (ret - 1);
}

size_t	ft_strlenc(const char *s, char c)
{
	int	ret;

	ret = 0;
	while (s[ret] && s[ret++] != c)
		;
	return (ret - 1);
}
