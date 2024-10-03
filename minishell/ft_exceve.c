/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:35:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/03 15:46:46 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void    ft_exceve(t_node *list, t_data *data)
{
    (void)list;
    (void)data;
    //1 er chose verifier si il n'y a que que une seule boucle 
    // printf("Je suis le nbr de commande |%d|", (*data).nbr_command);
    // if (list->cmd->is_builtin== 1)
    //     ft_builtin(list);
    // printf ("\nNRB_Outfile = |%d| NBR_Infile = |%d| FD_Outfile |%d| FD_Infile|%d|\n", list->cmd->output, list->cmd->output, list->save[1],list->save[0]);
}