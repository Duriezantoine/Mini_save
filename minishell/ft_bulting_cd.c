/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:44:24 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/23 17:46:24 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *save_pwd(t_env **env)
{
    char *dest;
    t_env *tmp;

    dest = NULL;
    tmp = *env;
    while(tmp)
    {
        if (strncmp(tmp->key, "PWD", 3) == 0) 
            dest = ft_strdup(tmp->value);
        tmp = tmp->next;
    }
    return(dest);
}

int     ft_verif_cd(char **cmd_and_args)
{

    if (cmd_and_args[1] && cmd_and_args[2])
    {
        write(2, "cd: too many arguments\n", 24);
        return(1);
    }
    return(0);
}
int    ft_exceve_cd(char **cmd_and_args, t_env **env)
{
    char *dest;
    char *save;

    if(ft_verif_cd(cmd_and_args)==1)
        return(1);
    if (ft_no_cd_(cmd_and_args[1])==0)
    {
        if(ft_simple_cd(cmd_and_args[1], env)==1)
            return(1);
    }
    else
    {
        save = save_pwd(env);
        dest = new_path_cd(cmd_and_args[1], env);
        chdir(dest);
        ft_change_env(save, &env);
        free(dest);
    }
    return(0);
}

int    bulting_cd (char **cmd_and_args,t_node *list ,t_env **env)
{
    (void)list;
    if(cmd_and_args[1] !=NULL)
    {
        if ((cmd_and_args[1]) != NULL)
        {
            if(ft_exceve_cd(cmd_and_args, env)==1)
                return (1);
        }
    }
    else
        ft_execute_cd_home(env, 0);
    return (0);
}

int    ft_simple_cd(char *s, t_env **env)
{
    char *save;

    save = save_pwd(env);
    if(chdir(s)!= 0)
    {
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        return (1);
    }
    ft_change_env(save, &env);
    return (0);
}

void ft_change_env(char *save, t_env ***env)
{
    t_env *tmp;

    tmp = **env;
    char cwd[1024];
    while (tmp)
    {
        if (strncmp(tmp->key, "OLDPWD", 6) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(save);
        }
        if (strncmp(tmp->key, "PWD", 3) == 0)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                free(tmp->value);
                tmp->value = ft_strdup(cwd);
            }
        }
        tmp = tmp->next;
    }
    free(save);
}
char    *new_path_cd(char *s, t_env **env)
{
    char *dest;
    int i;
    int x;

    x = 0;
    i=0;
    dest = NULL;
    while(s[i])
    {
        if(s[i]== '~')
            break;
        i++;
    }
    dest = ft_execute_cd_home(env, 1);
    x = ft_strlen(dest);
    while(s[++i])
    {
        dest[x++] = s[i];
    }
    dest[x] = '\0';
    return(dest);
}

char *ft_execute_cd_home(t_env **env, int i)
{
    t_env *tmp;
    char *dest;
    char *save;

    tmp = *env;
    while(tmp)
    {
        if (strncmp("HOME", tmp->key, 4) == 0)
        {
            if (i == 0)
            {
                save = save_pwd(env);
                if(chdir(tmp->value) != 0)
                    ft_putstr_fd("Failed to enter directory", 2);
                ft_change_env(save, &env);
                return (NULL);
            }
            dest = ft_strdup(tmp->value);
            return(dest);
        }
        tmp = tmp->next;
    }
    return(NULL);
}

int     ft_no_cd_(char *s)
{
    int i;

    i = 0;
    while(s[i])
    {
        if(s[i]== '~')
            return(1);
        i++;
    }
    return(0);
}
