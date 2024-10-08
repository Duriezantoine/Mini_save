/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:51:14 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/08 15:30:08 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_t_echo(t_echo *echo)
{
    if (echo == NULL) return;

    // Libérer la mémoire allouée pour str_w_quot
    if (echo->str_w_quot) {
        if (echo->str_w_quot->str) {
            free(echo->str_w_quot->str);
        }
        free(echo->str_w_quot);
    }

    // Libérer la mémoire allouée pour str_s_quot
    if (echo->str_s_quot) {
        if (echo->str_s_quot->str) {
            free(echo->str_s_quot->str);
        }
        free(echo->str_s_quot);
    }
    // Libérer la mémoire allouée pour la structure t_echo
    free(echo);
}

void print_list(t_node *list)
{
    t_arg *current = list->arg;
    while (current)
    {
        printf("Command: |%s| type ;|%d|\n", current->str_command, current->type);
        current = current->next;
    }
}