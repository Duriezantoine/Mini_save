/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_new_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:50:40 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/18 17:10:04 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_add_string_to_array(char **arr, char *str)
{
    int size = ft_get_array_size(arr);
    char **new_arr = ft_allocate_new_array(size);

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
int ft_get_array_size(char **arr)
{
    int size = 0;
    while (arr && arr[size])
        size++;
    return (size);
}
char **ft_allocate_new_array(int size)
{
    char **new_arr = (char **)malloc(sizeof(char *) * (size + 2));
    if (!new_arr)
        return (NULL);
    return (new_arr);
}
int ft_copy_strings(char **new_arr, char **arr, int size)
{
    int i = 0;
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
void ft_free_new_array(char **new_arr, int size)
{
    while (size > 0)
        free(new_arr[--size]);
    free(new_arr);
}
void ft_free_array(char **arr)
{
    int i = 0;
    while (arr && arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}
int ft_add_new_string(char **new_arr, char *str, int size)
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

