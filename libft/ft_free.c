/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:23:50 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/15 08:27:11 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>
#include <stdarg.h>

static void	ft_free_impl(char code, t_free_function f, const char *fmt,
		va_list ap)
{
	int						i;
	int						c;
	static t_free_function	funcs[256] = {0};

	if (fmt == NULL)
	{
		funcs[(int)code] = f;
		return ;
	}
	i = -1;
	while (fmt[++i])
	{
		c = fmt[i];
		if (funcs[c] != NULL)
			funcs[c](va_arg(ap, void *));
	}
}

void	ft_free(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	ft_free_impl(0, NULL, fmt, ap);
	va_end(ap);
}

void	ft_free_register(char c, t_free_function f)
{
	ft_free_impl(c, f, NULL, NULL);
}
