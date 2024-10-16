/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/16 17:40:33 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exceve_bulting(char *str, int len)
{
	if (str == NULL)
		return (0);

    if (strncmp(str, "echo", 5) == 0) {
      // printf("\n0\n");
		return(0);
    }
    if (strncmp(str, "env", 4) == 0) {
	    // printf("\n1\n");
       return(0);
    }
    if (strncmp(str, "unset", 6) == 0 && len==1) {
	    // printf("\n3\n");

		return(0);
    }    
    if (strncmp(str, "export", 7) == 0 && len==1) {
	    // printf("\n4\n");

       return(0);
    }
    if (strncmp(str, "cd", 3) == 0) {
	    // printf("\n5\n");

       return(0);
    }
    if (strncmp(str, "pwd", 4) == 0) {
	    // printf("\n6\n");

       return(0);
    }
    if (strncmp(str, "exit", 5) == 0 && len==1) {
	    // printf("\n6\n");

       return(0);
    }
    // if (strncmp(cmd->cmd_and_args[0], "exit",4) == 0) {
    //     // exit(EXIT_SUCCESS);
    // }
    return(1);
}

