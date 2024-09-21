/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/29 17:24:46 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_init_data(t_data **data, t_node *list)
{
    *data = malloc(sizeof(t_data));
    if (data == NULL)
    {
        fprintf(stderr, "Memory allocation failed for data\n");
        exit(1);
    }
    list = malloc(sizeof(t_node));
    if (data == NULL)
    {
        fprintf(stderr, "Memory allocation failed for data\n");
        exit(1);
    }
    list->arg = NULL;
    list->cmd = NULL;
    list->save[0] = dup(STDIN_FILENO);
    list->save[1] = dup(STDOUT_FILENO);
    list->pipe[0] = -1;
}
void ft_init_echo_malloc(t_echo **data_echo)
{
    (*data_echo)->str_w_quot = malloc((*data_echo)->w_quot * sizeof(t_str));
    (*data_echo)->str_s_quot = malloc((*data_echo)->s_quot * sizeof(t_str));
    // printf("\nFT_init echo malloc|w=%d|s=%d||\n",(*data_echo)->w_quot, (*data_echo)->s_quot);
}
t_arg *ft_init_list(t_node *list, t_echo **data_echo)
{
    (void)list;
    t_arg *arg ;
    // 1 er chose il faut commencer par malloc
    if (arg == NULL || data_echo == NULL || list == NULL)
    {
        fprintf(stderr, "Erreur : paramètres invalides\n");
    }

    // 2 eme chose il faut initialiser les variables
    arg->str_command = NULL;
    arg->type = 0;
    arg->prev = NULL;
    arg->next = NULL;
    // 3 eme chose il faut inserer les données

    // ft_insert_list(list, data_echo);
    return (arg);
}
