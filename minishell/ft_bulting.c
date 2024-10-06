/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/06 19:04:12 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exceve_bulting(t_cmd *cmd, t_node *list, t_env ***env)
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
        bulting_export(cmd,list, *env);
    }
    if (strncmp(cmd->cmd_and_args[0], "cd", 2) == 0) {
        bulting_cd(cmd,list,  *env);
    }
    if (strncmp(cmd->cmd_and_args[0], "pwd", 3) == 0) {
        bulting_pwd();
    }
}

