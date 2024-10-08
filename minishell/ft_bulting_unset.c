/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:43:21 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/08 15:11:55 by aduriez          ###   ########.fr       */
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

void    bulting_unset(t_cmd *cmd, t_node *list)
{
    //1) il faut cherche dans l'environnement
    char  **tmp = cmd->cmd_and_args;
    int x = 1;
    while(tmp[x])
    {
        if(ft_search_envp(&list->env, cmd->cmd_and_args[x])==0)
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

int   ft_search_envp(t_env **env, char *search)
{
    //IL va falloir faire attention si il y a plusieurs argumment
    t_env *tmp = *env;
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



