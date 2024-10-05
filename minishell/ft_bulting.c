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

void sort_envp(t_env **env) {
    t_env *current, *index;
    char *tmp_key;
    char *tmp_value;

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
void bulting_env(t_cmd *cmd, t_node *list) {
    (void)cmd;
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

int   ft_search_envp(t_env *env, char *search)
{
    //IL va falloir faire attention si il y a plusieurs argumment
    t_env *tmp = env;
    (void)search;
    while(tmp)
    {
        if (strncmp(tmp->key, search, ft_strlen(search)) == 0)
        {
            return(1);
        }
        tmp = tmp->next;
    }
    return(0);

}

void   ft_delete_unset(t_env *env, char *search)
{   
    //Attention il faut faire une conditition si elle existe mais on peux pas la supprimer
    t_env *tmp = env;
    (void)search;

    while(tmp)
    {
        //Conditions permettant ce que je dois remplace
        if (strncmp(tmp->key, search, ft_strlen(search)) == 0)
        {
            if (tmp->next != NULL) 
            {
                free(tmp->value);
                free(tmp->key);
                tmp =tmp->next;
            } 
            else
             { //la fin de la liste
                free(tmp->value);
                free(tmp->key);
                tmp = NULL;
            }
        }
        tmp = tmp->next;
    }
}

void    bulting_unset(t_cmd *cmd, t_node *list)
{
    //1) il faut cherche dans l'environnement
    char  **tmp = cmd->cmd_and_args;
    int x = 1;
    while(tmp[x])
    {
        if(ft_search_envp(list->env, cmd->cmd_and_args[x])==0)
        {
            printf("\nVariables not exist\n");
        }
        else 
        {
            printf("\nJe dois deleat\n");
            ft_delete_unset(list->env, cmd->cmd_and_args[x]);
            	//print_env(list->env);

        }
        x++;
    }
}

int ft_verif_export_space(char *str)
{
    int x;

    x = 0;
    while(str[x])
    {
        if (ft_isalnum(x)==1)
            return(1);
        if (str[x] == '=')
            break;
        x++;
    }
    return(0);
}

int     ft_verif_export(char *str)
{
    if (ft_verif_export_equal(str)==0)
    {
        return(0);
    }
    if(ft_verif_export_space(str)==1)
    {

        printf("\nft_verif_export_equal\n");
        return(0);
    }
    return(1);
}

// void    ft_insert_envp(char *str, t_env env)
// {
//     (void) env;
//     (void)str;
//     printf("\n Je suis ce que je dois inserer\n");

// }

int     ft_verif_export_equal(char *str)
{
    int x;

    x = 0;
    //Cette fonction permet de savoir si la commande est bonne 
    while (str[x])//Verification si il y a un egal ou non
    {
        if(str[x]=='=')
            return(1);
        x++;
    } 
    return(0);

}

void    bulting_export(t_cmd *cmd, t_env *env)
{
    (void)env;
    (void)cmd;
    char **tmp = cmd->cmd_and_args;
    int x = 1;
    while(tmp[x])
    {
        if(ft_verif_export(tmp[x])==0)
            printf("NOT VALID");
        else
            {
                if(ft_search_envp(env, tmp[x])==0)
                {

                    printf("\nVariables not exist\n");//Je dois donc la mettre a la creer et l'inserer
                    // ft_insert_envp(env, tmp[x]);
                }
                else 
                {
                    printf("\nJe dois Modifier la variable deje existante\n");
                        //print_env(list->env);
                }

            }
        x++;
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