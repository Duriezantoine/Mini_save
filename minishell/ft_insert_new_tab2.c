/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_new_tab2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:52:45 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 15:53:31 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_copy_strings(char **new_arr, char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
		{
			while (i > 0)
				free(new_arr[--i]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_free_new_array(char **new_arr, int size)
{
	while (size > 0)
		free(new_arr[--size]);
	free(new_arr);
}

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_add_new_string(char **new_arr, char *str, int size)
{
	new_arr[size] = ft_strdup(str);
	if (!new_arr[size])
	{
		while (size > 0)
			free(new_arr[--size]);
		return (0);
	}
	new_arr[size + 1] = NULL;
	return (1);
}
