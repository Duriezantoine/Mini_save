/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:05:36 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/23 17:58:40 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

long	ft_strtol(char *str, char **endptr)
{
	long	res;
	short	sign;

	if (!str || *str == '\0')
		return (0);
	while ((*str >= 8 && *str <= 12) || *str == ' ')
		str++;
	sign = 1;
	res = 0;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		if ((sign == 1 &&  res > (LONG_MAX - (*str - '0')) / 10)
			|| (sign == -1 && -res < (LONG_MIN + (*str - '0')) / 10))
			break;
		else
			res = res * 10 + (*str - '0');
		str++;
	}
	*endptr = str;
	return (res * sign);
}

int bulting_exit(char **args, t_node *list, t_env **env, t_data *data)
{
    (void) env;
    (void) list;
    long exit_status;
    char *endptr;

    if (args[1] == NULL)
		return (data->exit_code);

	exit_status = ft_strtol(args[1], &endptr);
	
	if (*endptr != '\0' || endptr == args[1]) 
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return 2;
	}

	if (args[2] != NULL)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return 1;
	}
	else
		return (exit_status & 255);
}
