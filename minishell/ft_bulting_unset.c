/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:43:21 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/19 11:40:58 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_delete_unset(t_env **env, char *search)
{
    t_env *current;
    t_env *prev;

    if (!env || !*env || !search)
        return;

    current = *env;
    prev = NULL;

    while (current)
    {
        if (strcmp(current->key, search) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;
    
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int    bulting_unset( char ***env, t_cmd *cmd, t_node *list)
{
    //1) il faut cherche dans l'environnement
    char  **tmp = cmd->cmd_and_args;
    int x = 1;
    while(tmp[x])
    {
        if(ft_search_envp((*env), cmd->cmd_and_args[x])==0)
        {
            return(1);
        }
        else 
        {
            ft_delete_unset(&list->env, cmd->cmd_and_args[x]);
        }
        x++;
    }
    return(0);
}

int   ft_search_envp(char  **env, char *search)
{
    //IL va falloir faire attention si il y a plusieurs argumment
    (void)search;
    char *key;
    int x;
    int count;
   char *key_envp;
    x = 0;
    key = ft_copy_start(search, '=');//A inserer dans ma libft
    count = ft_strlen(key);
    while(env[x])
    {
        key_envp = ft_copy_start(env[x], '=');
        if(key[count-1] == '+')
        {
            free(key);
            free(key_envp); 
            // printf("Je retourne 2");    
            return(2);
        }
        // printf("\nKEY_ENVP|%s|SEARCH|%s|\n", key_envp, key);
        if (strncmp(key_envp, key, ft_strlen(search)) == 0)
        {
            free(key);
            free(key_envp); 
            // printf("\nfound\n");
            return(3);
        }
        free(key_envp); 
        x++;
    }
    free(key);
    return(0);

}



