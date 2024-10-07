/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:24:45 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/01 02:16:44 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HANDLERS_H
# define FT_HANDLERS_H

# include "ft_structs.h"
# include <stddef.h>

int	ft_printf_print_percent(int fd, size_t *index);
int	ft_printf_putchar(int fd, char c, size_t *index);
int	ft_printf_putstr(int fd, char *s, size_t *index);
int	ft_printf_putptr(int fd, void *s, size_t *index);
int	ft_printf_putint(int fd, int i, size_t *index);
int	ft_printf_putuint(int fd, unsigned int i, size_t *index);
int	ft_printf_puthex(int fd, unsigned int i, int up, size_t *index);

#endif // FT_HANDLERS_H
