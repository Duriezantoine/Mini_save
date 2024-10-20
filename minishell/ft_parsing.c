/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:51:14 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/20 18:57:48 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void append_node(t_node **list, t_node *new_list)
{
    while ((*list)->next)
    {
        (*list) = (*list)->next;
    }
    new_list->prev = (*list);
    (*list)->next = new_list;
}
void ft_inser_init_list_arg(t_node **list)
{
    t_node *new_list;
    ft_init_data_list(&new_list);
    append_node(list, new_list);
    (*list) = (*list)->next;
}
void init_t_save(t_save **save)
{
    if (save == NULL)
    {
        return;
    }

    *save = NULL;
}
void free_list(t_save* head) {
    t_save* current = head;
    t_save* next;

    while (current != NULL) {
        next = current->next;
        free(current->str); // Libérer la chaîne de caractères si elle est allouée dynamiquement
        free(current);
        current = next;
    }
}
void print_list_save(t_save* head) {
    t_save* current = head;

    while (current != NULL) {
        // printf("str: %s, bool: %d\n", current->str, current->bool);
        // current = current->next;
    }
}
void print_save_list(t_save *head)
{
	t_save *current = head;

	while (current != NULL)
	{
		// printf("str: %s, bool: %d\n", current->str, current->bool);
		current = current->next;
	}
}
void print_t_arg(t_arg *arg) {
    if (arg == NULL) {
        printf("NULL\n");
        return;
    }

    printf("str_command: %s\n", arg->str_command ? arg->str_command : "NULL");
    printf("type: %d\n", arg->type);
    printf("quot: %d\n", arg->quot);
    printf("prev: %p\n", (void *)arg->prev);
    printf("next: %p\n", (void *)arg->next);
}

int     ft_search_var_env(char **save, t_env *env, t_data *data)
{
    t_env *tmp;
    char *tampon;
    char *new_val;
    tmp = env;
    if ((*save)[0] == '?')
    { 
        tampon = ft_itoa(data->exit_code);
        new_val = ft_strjoin(tampon, *save + 1);
        free(*save);
        free(tampon);
        *save = new_val;
        return (0);
    }
    while(tmp)
    {
        if(strequ((*save), tmp->key)) 
        {
            tampon = ft_strdup(tmp->value);
            free((*save));
            (*save) = tampon;
            return(0);
         }
        tmp = tmp->next;
    }
    return(1);
}
int     ft_verifi_var_glob(char *str, char **save, t_env *env, t_data *data)
{
    int i;
    int c;
    int y;

    y = 0;
    i = 0;
    c=0;
    while(str[i])
    {
        // if(str[i]== '\'' && str[i+1]== '\0')
        // {
        //     (*save)=NULL;   
        //     return(0);
        // }
        if (str[i] == '"' && str[i+1] == '$' && str[i+2] != '\0')
        {
             i=i+2;
             y = i;
             while(str[i]!='"')
            {
                i++;
                c++;
            } 
        }
        else
            c++;
        i++;
    }
    i = 0;
    (*save) = malloc(sizeof(char) *  (c + 1));
    while(str[y] && str[y] != '"')
    {
        (*save)[i] = str[y]; 
        // printf("y: |%d|%c| i:|%d|%c|\n ", y,  str[y], i, (*save)[i]);
        i++;
        y++;
    }
    (*save)[i]= '\0';
    if(ft_search_var_env(save, env, data)== 0)
        return(0);
    return(1);
}
char    *ft_change_save_v3(char *str, t_env *env, char c, t_data *data)
{
    int x;
    int i;

    char *save;
    x = 0;
    i = 0;
    save = NULL; 
    if(ft_verifi_var_glob(str, &save, env, data)== 0)
    {
        return(save);
    }
    while(str[x])
    {
        if(str[x]== c)
        {
            x++;
        }
        else
        {
            i++;
            x++;
        }
    }
    free(save);
    save = malloc(sizeof(char)*(i+1));
    i = 0;
    x = 0;
    while(str[x])
    {
        if(str[x]== c)
            x++;
        else
        {
            save[i] = str[x];
            i++;
            x++;
        }
    }
    save[i]= '\0';
    return(save);
}
void ft_change_save_v2(t_save **save, t_env *env, t_data *data)
{
    t_save *tmp;
    int x;
    (void)env;
    char *save_tmp;
    tmp = *save;
    while(tmp)
    {
        // printf("Boucle|%s|", tmp->str);
        x = 0;
        while(tmp->str[x])
        {
            if (tmp->str[x]== '\'' || tmp->str[x] == '"')
                {        
                    // printf("TMP|%s|", tmp->str);
                    save_tmp = ft_change_save_v3(tmp->str, env, tmp->str[x], data);
                    free(tmp->str);
                    tmp->str = ft_strdup(save_tmp);
                    free(save_tmp);
                    break;
                }
            x++;
        }
        tmp = tmp->next;
    }
}

int ft_parsing(t_node *list, t_data *data, char *input, t_env *env)
{
    int i;

    i = 0;
    t_save *save = NULL;
    t_echo data_echo;
    char **tokens;

    tokens = ft_parsing_init(data, input); // IL faut mettre des conditions pour verifier les signaux
    while (i < data->nbr_command)
    {
        if (i != 0)
            ft_inser_init_list_arg(&list); // Je pense qu'il faut utliser un pointeur pour mettre next in function demander a titouan
        if (ft_split_with_space(&data_echo, tokens[i]) == 1)
            return (1); // Voir comment acceder a ma data
        save = NULL;
        ft_insert_new_data_with_data(&save, &data_echo, env);
      print_save_list(save);
         ft_change_save_v2(&save,env, data);
        t_save *tmp = save;
        while (tmp)
        { // Boucle permettant d'introduire dans la list->arg
            // printf("adding: %s\n", tmp->str);
            list->arg = ft_init_list(list, &data_echo, tmp);
            // print_t_arg(list->arg);
            tmp = tmp->next;
        }
        free_list(save);
        ft_free_data_echo(&data_echo);
        i++;
    }
    free_tokens(tokens, data->nbr_command);
    return (0);
}

char **ft_parsing_init(t_data *data, char *input)
{
    if (data == NULL)
        ft_out_exit(5);
    int len;
    char **tokens = split_string(input, &len); // Appeler la fonction split_string
    if (tokens == NULL)
        ft_out_exit(4);
    (*data).nbr_command = len;
    return tokens;
}
