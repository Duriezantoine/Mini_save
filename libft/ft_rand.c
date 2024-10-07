/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <tdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:47:12 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/22 18:53:07 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	gen_bit_shift_rng(unsigned int seed, unsigned int keys[5])
{
	int	t1;
	int	t2;
	int	t3;

	t1 = (seed << 20) ^ (seed >> 7);
	t2 = (t1 >> 13) ^ ((seed << 6) ^ t1);
	t3 = t1 ^ (t2 >> 10) ^ (seed << 5) * 2;
	keys[0] = (t3 >> 12) ^ (t2 << 2);
	keys[1] = (t3 << 18) ^ t1;
	keys[2] = t1 ^ t2 ^ t3;
	keys[3] = ((seed ^ t1) << 24) ^ t3;
	keys[4] = keys[3] ^ (t2 << 12);
}

static unsigned int	ft_rrand(int init, unsigned int seed, unsigned int min,
		unsigned int max)
{
	static unsigned int	m_seed;
	unsigned int		key[5];
	int					range;

	range = max - min + 1;
	if (init)
	{
		m_seed = seed;
		return (m_seed);
	}
	gen_bit_shift_rng(m_seed, key);
	m_seed = key[0] ^ (key[1] << 13) ^ (key[2] >> 5) ^ key[3];
	m_seed ^= key[4] << (key[2] ^ key[1]) % 15;
	m_seed >>= 3;
	m_seed ^= key[2] ^ key[4];
	return ((m_seed % (range)) + min);
}

void	ft_srand(unsigned int seed)
{
	if (seed == 0)
		seed = 1;
	ft_rrand(1, seed, 0, 0);
}

int	ft_rand(int a, int b)
{
	unsigned int	umin;
	unsigned int	umax;

	if (a == b)
		return (a);
	if (a > b)
	{
		a += b;
		b = a - b;
		a = a - b;
	}
	if (a < 0)
	{
		umin = -a;
		umax = b + umin;
		return (ft_rrand(0, 0, 0, umax) - umin);
	}
	return (ft_rrand(0, 0, a, b));
}
