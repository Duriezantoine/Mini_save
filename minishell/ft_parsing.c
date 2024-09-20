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

void ft_split_with_space(t_echo **data_echo, char *input)
{
    ft_init_token_space(data_echo, input, 0);
    ft_init_echo_malloc(data_echo);
    ft_init_tab_echo_malloc(data_echo, input, 0);
    ft_insert_tab_echo(data_echo, input, 0);
    // Il faut recrer une fonction permettant
}

void ft_init_list(t_node **list, t_echo **data_echo)
{
    (void)list;
    // 1 er chose il faut commencer par malloc
    *list = (t_node *)malloc(sizeof(t_node));
    if (list == NULL || data_echo == NULL || *data_echo == NULL)
    {
        fprintf(stderr, "Erreur : paramètres invalides\n");
        return;
    }
    (*list)->infile = -1;
    (*list)->outfile = -1;

    (*list)->next = NULL;
}
void ft_insert_list(t_node **list, t_echo **data)
{
    printf("TotalINSER = %d", (*data_echo)->w_quot + (*data_echo)->s_quot);
    char **save; // CREATION D'UNE DOUBLE CHAINNE DE CARACTERERE POUR SE BALADER DEDAN.
    *save = malloc (sizeof(char *) * (*data_echo)->w_quot + (*data_echo)->s_quot))
    ft_insert_new_data_with_data(save, &data_echo);
}

void ft_parsing(t_node ***list, t_data **data, char *input)
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
    ft_split_with_space(&data_echo, command[0].input_split); // Voir comment acceder a ma data
    ft_init_list(&((*list)[0]), &data_echo);
    ft_inser_list((&(*list)[0], &data_echo));
    // i++;
    // }
    //  Malloc de la structure avec le nbr de commandes
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
