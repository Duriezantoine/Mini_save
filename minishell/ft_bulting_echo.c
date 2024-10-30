/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:51:35 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 10:08:47 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bulting_echo(char **cmd, int i)
{
	int	n;

	n = 0;
	if (cmd[i] == NULL)
	{
		if (i == 1)
			write(1, "\n", 1);
		return (0);
	}
	if (ft_search_n(cmd, i) == 0)
		bulting_echo(cmd, i + 1);
	else
	{
		if (i != 1)
			n = 1;
		while (cmd[i])
		{
			write(1, cmd[i], ft_strlen(cmd[i]));
			if (cmd[++i] != NULL)
				write(1, " ", 1);
		}
		if (n != 1)
			write(1, "\n", 1);
	}
	return (0);
}

int	ft_search_n(char **cmd, int i)
{
	int	x;

	x = 0;
	if (cmd[i][x] == '-' && cmd[i][x + 1] == 'n')
	{
		x = x + 2;
		if (cmd[i][x] == '\0')
			return (0);
	}
	else
		return (1);
	while (cmd[i][x] == 'n')
		x++;
	return (cmd[i][x] != '\0');
}
