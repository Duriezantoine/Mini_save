/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:35:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/03 15:46:46 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exceve_bulting(t_cmd *cmd, t_node *list)
{
    int i;

    i =  1;
    if (strncmp(cmd->cmd_and_args[0], "echo", 4) == 0) {
        bulting_echo(cmd, i);
    }
    if (strncmp(cmd->cmd_and_args[0], "env", 3) == 0) {
        bulting_env(cmd, list);
    }
    if (strncmp(cmd->cmd_and_args[0], "unset", 5) == 0) {
        bulting_unset(cmd, list);
    }    
      if (strncmp(cmd->cmd_and_args[0], "export", 6) == 0) {
        bulting_export(cmd,list->env);
    }
}

void    ft_exceve(t_node *list, t_data *data)
{
    (void)list;
    (void)data;
    t_cmd *tmp = list->cmd;
    while(tmp)
    {
        if (tmp->is_builtin==1)
            ft_exceve_bulting(tmp, list);
        tmp = tmp->next;
    }

}