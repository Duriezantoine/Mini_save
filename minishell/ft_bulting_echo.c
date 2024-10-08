/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:51:35 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/06 17:52:46 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    bulting_echo(t_cmd *cmd, int i)
{
    (void)cmd;
     if (ft_search_n(cmd, i)== 0)
        bulting_echo(cmd, i+1);
    else
        {
            while(cmd->cmd_and_args[i] )
            {
                printf("%s", cmd->cmd_and_args[i]);
                i++;
            }
        }    
}

int ft_search_n(t_cmd *cmd, int i)
{
    int x;
    x = 0;
    while(cmd->cmd_and_args[i][x])
    {
        if (cmd->cmd_and_args[i][x]== '-' && cmd->cmd_and_args[i][x+1] == 'n')
            x = x+2;
        else 
            return(1);
        while(cmd->cmd_and_args[i][x]== 'n')
           x++;
    }
    if (cmd->cmd_and_args[i][x]== '\0')
    {
        printf("\nJe suis a la fin de l'atguments\n");
        return(0);
    }
    return(1);
}