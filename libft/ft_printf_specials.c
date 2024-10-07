/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specials.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:06:34 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/01 02:16:21 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_handlers.h"
#include "ft_printf.h"

int	print_printf_specials_next(int fd, const char *fmt, va_list lst,
		size_t *index)
{
	if (fmt[1] == 'x')
		return (ft_printf_puthex(fd, (int)va_arg(lst, int), 0, index));
	if (fmt[1] == 'X')
		return (ft_printf_puthex(fd, (int)va_arg(lst, int), 1, index));
	return (ft_putchar_fd(fmt[*index], fd));
}

int	print_printf_specials(int fd, const char *fmt, va_list lst, size_t *index)
{
	(void)lst;
	if (fmt[1] == '\0')
		return (-1);
	if (fmt[1] == '%')
		return (ft_printf_print_percent(fd, index));
	if (fmt[1] == 'c')
		return (ft_printf_putchar(fd, (char)va_arg(lst, int), index));
	if (fmt[1] == 's')
		return (ft_printf_putstr(fd, (char *)va_arg(lst, char *), index));
	if (fmt[1] == 'p')
		return (ft_printf_putptr(fd, (void *)va_arg(lst, void *), index));
	if (fmt[1] == 'd' || fmt[1] == 'i')
		return (ft_printf_putint(fd, (int)va_arg(lst, int), index));
	if (fmt[1] == 'u')
		return (ft_printf_putuint(fd, (unsigned int)va_arg(lst, int), index));
	return (print_printf_specials_next(fd, fmt, lst, index));
}
