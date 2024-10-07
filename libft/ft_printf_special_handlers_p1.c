/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_special_handlers_p1.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:23:56 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/10 19:41:03 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_handlers.h"
#include "ft_printf.h"

int	ft_printf_print_percent(int fd, size_t *index)
{
	(*index)++;
	return (ft_putchar_fd('%', fd));
}

int	ft_printf_putchar(int fd, char c, size_t *index)
{
	(*index)++;
	return (ft_putchar_fd(c, fd));
}

int	ft_printf_putint(int fd, int i, size_t *index)
{
	(*index)++;
	return (ft_putnbr_fd((long long int)i, fd, 10, 0));
}

int	ft_printf_putuint(int fd, unsigned int i, size_t *index)
{
	(*index)++;
	return (ft_putunbr_fd((unsigned long long int)i, fd, 10, 0));
}

int	ft_printf_puthex(int fd, unsigned int i, int up, size_t *index)
{
	(*index)++;
	return (ft_putunbr_fd((unsigned long long int)i, fd, 16, up));
}
