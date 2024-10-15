/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:44:24 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/15 08:41:30 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void    ft_exceve_cd(char **cmd_and_args, t_env **env)
{
    char *dest;
    char *save;
    if (ft_no_cd_(cmd_and_args[1])==0)
        ft_simple_cd(cmd_and_args[1], env);
    else
    {
        save = save_pwd(env);//C'est ce qui permet de sauvegarder dans tous les cas ou on utlise cd
        dest = new_path_cd(cmd_and_args[1], env);
        chdir(dest);
        ft_change_env(save, &env);
        free(dest);
    }
}
void    bulting_cd (char **cmd_and_args,t_node *list ,t_env **env)
{
    (void)list;
    printf("\nCD\n");//A chaque utilisation de cd il faut remettre en place 

    if(cmd_and_args[1] !=NULL)
    {
        if ((cmd_and_args[1]) != NULL)
        {
            ft_exceve_cd(cmd_and_args, env);
        }
    }
    else
        ft_execute_cd_home(env, 0);
}

void    ft_simple_cd(char *s, t_env **env)
{
    char *save;

    save = save_pwd(env);
    printf("Je passe dans simple cds = |%s|\n", s);
    if(chdir(s)!= 0)
        printf("Probleme");
    ft_change_env(save, &env);
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
