/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_new_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:50:40 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 15:53:39 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_add_string_to_array(char **arr, char *str)
{
	int		size;
	char	**new_arr;

	size = ft_get_array_size(arr);
	new_arr = ft_allocate_new_array(size);
	if (!new_arr)
		return (NULL);
	if (!ft_copy_strings(new_arr, arr, size))
	{
		ft_free_new_array(new_arr, size);
		return (NULL);
	}
	if (!ft_add_new_string(new_arr, str, size))
	{
		ft_free_new_array(new_arr, size + 1);
		return (NULL);
	}
	ft_free_array(arr);
	return (new_arr);
}

int	ft_get_array_size(char **arr)
{
	int	size;

	size = 0;
	while (arr && arr[size])
		size++;
	return (size);
}

char	**ft_allocate_new_array(int size)
{
	char	**new_arr;

	new_arr = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_arr)
		return (NULL);
	return (new_arr);
}
