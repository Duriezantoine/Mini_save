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

void free_t_str(t_str *str) {
    if (str != NULL) {
        if (str->str != NULL) {
            free(str->str);
        }
        free(str);
    }
}

void     ft_free_data_echo(t_echo *data_echo)
{
    int i;
    int iterateur_w;
    int iterateur_s;
    i = 0;

        while (++i < data_echo->w_quot + data_echo->s_quot)//Bonne pratique
    {
        iterateur_s = 0;
        while (iterateur_s < data_echo->s_quot)
        {
            if (data_echo->str_s_quot[iterateur_s].order == i)
                printf("FREE|%s|\n",data_echo->str_w_quot[iterateur_s].str );
                
                // free_t_str(data_echo->str_w_quot[iterateur_s]);
            iterateur_s++;
        }
        iterateur_w = 0;
        while (iterateur_w < data_echo->w_quot)
        {
            if (data_echo->str_w_quot[iterateur_w].order == i)
                // ft_insert_data_data_echo_w(save, data_echo, iterateur_w);
            iterateur_w++;
        }
    }
    // free_t_str(echo->str_s_quot);


}
void ft_free_arg(t_arg *tmp)
{
    t_arg *next_tmp;

    while (tmp != NULL) {
        next_tmp = tmp->next;
        if (tmp->str_command != NULL) {
            free(tmp->str_command);
        }
        free(tmp);
        tmp = next_tmp;
    }
}

void ft_free_cmd(char *cmd)
{
    if (cmd != NULL) {
        free(cmd);
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
        // ft_free_cmd(current->cmd);
        free(current);
        current = next;
    }
}

