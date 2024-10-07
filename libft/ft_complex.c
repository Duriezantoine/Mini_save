/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:38:11 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/08 21:23:08 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

struct s_complex	ft_complex_create(double real, double imag)
{
	struct s_complex	clx;

	clx.r = real;
	clx.i = imag;
	return (clx);
}
