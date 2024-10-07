/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:51:36 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/07 21:33:57 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void     ft_free_data_echo(t_echo *data_echo)
{
        int i = 0;
        while(i < data_echo->s_quot) {
                free(data_echo->str_s_quot[i].str);
                i++;
        }
        i = 0;
        while(i < data_echo->w_quot) {
                free(data_echo->str_w_quot[i].str);
                i++;
        }
        free(data_echo->str_s_quot);
        free(data_echo->str_w_quot);
}
void ft_free_arg(t_arg *tmp)
{
    t_arg *next_tmp;

    while (tmp != NULL) {
        next_tmp = tmp->next;
        free(tmp->str_command);
        free(tmp);
        tmp = next_tmp;
    }
}

void free_dt_c(char **dt) {
        int i = 0;
        if(!dt) return;
        while(dt[i] != NULL) {
                free(dt[i]);
                i++;
        }
        free(dt);
}

void ft_free_cmd(t_cmd *tmp)
{
    t_cmd *next_tmp;

    while (tmp != NULL) {
        next_tmp = tmp->next;
        if (tmp->cmd_and_args != NULL) {
            free_dt_c(tmp->cmd_and_args);
        }
        free(tmp);
        tmp = next_tmp;
    }
}

void free_node(t_node *list, t_data *data)
{
    t_node *current = list;
    t_node *next;

    // Sauvegarder l'environnement
    if (data != NULL) {
        free(data);
    }

    // printf("\nJe passe ici\n");

    while (current != NULL) {
        next = current->next;
        ft_free_arg(current->arg);
        ft_free_cmd(current->cmd);
        free(current);
        current = next;
    }
}

