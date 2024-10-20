/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:51:35 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/20 14:53:10 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    bulting_echo(char **cmd, int i)
{
    (void)cmd;
    int n;

    n = 0;
    if(cmd[i]== NULL)
    {
        if (i == 1)
            write(1, "\n", 1);
        return(0);
    }
     if (ft_search_n(cmd, i)== 0)
     {
        // printf("ici");
        bulting_echo(cmd, i+1);
     }
    else
        {
            if (i != 1)
                n=1;
            while(cmd[i])
            {
                write(1, cmd[i], ft_strlen(cmd[i]));
                if (cmd[i+1]!= NULL)
                        write(1, " ", 1);
                i++;
            }
            if(n !=1)
                    write(1, "\n", 1);
        }   
    return(0);
}

int ft_search_n(char **cmd, int i)
{
    int x;
    x = 0;
    // int count ;

    // count = 0;
    // while(cmd[i][x])
    // {
    if (cmd[i][x]== '-' && cmd[i][x+1] == 'n')
    {
        x = x+2;
        if (cmd[i][x]== '\0')
        {
            return (0);
        }
    }
    else 
        return(1);
    while(cmd[i][x]== 'n')
        x++;
    // }
    if (cmd[i][x]== '\0')
    {
        // printf("\nJe suis a la fin de l'atguments\n");
        return(0);
    }
    return(1);
}