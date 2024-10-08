/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:35:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/08 15:11:36 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int    ft_exceve(t_node *list, t_data *data, t_env **env)
{
    (void)list;
    (void)data;
    t_cmd *tmp ;
    tmp = list->cmd;
    while(tmp)
    {
        if (tmp->is_builtin==1)
            ft_exceve_bulting(tmp, list, &env);
        tmp = tmp->next;
    }
    printf("CMD= %s| ", list->cmd->cmd_and_args[0]);
    if ( list->cmd->cmd_and_args[0] != NULL)
         if(strncmp(list->cmd->cmd_and_args[0], "exit", ft_strlen(list->cmd->cmd_and_args[0])) == 0) 
              return 1;
    return 0;

}
