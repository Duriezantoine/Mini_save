/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/15 10:05:07 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exceve_bulting(char *str, int i)
{

    if (strncmp(str, "echo", 4) == 0) {
      // printf("\n0\n");
        return(0);
    }
    if (strncmp(str, "env", 3) == 0) {
            // printf("\n1\n");
       return(0);
    }
    if (strncmp(str, "unset", 5) == 0 && i==0) {
            // printf("\n3\n");

        return(0);
    }    
    if (strncmp(str, "export", 6) == 0 && i==0) {
            // printf("\n4\n");

       return(0);
    }
    if (strncmp(str, "cd", 2) == 0) {
            // printf("\n5\n");

       return(0);
    }
    if (strncmp(str, "pwd", 3) == 0) {
            // printf("\n6\n");

       return(0);
    }
    // if (strncmp(cmd->cmd_and_args[0], "exit",4) == 0) {
    //     // exit(EXIT_SUCCESS);
    // }
    return(1);
}

