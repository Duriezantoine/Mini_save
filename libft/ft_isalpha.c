/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:07:13 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/15 14:32:15 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file ft_isalpha.c

#include "libft.h"

/**
 * @brief verify if a character is a letter minuscule or majuscule
 * @param c the character ascii code to be
 * @return a boolean integer
 */
int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
