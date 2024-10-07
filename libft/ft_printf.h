/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:41:05 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/10 20:41:23 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stddef.h>
# define STDOUT 1

int	ft_vfprintf(int fd, const char *fmt, va_list lst);
int	ft_fprintf(int fd, const char *fmt, ...);
int	ft_vprintf(const char *fmt, va_list lst);
int	ft_printf(const char *fmt, ...);
int	print_printf_specials(int fd, const char *fmt, va_list lst, size_t *index);

#endif // FT_PRINTF_H
