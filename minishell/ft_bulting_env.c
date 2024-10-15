/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:48:02 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/15 08:34:18 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void bulting_env( t_node *list)
{
    // Créer une copie temporaire de la liste t_env
    t_env *tmp = copy_env(list->env);

    // Trier la copie temporaire
    sort_envp(&tmp);

    // Afficher les variables d'environnement triées
    t_env *current = tmp;
    while (current != NULL) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }

    // Libérer la mémoire allouée pour la copie temporaire
    current = tmp;
    while (current != NULL) {
        t_env *next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
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
        new_node->value = strdup(current->value);
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
