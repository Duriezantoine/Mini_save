/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:56:21 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/23 18:04:14 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    bulting_export(char **argv, char ***env)
{
    char    **tmp;
    int     x;

    tmp = argv;
    x = 1;
    while(tmp[x])
    {
        if(ft_verif_export(tmp[x])==1)
            return(1);
        if(ft_search_envp(*env, tmp[x])==2)
            ft_change_var(env, tmp[x], 0);
        else if(ft_search_envp(*env, tmp[x])==0)
            ft_delim_envp(env, tmp[x]);
        else
            ft_change_var(env, tmp[x], 1);          
        x++;
    }
    return(0);
}

void ft_search_and_change_envp(char *key, char *str, char ***envp)
{
    int x = 0;
    char *key_envp;
    char *tmp;
    
    while((*envp)[x])
    {
        key_envp = ft_copy_start((*envp)[x], '=');
        if (strncmp(key_envp, key, ft_strlen(key)) == 0) {
            
            free((*envp)[x]);
            tmp = ft_strjoin(key, "=");
            (*envp)[x] = ft_strjoin(tmp, str);
            free(tmp);
            free(key_envp);
            break;
        }
        free(key_envp);
        x++;
    }
}

void ft_search_and_concaten_envp(char *key, char *str, char ***envp)
{
    int x = 0;
    char *key_envp;
    char *value_envp;
    char *new_value;
    char *tmp;
    while((*envp)[x])
    {
        key_envp = ft_copy_start((*envp)[x], '=');
        if (strncmp(key_envp, key, ft_strlen(key)) == 0) {
            
            value_envp = ft_copy_end((*envp)[x], '=');
            new_value = ft_strjoin(value_envp, str);
            free((*envp)[x]);
            tmp = ft_strjoin(key_envp, "=");
            (*envp)[x] = ft_strjoin(tmp, new_value);
            free(tmp);
            free(key_envp);
            free(value_envp);
            free(new_value);
            break;
        }
        free(key_envp);
        x++;
    }
}


void ft_change_var(char ***env, char *str, int x)
{
    char    *sep;
    
    sep = strchr(str, '=');
    if (x == 1)
    {
        if (sep == NULL)
            return;
        *sep = '\0';
        ft_search_and_change_envp(str, sep + 1, env);
    }
    else if (x == 0)
    {
        *(sep - 1) = '\0';
        ft_search_and_concaten_envp(str, sep + 1, env);
    }
}


void    ft_delim_envp( char  ***env, char *str)
{
    char    *sep;

    sep = strchr(str, '=');
    if (sep == NULL)
        ft_insert_envp(env, str, NULL);
    else
    {
        *sep = '\0';
        ft_insert_envp(env, str, sep + 1);
    }
}

void ft_insert_envp(char  ***env, char *key, char *value)
{
    char *str;
    char *tmp;

    if (value == NULL)
        *env = ft_add_string_to_array(*env, key);
    else
    {
        tmp = ft_strjoin(key, "=");
        str = ft_strjoin(tmp, value);
        free(tmp);
        *env = ft_add_string_to_array(*env, str);
        free(str);
    }
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
    dest = malloc((sizeof(char *) *(ft_strlen(str) - x + 1)));
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
    dest = malloc(sizeof(char *)*(x + 1));
    while(i<x)
    {
        dest[i] = str[i];
        i++;
    }
    dest[i]= '\0';
    return(dest);
}

int     ft_verif_export_add_equal(char *str)
{
    int x;
    x = 0;
    while(str[x])
    {
        if(str[x]=='+')
            if(str[x+1]!= '=')
                return(0);
        x++;
    }
    return(1);
}
int     ft_verif_key_letter_number_underscore(char *str)
{
    int x;
    x = 0;
    char *end;

    char *sep;
     sep = strchr(str, '+');
    if(sep==NULL)
        end = ft_copy_start(str, '=');
    else
        end = ft_copy_start(str, '+');
    if (end[0] == '\0' )
        return(1);
    while(end[x])
    {
        if ((str[x]< 48 || str[x]> 57) &&
        (str[x]< 65 || str[x]> 90) &&
        (str[x]< 97 || str[x]> 122) &&
        str[x]!= 95)
        return(1);
        x++;
    }
    return(0);
}

int ft_verif_one_letter(char *str)
{
    if (str == NULL || *str == '\0')
        return 1;
    if (str[0] >= '0' && str[0] <= '9')
    {
        write(2, "export: `", 9);
        write(2, str, ft_strlen(str));
        write(2, "': not a valid identifier\n", 26);
        return 1;
    }
    return(0); 
}

int     ft_verif_export(char *str)
{
        if(ft_verif_export_add_equal(str)==0)
        {
            write(2,"export: not valid in this context: ", 30);
            write(2, str, ft_strlen(str));
            write(2, "\n", 1);
            return(1);
        }
        if(ft_verif_key_letter_number_underscore(str)==1)
        {
            write(2, "export: `", 9);
            write(2, str, ft_strlen(str));
            write(2, "': not a valid identifier\n", 26);
            return(1);
        }
        if (ft_verif_one_letter(str)==1)
        {
            printf("La");
            return(1);
        }
        return(0);
}





