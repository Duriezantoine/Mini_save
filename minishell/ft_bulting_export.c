/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:56:21 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/07 22:36:35 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    bulting_export(t_cmd *cmd, t_node *list, t_env **env)
{
    (void)env;
    (void)cmd;
    (void)list;
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
                    ft_delim_envp(env, tmp[x]);
                }

            }
        x++;
    }
}

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

void    ft_delim_envp( t_env **env, char *str)
{
    (void) env;
    (void)str;
    char *key;
    char *value;
    //IL faut faire la difference entre la clef et la valeur
    key = ft_copy_start(str, '=');//A inserer dans ma libft
    value = ft_copy_end(str, '=');//A inserer dans ma libft

    //Creation d'une protection
    if (key == NULL || value == NULL)
    {
        free(key);
        free(value);
        printf("\nCe n'est pas passer ft_insert_envp\n");
        return;
    }
    if(ft_search_key_envp(*env, key)==1)
    {
        printf("\n\n\n ICI JE LA CREE \n\n\n\n");
        ft_insert_envp(env, key, value);
    }
    else
        ft_change_envp(env, key,value);
    free(key);
    free(value);
    // print_env(env);
}

void    ft_change_envp(t_env **env, char *key, char *value)
{
    t_env *tmp;

    tmp = *env;
    while(tmp)
    {
        if (strncmp(tmp->key, key, ft_strlen(key)) == 0) 
        {
            // printf("\n\nJe suis dedans\n \n");
            //Je veux juste la valeur de value est que ca marche
            free(tmp->value);
            tmp->value = ft_strdup(value);
            return;
        }
        tmp = tmp->next;
    }
    return ;
}

int     ft_search_key_envp(t_env *env, char *key)
{
    //Je dois boucler dessus pour determiner si elle est dedans
    t_env *tmp;

    tmp = env;
    while(tmp)
    {
        // printf("\nJe compare |%s|%s|result = |%d|", tmp->key, key,strncmp(tmp->key, key, ft_strlen(key)) );
        if (strncmp(tmp->key, key, ft_strlen(key)) == 0) 
            return 0;
        tmp = tmp->next;
    }
    return(1);

} 
void ft_insert_envp(t_env **env, char *key, char *value)
{
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (new_node == NULL)
    {
        free(key);
        free(value);
        return;
    }

    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = *env;
    *env = new_node;
}

char    *ft_copy_end(char *str, char c)
{
    char *dest;
    int x;
    int i;

    x = 0;
    i =0;

    while(str[x])
    {   
        if(str[x]==c)
            break;
        x++;
    }
    // printf("Je suis ft_strlen = |%d|, x = |%d|, les deux |%d| strx= |%c|", ft_strlen(str),x, (ft_strlen(str) - x),str[x]  );
    dest = malloc((sizeof(char *) *(ft_strlen(str) - x + 1)));//It's ok
    x++;
    while(str[x])
    {
        dest[i] = str[x];
        i++;
        x++;
    }
    dest[i] = '\0';
    return(dest);
}

char    *ft_copy_start(char *str, char c)
{   
    int x;
    char *dest;
    int i;

    i = 0;
    x = 0;
    while(str[x])
    {
        if (str[x] == c)
            break;
        x++;
    }
    dest = malloc(sizeof(char *)*(x + 1));//Il n'y a pas le plus car nous sommes a la fin de la boucle.
    while(i<x)
    {
        dest[i] = str[i];
        i++;
    }
    dest[i]= '\0';
    return(dest);
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





