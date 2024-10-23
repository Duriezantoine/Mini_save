/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:48:02 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/23 14:50:02 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int bulting_env( t_node *list)
{
    t_env *tmp;
    t_env *current;

    tmp = copy_env(list->env);
    sort_envp(&tmp);
    current = tmp;
    while (current != NULL)
    {
        if (current->value)
            printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    current = tmp;
    while (current != NULL) {
        t_env *next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    return (0);
}

void sort_envp(t_env **env) 
{
    t_env *current, *index;
    char *tmp_key;
    char *tmp_value;

    for (current = *env; current != NULL; current = current->next) 
    {
        for (index = current->next; index != NULL; index = index->next) 
        {
            if (strcmp(current->key, index->key) > 0) 
            {
                // Échanger les clés
                tmp_key = current->key;
                current->key = index->key;
                index->key = tmp_key;

                // Échanger les valeurs
                tmp_value = current->value;
                current->value = index->value;
                index->value = tmp_value;
            }
        }
    }
}

t_env *copy_env(t_env *env) 
{
    t_env *copy = NULL;
    t_env *current = env;
    t_env *prev = NULL;

    while (current != NULL) {
        t_env *new_node = (t_env *)malloc(sizeof(t_env));
        if (new_node == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        new_node->key = strdup(current->key);
        if (current->value)
            new_node->value = strdup(current->value);
        else
            new_node->value = NULL;
        new_node->next = NULL;
        if (copy == NULL) 
            copy = new_node;
         else 
            prev->next = new_node;
        prev = new_node;
        current = current->next;
    }
    return copy;
}
