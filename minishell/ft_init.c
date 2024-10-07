/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/07 21:38:38 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_init_data_list(t_node **list)
{
    *list = malloc(sizeof(t_node));
    if (list == NULL)
    {
        fprintf(stderr, "Memory allocation failed for data\n");
        exit(1);
    }
    (*list)->arg = NULL;
    (*list)->cmd = NULL;
    (*list)->env = NULL;
    (*list)->save[0] = dup(STDIN_FILENO);
    (*list)->save[1] = dup(STDOUT_FILENO);
    (*list)->pipe[0] = -1;
    (*list)->prev = NULL;
    (*list)->next = NULL;
}

void ft_init_data(t_data ***data, t_node *list)
{
    (**data) = ft_calloc(1, sizeof(t_data));
    (**data)->count = '1';

    if ((**data) == NULL)
    {
        fprintf(stderr, "Memory allocation failed for data\n");
        exit(1);
    }
    (void)list;
}

void ft_init_echo_malloc(t_echo *data_echo)
{
    data_echo->str_w_quot = malloc(data_echo->w_quot * sizeof(t_str));
    data_echo->str_s_quot = malloc(data_echo->s_quot * sizeof(t_str));
    // printf("\nFT_init echo malloc|w=%d|s=%d||\n",data_echo->w_quot, data_echo->s_quot);
}

t_arg *ft_init_list(t_node *list, t_echo *data_echo, t_save *save)
{
    (void)data_echo; // Supprimer l'avertissement d'utilisation inutilisée
    t_arg *new_node = ft_calloc(sizeof(t_arg), 1);
    if (!new_node)
    {
        printf("Erreur d'allocation de mémoire\n");
        return NULL;
    }
    // printf("\nDNEWNODE = |%s|\n",save->str);
    new_node->str_command = ft_strdup(save->str);
    // printf("\nFNEWNODE = |%s|\n", new_node->str_command);

    new_node->quot = save->bool;
    new_node->type = -1;

    if (!new_node->str_command)
    {
        printf("Erreur de duplication de chaîne\n");
        free(new_node);
        return NULL;
    }

    // printf("Voila ce que je viens d'introduire: |%s|\n", new_node->str_command);
    new_node->next = NULL;
    if (list==NULL)
    {
        printf("\nCa beug\n");
    }
    if (list->arg == NULL)
    {
//         printf("\n  Je suis le 1 , NEW_NODE %s\n", new_node->str_command);
        list->arg = new_node;
        list->arg->prev = NULL;
    }
    else
    {
//         printf("\n  Je suis le 2 , NEW_NODE %s\n", new_node->str_command);
        t_arg *tmp = list->arg;

        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new_node;
        new_node->prev = tmp;
    }
    return list->arg;
}
