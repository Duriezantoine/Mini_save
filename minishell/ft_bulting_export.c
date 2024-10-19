/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:56:21 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/19 11:34:55 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_char_array(char **array) {
    if (array == NULL) {
        printf("Le tableau est NULL\n");
        return;
    }

    int i = 0;
    while (array[i] != NULL) {
        printf("%s\n", array[i]);
        i++;
    }
}

int    bulting_export(char **argv, char ***env)
{
    (void)env;

    char **tmp = argv;
    int x = 1;
    while(tmp[x])
    {
        // if(tmp[x][ft_strlen(tmp)-1]=='=')

        // printf("\nTMP[x]=|%s|\n",tmp[x] );
        if(ft_verif_export(tmp[x])==1)
            return(1);
        // else
        //     {
                // printf("Command est valide");
                if(ft_search_envp(*env, tmp[x])==2)
                {

                    ft_change_var(env, tmp[x], 0); // replace
                }
                else if(ft_search_envp(*env, tmp[x])==0)
                {

                    ft_delim_envp(env, tmp[x]); // create var
                }
                else
                {
                    ft_change_var(env, tmp[x], 1); // concat             
                }


            // }
        x++;
    }
    return(0);
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

void ft_search_and_change_envp(char *key, char *str, char ***envp)
{
    int x = 0;
    char *key_envp;
    char *tmp;
    
    while((*envp)[x])
    {
        key_envp = ft_copy_start((*envp)[x], '=');
        // printf("KEY_ENVP|%s|, key|%s|", key_envp, key);
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

//    print_char_array(*envp);
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
    // print_char_array(*envp);
}

 void ft_change_var_g(char ***env, char *str, int x, char *change)
 {
    char *key;
    char *value;
    (void)change;
    //IL faut faire la difference entre la clef et la valeur
    value = ft_copy_end(str, '=');//A inserer dans ma libft
    // printf("\nValue|%s|\n");
    if(x==1)
    {
         key = ft_copy_start(str, '=');//A inserer dans ma libft
        ft_search_and_change_envp(key, value, env);
    }
    if(x==0)
    {
        key = ft_copy_start(str, '+');//A inserer dans ma libft
        ft_search_and_concaten_envp(key, value, env);
    }
 }


 void ft_change_var(char ***env, char *str, int x)
 {
    // x=1: create
    // x=0: concat
    char    *sep = strchr(str, '=');

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


    // char *key;
    // char *value;
    // //IL faut faire la difference entre la clef et la valeur
    // // value = strchr(str, '=');
    // value = ft_copy_end(str, '=');//A inserer dans ma libft

    // printf("v:%d\n", x);
    
    // if(x==1) // create
    // {
    //     key = ft_copy_start(str, '=');//A inserer dans ma libft
    //     ft_search_and_change_envp(key, value, env);
    // }
    // if(x==0) // concat
    // {
    //     key = ft_copy_start(str, '+');//A inserer dans ma libft
    //     ft_search_and_concaten_envp(key, value, env);
    // }
    // free(value);
    // free(key);
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
        if ((str[x]< 48 || str[x]> 57) && // Chiffres 0-9
        (str[x]< 65 || str[x]> 90) && // Lettres majuscules A-Z
        (str[x]< 97 || str[x]> 122) && // Lettres minuscules a-z
        str[x]!= 95)
        return(1);
        x++;
    }
    return(0);
}

int ft_verif_one_letter(char *str)
{
    if (str == NULL || *str == '\0')
    {
        // Gestion du cas où la chaîne est NULL ou vide
        return 1;
    }

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

        //1 er conditions determiner si il n'y a de = apres
        if(ft_verif_export_add_equal(str)==0)
        {
            // printf("ICIC");
            write(2,"export: not valid in this context: ", 30);
            write(2, str, ft_strlen(str));
            write(2, "\n", 1);
            return(1);
        }
        //2 em conditions qui verifier si la key est bien composer de lettre de chiffre et de underscore
        if(ft_verif_key_letter_number_underscore(str)==1)
        {
            write(2, "export: `", 9);
            write(2, str, ft_strlen(str));
            write(2, "': not a valid identifier\n", 26);
            return(1);
        }
        //3em conditions qui verifient que la premiere lettre ne soit pas considerer comme un nombre 
        if (ft_verif_one_letter(str)==1)
        {
            printf("La");
            return(1);
        }
        return(0);
}





