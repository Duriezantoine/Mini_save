/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <tdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:00:17 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/15 20:25:05 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_countof(char *str, char c)
{
	size_t	i;
	size_t	number;

	i = 0;
	number = 0;
	while (str[i])
	{
		if (str[i] == c)
			number++;
		i++;
	}
	return (number);
}

size_t	ft_countofnot(char *str, char c)
{
	size_t	i;
	size_t	number;

	i = 0;
	number = 0;
	while (str[i])
	{
		if (str[i] != c)
			number++;
		i++;
	}
	return (number);
}

void	ft_count(char *str, char c, size_t *of, size_t *ofnt)
{
	*of = ft_countof(str, c);
	*ofnt = ft_countofnot(str, c);
}
