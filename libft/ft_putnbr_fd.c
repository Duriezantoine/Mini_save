/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 05:41:50 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/10 19:37:32 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

static char	get_int(int n, int up)
{
	static const char	all_chars[] = "0123456789abcdef0123456789ABCDEF";

	return (all_chars[n + (up * 16)]);
}

static int	ft_putnbr_buf(unsigned long long int nb, int fd, int radix, int up)
{
	int		pos;
	int		rem;
	char	buf[64];
	int		ret;

	pos = 0;
	while (pos == 0 || nb > 0)
	{
		rem = nb % radix;
		nb /= radix;
		buf[pos++] = get_int(rem, up);
	}
	ret = 0;
	while (--pos >= 0)
	{
		ret += write(fd, &buf[pos], 1);
	}
	return (ret);
}

int	ft_putnbr_fd(long long int nb, int fd, int radix, int up)
{
	int	ret;

	if (nb < 0)
	{
		ret = write(fd, "-", 1);
		ret += ft_putnbr_buf(-nb, fd, radix, up);
	}
	else
		ret = ft_putnbr_buf(nb, fd, radix, up);
	return (ret);
}

int	ft_putunbr_fd(unsigned long long int nb, int fd, int radix, int up)
{
	return (ft_putnbr_buf(nb, fd, radix, up));
}
