/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:51:35 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/12 12:18:42 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    bulting_echo(char **cmd, int i)
{
    (void)cmd;
     if (ft_search_n(cmd, i)== 0)
        bulting_echo(cmd, i+1);
    else
        {
            while(cmd[i] )
            {
                printf("%s", cmd[i]);
                i++;
            }
        }    
}

int ft_search_n(char **cmd, int i)
{
    int x;
    x = 0;
    while(cmd[i][x])
    {
        if (cmd[i][x]== '-' && cmd[i][x+1] == 'n')
            x = x+2;
        else 
            return(1);
        while(cmd[i][x]== 'n')
           x++;
    }
    if (cmd[i][x]== '\0')
    {
        printf("\nJe suis a la fin de l'atguments\n");
        return(0);
    }
    return(1);
}