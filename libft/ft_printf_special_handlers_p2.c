/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_special_handlers_p2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:38:11 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/01 02:16:28 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_handlers.h"
#include "ft_printf.h"
#include <unistd.h>

int	ft_printf_putstr(int fd, char *s, size_t *index)
{
	(*index)++;
	if (!s)
		return (ft_putstr_fd("(null)", fd));
	return (ft_putstr_fd(s, fd));
}

int	ft_printf_putptr(int fd, void *s, size_t *index)
{
	int	ret;

	(*index)++;
	if (!s)
		return (ft_putstr_fd("(nil)", fd));
	ret = ft_putstr_fd("0x", fd);
	return (ft_putunbr_fd((unsigned long long)s, fd, 16, 0) + ret);
}
