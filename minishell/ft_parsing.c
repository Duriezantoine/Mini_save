/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:51:14 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/01 10:10:14 by aduriez          ###   ########.fr       */
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
        printf("str: %s, bool: %d\n", current->str, current->bool);
        current = current->next;
    }
}

int ft_parsing(t_node *list, t_data **data, char *input)
{
    int i;

    i = 0;
    t_save *save = NULL;
    t_echo data_echo;
    t_command *command = NULL;

    ft_parsing_init(&command, *data, input); // IL faut mettre des conditions pour verifier les signaux
    t_node *pointeur = list;                 // IL faut mettre des conditions pour verifier le parsing
    while ((data != NULL) && (*data != NULL) && i < (*data)->nbr_command)
    {
        save = NULL;
        if (i != 0)
            ft_inser_init_list_arg(&list); // Je pense qu'il faut utliser un pointeur pour mettre next in function demander a titouan
        if (ft_split_with_space(&data_echo, command[i].input_split) == 1)
            return (1); // Voir comment acceder a ma data
        init_t_save(&save);
        ft_insert_new_data_with_data(&save, &data_echo);
        t_save *tmp = save;
        while (tmp)
        { // Boucle permettant d'introduire dans la list->arg
            list->arg = ft_init_list(list, &data_echo, tmp);
            tmp = tmp->next;
        }
        free_list(save);
        i++;

    }
    list = pointeur;
    return (0);
}

void ft_parsing_init(t_command **command, t_data *data, char *input)
{
    if (command == NULL || data == NULL)
        ft_out_exit(5);
    int i = 0;
    int len;
    char **tokens = split_string(input, &len); // Appeler la fonction split_string
    if (tokens == NULL)
        ft_out_exit(4);
    // printf("LONGEUR= %d", len);
    *command = malloc((len + 1) * sizeof(t_command));
    if (*command == NULL)
        ft_out_exit(3);
    while (i < len)
    {
        (*command)[i].input_split = malloc(sizeof(char *) * (ft_strlen(tokens[i]) + 1));
        (*command)[i].b = 2;
        (*command)[i].input_split = ft_strdup(tokens[i]);
        // printf("\n|Jqe suis la cmd|%s|n", (*command)[i].input_split);
        i++;
    }
    (*data).nbr_command = len;
    // free_tokens(tokens, len); // Libérer les tokens
}
