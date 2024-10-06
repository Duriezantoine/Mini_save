/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/03 15:56:07 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_search_n(t_cmd *cmd, int i)
{
    int x;
    x = 0;
    while(cmd->cmd_and_args[i][x])
    {
        if (cmd->cmd_and_args[i][x]== '-' && cmd->cmd_and_args[i][x+1] == 'n')
            x = x+2;
        else 
            return(1);
        while(cmd->cmd_and_args[i][x]== 'n')
           x++;
    }
    if (cmd->cmd_and_args[i][x]== '\0')
    {
        printf("\nJe suis a la fin de l'atguments\n");
        return(0);
    }
    return(1);
}

void sort_envp(t_env **env) {
    t_env *current, *index;
    char *tmp_key;
    char *tmp_value;

    for (current = *env; current != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (strcmp(current->key, index->key) > 0) {
                // Échanger les clés
                tmp_key = current->key;
                current->key = index->key;
                index->key = tmp_key;

                // Échanger les valeurs
                tmp_value = current->value;
                current->value = index->value;
                index->value = tmp_value;
            }
        }
    }
}

t_env *copy_env(t_env *env) 
{
    t_env *copy = NULL;
    t_env *current = env;
    t_env *prev = NULL;

    while (current != NULL) {
        t_env *new_node = (t_env *)malloc(sizeof(t_env));
        if (new_node == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        new_node->key = strdup(current->key);
        new_node->value = strdup(current->value);
        new_node->next = NULL;
        if (copy == NULL) 
            copy = new_node;
         else 
            prev->next = new_node;
        prev = new_node;
        current = current->next;
    }
    return copy;
}
void bulting_env(t_cmd *cmd, t_node *list) {
    (void)cmd;
    // Créer une copie temporaire de la liste t_env
    t_env *tmp = copy_env(list->env);

    // Trier la copie temporaire
    sort_envp(&tmp);

    // Afficher les variables d'environnement triées
    t_env *current = tmp;
    while (current != NULL) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }

    // Libérer la mémoire allouée pour la copie temporaire
    current = tmp;
    while (current != NULL) {
        t_env *next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
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
    dest = malloc((sizeof(char *) *(ft_strlen(str) - x)));//It's ok
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
    dest = malloc(sizeof(char *)*(x));//Il n'y a pas le plus car nous sommes a la fin de la boucle.
    while(i<x)
    {
        dest[i] = str[i];
        i++;
    }
    dest[i]= '\0';
    return(dest);
}
void print_env(t_env *env)
{
    while (env != NULL)
    {
        printf("Key: %s, Value: %s\n", env->key, env->value);
        env = env->next;
    }
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

void    bulting_echo(t_cmd *cmd, int i)
{
    (void)cmd;
     if (ft_search_n(cmd, i)== 0)
        bulting_echo(cmd, i+1);
    else
        {
            while(cmd->cmd_and_args[i] )
            {
                printf("%s", cmd->cmd_and_args[i]);
                i++;
            }
        }    
}
char *ft_execute_cd_home(t_env **env, int i)
{

    t_env *tmp;
    tmp = *env;
    char *dest;
    printf ("Je rentre dans la contions si l'argument est vide");
    while(tmp)
    {
        if (strncmp("HOME", tmp->key, 4) == 0)
        {
            printf("Je suis le home value|%s|", tmp->value);
            if( i ==0)
            {
                if(chdir(tmp->value)!= 0)
                {
                    printf("IL y a une erreur dans le chemin");
                }
                return(NULL);
            }
            if(i ==1)
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

void    ft_simple_cd(char *s)
{
    printf("Je passe dans simple cds = |%s|\n", s);
    if(chdir(s)!= 0)
        printf("Probleme");
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

void    ft_exceve_cd(t_cmd *cmd, t_env **env)
{
    char *dest;
    if (ft_no_cd_(cmd->cmd_and_args[1])==0)
        ft_simple_cd(cmd->cmd_and_args[1]);
    else
    {
        dest = new_path_cd(cmd->cmd_and_args[1], env);
        chdir(dest);
        free(dest);
    }
}
void    bulting_cd (t_cmd *cmd, t_env **env)
{
    printf("\nCD\n");

    if(cmd->cmd_and_args[1] !=NULL)
    {
        
        if ((cmd->cmd_and_args[1]) != NULL)
        {
            ft_exceve_cd(cmd, env);
        }
    }
    else
        ft_execute_cd_home(env, 0);
}