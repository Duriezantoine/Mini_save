/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/23 18:08:46 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exceve_bulting(char *str, int len)
{
	if (str == NULL)
		return (0);

    if (strncmp(str, "echo", 5) == 0)
		return(0);
    if (strncmp(str, "env", 4) == 0)
       return(0);
    if (strncmp(str, "unset", 6) == 0 && len==1)
		return(0);
    if (strncmp(str, "export", 7) == 0)
       return(0);
    if (strncmp(str, "cd", 3) == 0)
       return(0);
    if (strncmp(str, "pwd", 4) == 0)
       return(0);
    if (strncmp(str, "exit", 5) == 0 )
       return(0);
    return(1);
}

