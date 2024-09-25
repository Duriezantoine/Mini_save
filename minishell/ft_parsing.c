/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:51:14 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/24 13:54:25 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void       append_node(t_node **list, t_node *new_list)
{
    while((*list)->next)
    {
        (*list) = (*list)->next;
    }
    new_list ->prev = (*list);
    (*list)->next = new_list;

}


int ft_parsing(t_node *list, t_data **data, char *input)
{
    int i;

    i = 0;
    t_echo data_echo;
    t_command *command = NULL;
    //     t_arg *arg_s = NULL;
    int x = 0;
    char **save = NULL; // CREATION D'UNE DOUBLE CHAINNE DE CARACTERERE POUR SE BALADER DEDAN.
    // Il faut d'une conditions pour les signaux
    // Mettre en place des conditions pour verifier le parsing
    ft_parsing_init(&command, *data, input);
    t_node *pointeur = list ;
    while (i < (*data)->nbr_command)
    {
        if(i != 0)
        {
            t_node *new_list;
            ft_init_data_list(&new_list);
            append_node(&list, new_list);
            list = list->next;
        }
        if (ft_split_with_space(&data_echo, command[i].input_split) == 1)
            return (1); // Voir comment acceder a ma data
        save = malloc(sizeof(char *) * (data_echo.w_quot + data_echo.s_quot + 1));
        ft_insert_new_data_with_data(save, &data_echo);
        x = 0;
        //Possible mise en place d'un pointeur au debut de la liste
        while (save[x])
        {
            list->arg = ft_init_list(list, &data_echo, save[x]);
            x++;
        }
        free(save);
        i++;
    }
    list = pointeur;
    return (0);
}
void ft_verif_token_infile(t_command **command, t_data **data)
{
    printf("\n|SSSSJqe suis la cmd|%s|n", (*command)[0].input_split);
    (void)data;
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
