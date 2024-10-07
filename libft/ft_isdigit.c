/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:07:06 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/15 14:32:00 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file ft_isdigit.c

#include "libft.h"

/**
 * @brief verify if a character is a letter digit
 * @param c the character in ascii
 * @return a boolean integer
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
