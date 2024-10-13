/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/13 13:05:43 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exceve_bulting(char *str)
{
    int i;

    i =  1;
    if (strncmp(str, "echo", 4) == 0) {
        return(0);
    }
    if (strncmp(str, "env", 3) == 0) {
       return(0);
    }
    if (strncmp(str, "unset", 5) == 0) {
        return(0);
    }    
    if (strncmp(str, "export", 6) == 0) {
       return(0);
    }
    if (strncmp(str, "cd", 2) == 0) {
       return(0);
    }
    if (strncmp(str, "pwd", 3) == 0) {
       return(0);
    }
    // if (strncmp(cmd->cmd_and_args[0], "exit",4) == 0) {
    //     // exit(EXIT_SUCCESS);
    // }
    return(1);
}

