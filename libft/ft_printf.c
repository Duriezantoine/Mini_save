/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:07:07 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/10 19:03:59 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_vfprintf(int fd, const char *fmt, va_list lst)
{
	size_t	fmt_len;
	size_t	i;
	size_t	ret;
	int		tmp;

	if (!fmt)
		return (-1);
	fmt_len = ft_strlen(fmt);
	i = 0;
	ret = 0;
	while (i < fmt_len)
	{
		if (fmt[i] == '%')
		{
			tmp = print_printf_specials(fd, fmt + i, lst, &i);
			if (tmp == -1)
				return (-1);
			ret += tmp;
		}
		else
			ret += ft_putchar_fd(fmt[i], fd);
		i++;
	}
	return (ret);
}

int	ft_fprintf(int fd, const char *fmt, ...)
{
	va_list	lst;
	int		ret;

	va_start(lst, fmt);
	ret = ft_vfprintf(fd, fmt, lst);
	va_end(lst);
	return (ret);
}

int	ft_vprintf(const char *fmt, va_list lst)
{
	return (ft_vfprintf(STDOUT, fmt, lst));
}

int	ft_printf(const char *fmt, ...)
{
	va_list	lst;
	int		ret;

	va_start(lst, fmt);
	ret = ft_vprintf(fmt, lst);
	va_end(lst);
	return (ret);
}
