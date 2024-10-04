/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:51:36 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/03 15:52:24 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void ft_free_arg(t_arg *tmp)
{
    t_arg *next_tmp;

    while (tmp) {
        next_tmp = tmp->next;
        free(tmp->str_command);
        free(tmp);
        tmp = next_tmp;
    }
}

void ft_free_cmd(t_cmd *tmp)
{
    t_cmd *next_tmp;

    while (tmp) {
        next_tmp = tmp->next;
        // Libérer chaque chaîne de caractères dans cmd_and_args
        if (tmp->cmd_and_args) {
            for (int i = 0; tmp->cmd_and_args[i] != NULL; i++) {
                free(tmp->cmd_and_args[i]);
            }
            free(tmp->cmd_and_args);
        }

        // Libérer l'élément actuel
        free(tmp);

        // Avancer dans la liste
        tmp = next_tmp;
    }
}
void free_node(t_node *list) 
{
//Sauvegarder l'environnement 

(void)list;
printf("\nJe passe ici\n");
while(list)
 {
     ft_free_arg(list->arg);
     ft_free_cmd(list->cmd);
     list = list->next;
 } 
}   

