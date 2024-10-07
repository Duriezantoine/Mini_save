/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:24:38 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/10 18:08:13 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *str, int fd)
{
	int	ret;

	ret = ft_putstr_fd(str, fd);
	ret += ft_putchar_fd('\n', fd);
	return (ret);
}
