/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:44:24 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/19 14:08:07 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

char *save_pwd(t_env **env)
{
    char *dest;

    dest = NULL;
    t_env *tmp;
    tmp = *env;
    while(tmp)
    {
        if (strncmp(tmp->key, "PWD", 3) == 0) 
            dest = ft_strdup(tmp->value);
      tmp = tmp->next;
    }
    return(dest);
}

int verif_num_args_cd(char **cmd_and_args)
{
    int x;

    x = 0;
    while(cmd_and_args[x])
    {
        x++;
    }
    // printf("\nX=|%d|\n", x);
    if(x>2)
    {
        return(1);  
    }
    return(0);
}

int     ft_verif_cd(char **cmd_and_args)
{



    if (verif_num_args_cd (cmd_and_args)==1)
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
        save = save_pwd(env);//C'est ce qui permet de sauvegarder dans tous les cas ou on utlise cd
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
    //printf("\nCD\n");//A chaque utilisation de cd il faut remettre en place 

    if(cmd_and_args[1] !=NULL)
    {
        if ((cmd_and_args[1]) != NULL)
        {
            if(ft_exceve_cd(cmd_and_args, env)==1)
                return(1);
        }
    }
    else
        ft_execute_cd_home(env, 0);
    return(0);
}

int    ft_simple_cd(char *s, t_env **env)
{
    char *save;

    save = save_pwd(env);
    // printf("Je passe dans simple cds = |%s|\n", s);
    if(chdir(s)!= 0)
    {
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        // write(2, "(too many arguments)\n", 22);
        return(1);
    }
    ft_change_env(save, &env);
    return(0);
}

void ft_change_env(char *save, t_env ***env)
{
    t_env *tmp;
    tmp = **env;
    char cwd[1024]; // Déclare un tableau de caractères pour stocker le chemin du répertoire de travail courant

    while (tmp)
    {
        if (strncmp(tmp->key, "OLDPWD", 6) == 0)
        {
            free(tmp->value);
            // printf("\nXXXXXXXXXjE SUIS CE QUE JE DOIS CHANGER|%s|\n", save);
            tmp->value = ft_strdup(save);
        }
        if (strncmp(tmp->key, "PWD", 3) == 0)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                // On considère que le nouveau chemin actuel est lui
                free(tmp->value);
                // printf("\nWWWWWWWWWWWWWWWWWWWjE SUIS LE NEWPWD|%s|\n", cwd);
                tmp->value = ft_strdup(cwd);
            }
        }
        tmp = tmp->next;
    }
    free(save); // Libérez save après avoir terminé toutes les modifications
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
    tmp = *env;
    char *dest;
    char *save;

    while(tmp)
    {
        if (strncmp("HOME", tmp->key, 4) == 0)
        {
            if( i == 0)
            {
                save = save_pwd(env);
                if(chdir(tmp->value)!= 0)
                    printf("IL y a une erreur dans le chemin");
                ft_change_env(save, &env);
                return(NULL);
            }
            if(i == 1)
            {
                dest = ft_strdup(tmp->value);
                return(dest);
            }
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
