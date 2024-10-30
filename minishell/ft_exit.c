/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:51:14 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/25 14:46:47 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (*str != 0)
		i += write(fd, str++, 1);
	return (i);
}

void	ft_out_exit(int i)
{
	if (i == 1)
	{
		ft_putstr_fd("Error arguments", 2);
		exit(2);
	}
	if (i == 2)
	{
		ft_putstr_fd("No environnement", 2);
		exit(2);
	}
	if (i == 3)
	{
		ft_putstr_fd("Memory allocation failed for command", 2);
		exit(1);
	}
	if (i == 4)
	{
		ft_putstr_fd("Error splitting input", 2);
		exit(1);
	}
	if (i == 5)
	{
		ft_putstr_fd("Invalid pointers in ft_parsing_init", 2);
		return ;
	}
}
