/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/03 15:56:07 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_search_n(t_cmd *cmd, int i)
{
    int x;
    x = 0;
    while(cmd->cmd_and_args[i][x])
    {
        if (cmd->cmd_and_args[i][x]== '-' && cmd->cmd_and_args[i][x+1] == 'n')
            x = x+2;
        else 
            return(1);
        while(cmd->cmd_and_args[i][x]== 'n')
           x++;
    }
    if (cmd->cmd_and_args[i][x]== '\0')
    {
        printf("\nJe suis a la fin de l'atguments\n");
        return(0);
    }
    return(1);
}
// void	ft_display_envp(t_env *envp)
// {
// 	int	i;

// 	i = 0;
// 	sort_envp(copy_envp);
// 	printf("\n 1er|%s|\n", copy_envp[0]);
// 	while (copy_envp[i])
// 	{
// 		printf("declare -x %s\n", copy_envp[i]);
// 		i++;
// 	}
// }
// void    bulting_export(t_cmd *cmd, t_node *list)
// {
//     //Il permet d'afficher tous l'environnement besoin
//     ft_display_envp(list->env);
    
// }

t_env *copy_env(t_env *env) {
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

        // Copier les valeurs
        int num_values = 0;
        while (current->value[num_values] != NULL) {
            num_values++;
        }
        new_node->value = (char **)malloc((num_values + 1) * sizeof(char *));
        if (new_node->value == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < num_values; i++) {
            new_node->value[i] = strdup(current->value[i]);
        }
        new_node->value[num_values] = NULL;

        new_node->next = NULL;

        if (copy == NULL) {
            copy = new_node;
        } else {
            prev->next = new_node;
        }
        prev = new_node;
        current = current->next;
    }
    return copy;
}

// Fonction pour trier les variables d'environnement
void sort_envp(t_env **env) {
    t_env *current, *index;
    char *tmp_key;
    char **tmp_value;

    for (current = *env; current != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (strcmp(current->key, index->key) > 0) {
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
void bulting_env(t_cmd *cmd, t_node *list) {
    (void)cmd;
    printf("\nJe passe dans le bulting env \n");
    printf("Je suis la première clé |%s|\n", list->env->key);

    // Créer une copie temporaire de la liste t_env
    t_env *tmp = copy_env(list->env);

    // Trier la copie temporaire
    sort_envp(&tmp);

    // Afficher les variables d'environnement triées
    t_env *current = tmp;
    while (current != NULL) {
        printf("%s=", current->key);
        for (int i = 0; current->value[i] != NULL; i++) {
            printf("%s", current->value[i]);
            if (current->value[i + 1] != NULL) {
                printf(",");
            }
        }
        printf("\n");
        current = current->next;
    }

    // Libérer la mémoire allouée pour la copie temporaire
    current = tmp;
    while (current != NULL) {
        t_env *next = current->next;
        free(current->key);
        for (int i = 0; current->value[i] != NULL; i++) {
            free(current->value[i]);
        }
        free(current->value);
        free(current);
        current = next;
    }
}


void    bulting_echo(t_cmd *cmd, int i)
{
    (void)cmd;
     if (ft_search_n(cmd, i)== 0)
        bulting_echo(cmd, i+1);
    else
        {
            while(cmd->cmd_and_args[i] )
            {
                printf("%s", cmd->cmd_and_args[i]);
                i++;
            }
        }    
}