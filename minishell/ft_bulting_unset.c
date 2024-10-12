/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:43:21 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/12 16:10:43 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// void    bulting_unset(t_cmd *cmd, t_env *list)
// {
//     //1) il faut cherche dans l'environnement
//     char  **tmp = cmd->cmd_and_args;
//     int x = 1;
//     while(tmp[x])
//     {
//         if(ft_search_envp(&env, cmd->cmd_and_args[x])==0)
//         {
//             printf("\nVariables not exist\n");
//         }
//         else 
//         {
//             printf("\nJe dois deleat\n");
//             ft_delete_unset(env, cmd->cmd_and_args[x]);
//             	//print_env(list->env);
//         }
//         x++;
//     }
// }

int   ft_search_envp(char  **env, char *search)
{
    //IL va falloir faire attention si il y a plusieurs argumment
    (void)search;
    char *key;
    int x;

    x = 0;
    key = ft_copy_start(search, '=');//A inserer dans ma libft
    printf("Je suis search|%s|", key);
    while(env[x])
    {
        if (strncmp(env[x], search, ft_strlen(search)) == 0)
        {
            return(1);
        }
        x++;
    }
    return(0);

}



