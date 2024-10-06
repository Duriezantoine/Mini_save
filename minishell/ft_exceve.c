/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:35:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/06 19:09:38 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void    ft_exceve(t_node *list, t_data *data, t_env **env)
{
    (void)list;
    (void)data;
    t_cmd *tmp = list->cmd;
    while(tmp)
    {
        if (tmp->is_builtin==1)
            ft_exceve_bulting(tmp, list, &env);
        tmp = tmp->next;
    }

}