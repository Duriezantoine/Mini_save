/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:35:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/07 20:17:11 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int    ft_exceve(t_node *list, t_data *data, t_env **env)
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
    if(ft_strcmp(list->cmd->cmd_and_args[0], "exit") == 0) return 1;
                    return 0;

}
