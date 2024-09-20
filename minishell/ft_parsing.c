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

void  ft_search_built(t_node **list, char **save)
{
    int i;

    i = 0;
    (void)list;
    while(save[i] != NULL)
    {
        if (ft_strcmp(save[i], "<"))
        printf("\nsave=|%s|\n",save[i]);
        i++;
    }
}

void ft_insert_list(t_node **list, t_echo **data_echo)
{
    (void)list;
    printf("TotalINSER = %d", (*data_echo)->w_quot + (*data_echo)->s_quot);
    char **save =NULL; // CREATION D'UNE DOUBLE CHAINNE DE CARACTERERE POUR SE BALADER DEDAN.
    save = malloc (sizeof(char *) * (*data_echo)->w_quot + (*data_echo)->s_quot);
    ft_insert_new_data_with_data(save, data_echo);
    //Maintenant il faut commencer a verfifier a la suite 
    ft_search_built(list, save);
    //Il ne faut pas oublier de free tout le data_echo 
}

int ft_parsing(t_node ***list, t_data **data, char *input)
{
    (void)data;
    (void)list;
    // int i;

    // i = 0;
    t_echo *data_echo;
    t_command *command = NULL; // Initialisation à NULL
    // Il faut d'une conditions pour les signaux
    // Mettre en place des conditions pour verifier le parsing
    ft_parsing_init(&command, *data, input);
    *list = (t_node **)malloc((*data)->nbr_command * sizeof(t_node *));
    // while (i < (*data)->nbr_command)
    // {
    if(ft_split_with_space(&data_echo, command[0].input_split)== 1)
        return(1); // Voir comment acceder a ma data
    ft_init_list(&((*list)[0]), &data_echo);
    // i++;
    // }
    //  Malloc de la structure avec le nbr de commandes
    return(0);
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
    printf("LONGEUR= %d", len);
    *command = malloc((len + 1) * sizeof(t_command));
    if (*command == NULL)
        ft_out_exit(3);
    while (i < len)
    {
        (*command)[i].input_split = malloc(sizeof(char *) * (ft_strlen(tokens[i]) + 1));
        (*command)[i].b = 2;
        (*command)[i].input_split = ft_strdup(tokens[i]);
        printf("\n|Jqe suis la cmd|%s|n", (*command)[i].input_split);
        i++;
    }
    (*data).nbr_command = len;
    // free_tokens(tokens, len); // Libérer les tokens
}
