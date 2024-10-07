/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex_math.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:41:47 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/08 21:23:20 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

struct s_complex	ft_complex_add(struct s_complex a, struct s_complex b)
{
	struct s_complex	c;

	c.r = a.r + b.r;
	c.i = a.i + b.i;
	return (c);
}

struct s_complex	ft_complex_sub(struct s_complex a, struct s_complex b)
{
	struct s_complex	c;

	c.r = a.r - b.r;
	c.i = a.i - b.i;
	return (c);
}

struct s_complex	ft_complex_mul(struct s_complex a, struct s_complex b)
{
	struct s_complex	c;

	c.r = a.r * b.r - a.i * b.i;
	c.i = a.r * b.i + a.i * b.r;
	return (c);
}

struct s_complex	ft_complex_div(struct s_complex a, struct s_complex b)
{
	struct s_complex	c;
	double				denom;

	denom = b.r * b.r + b.i * b.i;
	c.r = (a.r * b.r + a.i * b.i) / denom;
	c.i = (a.i * b.r - a.r * b.i) / denom;
	return (c);
}
