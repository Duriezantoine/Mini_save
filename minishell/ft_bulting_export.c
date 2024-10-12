/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:56:21 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/12 17:29:47 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    bulting_export(char **argv, char ***env)
{
    (void)env;

    char **tmp = argv;
    int x = 1;
    while(tmp[x])
    {
        if(ft_verif_export(tmp[x])==0)
            printf("NOT VALID");
        else
            {
                printf("Command est valide");
                if(ft_search_envp(*env, tmp[x])==0)
                {
                    printf("\nVariables not exist\n");//Je dois donc la mettre a la creer et l'inserer
                    ft_delim_envp(env, tmp[x]);
                    // print_env(env);
                }
                else
                     printf("\nExist\n");//Je dois donc la mettre a la creer et l'inserer


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

void    ft_delim_envp( char  ***env, char *str)
{
    (void) env;
    (void)str;
    char *key;
    char *value;
    //IL faut faire la difference entre la clef et la valeur
    key = ft_copy_start(str, '=');//A inserer dans ma libft
    value = ft_copy_end(str, '=');//A inserer dans ma libft

    printf("Value = |%s| Key=|%s|", key, value);    
   // Creation d'une protection
    if (key == NULL || value == NULL)
    {
        free(key);
        free(value);
        printf("\nCe n'est pas passer ft_insert_envp\n");
        return;
    }
    ft_insert_envp(env, key, value);
    free(key);
    free(value);
}

void    ft_change_envp(char **env, char *key, char *value)
{
    // t_env *tmp;
    (void)env;
    (void)key;
    (void)value;
    // tmp = *env;
    // while(tmp)
    // {
    //     if (strncmp(tmp->key, key, ft_strlen(key)) == 0) 
    //     {
    //         // printf("\n\nJe suis dedans\n \n");
    //         //Je veux juste la valeur de value est que ca marche
    //         free(tmp->value);
    //         tmp->value = ft_strdup(value);
    //         return;
    //     }
    //     tmp = tmp->next;
    // }
    return ;
}

void ft_insert_envp(char  ***env, char *key, char *value)
{
    (void)env;
    (void)value;
    char *str;
    str =ft_strjoin(key, "=");
    str = ft_strjoin(str, value);

    *env = ft_add_string_to_array(*env, str);
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





