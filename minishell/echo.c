/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:17:00 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/24 12:48:10 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(t_data *data)
{
	int		i;

	i = 1;
	if (ft_strcmp(data->arg[1], "-n"))
		i = 2;
	while (data->arg[i])
	{
		printf("%s", data->arg[i]);
		i++;
		if (data->arg[i])
			printf(" ");
	}
}

void	ft_echo(t_data *data)
{
	if (!data->arg[1])
	{
		printf("\n");
		return ;
	}
	else if (ft_strcmp(data->arg[1], "-n"))
	{
		print_echo(data);
		return ;
	}
	print_echo(data);
	printf("\n");
}

