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

int ft_split_with_space(t_echo **data_echo, char *input)
{
    printf("INPUT = |%s|", input);
    if(ft_init_token_space(data_echo, input, 0)== 1)
        return(1);
    ft_init_echo_malloc(data_echo);
    ft_init_tab_echo_malloc(data_echo, input, 0);
    ft_insert_tab_echo(data_echo, input, 0);
    // Il faut recrer une fonction permettant de free a la toutes fin ne pas zappe
    return(0);
}

void ft_insert_data_data_echo_w(char  **save, t_echo **data_echo, int i, int iterateur_w)
{
    int i_past;
    // int save;
    i_past = 0;
    free(save[i]);
    save[i] = malloc(sizeof(char *) * ft_strlen((*data_echo)->str_w_quot[iterateur_w].str) + 1);
    while ((*data_echo)->str_w_quot[iterateur_w].str[i_past])
    {
        save[i][i_past] = (*data_echo)->str_w_quot[iterateur_w].str[i_past];
        i_past++;
    }

    save[i][i_past] = '\0';
    free((*data_echo)->str_w_quot[iterateur_w].str);
}

void ft_insert_data_data_echo_s(char **save, t_echo **data_echo, int i, int iterateur_s)
{
    int i_past;

    i_past = 0;
    free(save[i]);
    save[i] = malloc(sizeof(char *) * ft_strlen((*data_echo)->str_s_quot[iterateur_s].str) + 1);
    while ((*data_echo)->str_s_quot[iterateur_s].str[i_past])
    {
        save[i][i_past] = (*data_echo)->str_s_quot[iterateur_s].str[i_past];
        i_past++;
    }

    save[i][i_past] = '\0';
    free((*data_echo)->str_s_quot[iterateur_s].str);
    // printf("\n|S|Je suis la nouvelle insertion |%s|\n", save[i]);
}
void ft_insert_new_data_with_data(char **save, t_echo **data_echo)
{
    (void)data_echo;
    int i;
    int iterateur_w;
    int iterateur_s;

    i = 0;
    // IL faut commencer a Introduire les nouvelles valeurs a l'interieuds de la base de donne
    while (i < (*data_echo)->w_quot + (*data_echo)->s_quot)
    {
        iterateur_s = 0;
        while (iterateur_s < (*data_echo)->s_quot)
        {
            if ((*data_echo)->str_s_quot[iterateur_s].order == i)
            {
                // Creation d'un boucle me permettant de free sans envoyer copier l'adresse
                ft_insert_data_data_echo_s(save, data_echo, i, iterateur_s);
                // (*data).arg[i] = (*data_echo)->str_s_quot[iterateur_s].str;
            }
            iterateur_s++;
        }
        iterateur_w = 0;
        while (iterateur_w < (*data_echo)->w_quot)
        {
            if ((*data_echo)->str_w_quot[iterateur_w].order == i)
            {
                ft_insert_data_data_echo_w(save, data_echo, i, iterateur_w);
            }
            iterateur_w++;
        }
        i++;
    }

    // if ((*data).arg[i] != NULL)
    // {
    //     while ((*data).arg[i] != NULL)
    //     {
    //         free((*data).arg[i]);
    //         (*data).arg[i] = NULL;
    //         i++;
    //     }
    // }
}

void ft_insert_data_s_whith_tab(t_echo **data_echo, char *input, int *i, int *clef_tab_s_quot)
{
    int iterateur_tab_s_quot;
    iterateur_tab_s_quot = 0;
    while (ft_isalnum(input[*i]) && input[*i] != '\0')
    {
        (*data_echo)->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = input[*i];

        (*i)++;
        iterateur_tab_s_quot++;
    }

    (*data_echo)->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = '\0';
    // printf("\nSave_with_tab_s|Nbr_occurence=%d|clef=%d|Save=%s|Sorti=%c", iterateur_tab_s_quot, (*clef_tab_s_quot), (*data_echo)->str_s_quot[(*clef_tab_s_quot)].str, input[*i]);
}

void ft_insert_data_w_whith_tab(t_echo **data_echo, char *input, int *i, int *clef_tab_w_quot)
{
    int iterateur_tab_w_quot;
    (void)data_echo;
    iterateur_tab_w_quot = 0;
    (*i) = (*i) + 1;
    while (input[*i] != '\0' && input[*i] != '"' && input[*i] != '\'')
    {
        // C'est le cas des doubles quot colle
        if ((*i) + 2 < ft_strlen(input) && (input[(*i) + 1] == '"' || input[(*i) + 1] == '\'') && (input[(*i) + 2] == '\'' || input[(*i) + 2] == '"'))
        {
            (*data_echo)->str_w_quot[(*clef_tab_w_quot)].str[iterateur_tab_w_quot] = input[*i];
            (*i)++;
            iterateur_tab_w_quot++;
            (*i) += 2;
        }
        (*data_echo)->str_w_quot[(*clef_tab_w_quot)].str[iterateur_tab_w_quot] = input[*i];
        iterateur_tab_w_quot++;
        (*i)++;
    }
    (*i)++;
    (*data_echo)->str_w_quot[(*clef_tab_w_quot)].str[iterateur_tab_w_quot] = '\0';
    // printf("\nSave_with_tab_w|Nbr_occurence=%d|clef=%d|Save=%s|Sorti=%c\n", iterateur_tab_w_quot, (*clef_tab_w_quot), (*data_echo)->str_w_quot[(*clef_tab_w_quot)].str, input[*i]);
}

void ft_insert_tab_echo(t_echo **data_echo, char *input, int i)
{
    int clef_tab_w_quot;
    int clef_tab_s_quot;

    clef_tab_s_quot = 0;
    clef_tab_w_quot = 0;
    // Creation d'une boucle permettant d'introduire dans le nouveau tableau
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        // Ce qui permet d'introduire dans le tableau nouvellement cree
        if ((input[i] == '"' || input[i] == '\'') && (input[i - 1] != '\'' && input[i - 1] != '"') && input[i] != '\0')
        {
            ft_insert_data_w_whith_tab(data_echo, input, &i, &clef_tab_w_quot);
            clef_tab_w_quot++;
        }
        if (ft_isalnum(input[i]) == 1)
        {
            ft_insert_data_s_whith_tab(data_echo, input, &i, &clef_tab_s_quot);
            clef_tab_s_quot++;
        }
        if ((!(input[i] != '"' || input[i] != '\'')) && input[i] != '\0')
            i++;
    }
}

void ft_insert_data_s_quot(t_echo **data_echo, char *input, int *i, int *place_tab_s_quot)
{
    int occurence;

    occurence = 0;

    while (ft_isalnum(input[*i]) == 1)
    {
        occurence++;
        (*i)++;
    }
    // Peux d'autre conditions a verifier ici
    (*data_echo)->str_s_quot[(*place_tab_s_quot)].order = (*data_echo)->order_occurence;
    (*data_echo)->order_occurence++;
    printf("\nTABS|PLace|%d|Nbr occurence|%d|Place_tab|%d|", (*data_echo)->str_s_quot[(*place_tab_s_quot)].order, occurence, (*place_tab_s_quot));
    (*data_echo)->str_s_quot[(*place_tab_s_quot)].str = malloc(sizeof(char *) * occurence + 1);
    (*place_tab_s_quot)++;
}

void ft_insert_data_w_quot(t_echo **data_echo, char *input, int *i, int *place_tab_w_quot)
{
    int occurence;
    occurence = 0;

    (*i) = (*i) + 1;
    while (input[*i] != '\0' && input[*i] != '"' && input[*i] != '\'')
    {
        if ((*i) + 2 < ft_strlen(input) && (input[(*i) + 1] == '"' || input[(*i) + 1] == '\'') && (input[(*i) + 2] == '\'' || input[(*i) + 2] == '"'))
            (*i) += 2;
        (*i)++;
        occurence++;
    }
    (*i)++;
    (*data_echo)->str_w_quot[(*place_tab_w_quot)].order = (*data_echo)->order_occurence;
    printf("\n|TABW|Place|%d|Nbr occurence|%d|Place_tab|%d|\n", (*data_echo)->str_w_quot[(*place_tab_w_quot)].order, occurence, (*place_tab_w_quot));
    (*data_echo)->order_occurence++;
    (*data_echo)->str_w_quot[(*place_tab_w_quot)].str = malloc(sizeof(char *) * occurence + 1);
    // Il faut proteger le malloc
    (*place_tab_w_quot)++;
}

void ft_init_tab_echo_malloc(t_echo **data_echo, char *input, int i)
{

    int place_tab_w_quot;
    int place_tab_s_quot;

    place_tab_s_quot = 0;
    place_tab_w_quot = 0;
    (*data_echo)->order_occurence = 0;
    // Cette fonction permetd e determiner le nombre d'occurence dans le tableau
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        if ((input[i] == '"' || input[i] == '\'') && (input[i - 1] != '\'' && input[i - 1] != '"'))
        {
            if (i + 2 < ft_strlen(input) && (input[i + 1] == '"' || input[i + 1] == '\'') && (input[i + 2] == '\'' || input[i + 2] == '"'))
                i += 2;
            ft_insert_data_w_quot(data_echo, input, &i, &place_tab_w_quot);
        }
        if (ft_isalnum(input[i]) == 1 && input[i] != '\'' && input[i] != '"' && input[i] != '\'' && input[i] != '"')
        {
            ft_insert_data_s_quot(data_echo, input, &i, &place_tab_s_quot);
        }
        if (!(input[i] != '"' || input[i] != '\''))
            i++;
    }
}

int ft_init_token_space(t_echo **data_echo, char *input, int i)
{
    // Cette fonction permet de calculer le nombre de quot
    int ss_quot = 0;
    int wt_quot = 0;

    if (ft_nbr_quot(input, i) == 1)
    {
        printf("Ce n'est pas paire ");
        return (1);
    }
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        if ((input[i] == '"' || input[i] == '\'') && (input[i - 1] != '\'' && input[i - 1] != '"'))
        {
            i++;
            while (input[i] != '\0' && input[i] != '"' && input[i] != '\'')
            {
                if (i + 2 < ft_strlen(input) && (input[i + 1] == '"' || input[i + 1] == '\'') && (input[i + 2] == '\'' || input[i + 2] == '"'))
                    i += 2;
                i++;
            }
            wt_quot++;
            i++;
        }
        if (ft_isalnum(input[i]) == 1 && input[i] != '"' && input[i] != '\'')
        {
            while (ft_isalnum(input[i]) == 1 && input[i] != '\'' && input[i] != '"')
                i++;
            ss_quot++;
        }
        if (!(input[i] != '"' || input[i] != '\''))
            i++;
    }
    (*data_echo)->s_quot = ss_quot;
    (*data_echo)->w_quot = wt_quot;
    printf("S_quot = |%d| W_quot|%d|", (*data_echo)->s_quot, (*data_echo)->w_quot);
    return(0);
}

int ft_nbr_quot(char *input, int i)
{
    int search;
    int result;

    result = 0;
    search = i;
    printf("\nft_nrb_echo de |%s|\n", input);

    while (input[search])
    {
        if ( input[search] == '"')
        {

            result++;
        }
        search++;
    }
    printf("Je suis result + %d", result);
    if (result % 2 == 0)
    {
        printf("\nC'est un nombre pair\n");
        return (0);
    }
    else
    {
        printf("\nCe n'est pas un nombre pair");
        return (1);
    }
}

int ft_isalnum(int c)
{
    if ((c >= 48 && c <= 57) || (c >= 97 && c <= 122) || (c >= 65 && c <= 90))
        return (1);
    else
        return (0);
}

void free_tokens(char **tokens, int len)
{
    if (tokens == NULL)
    {
        return;
    }

    int i = 0;
    while (i < len)
    {
        if (tokens[i] != NULL)
        {
            free(tokens[i]);
        }
        i++;
    }

    free(tokens);
}

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return i;
}
void *ft_bzero(void *s, size_t n)
{
    return (ft_memset(s, 0, n));
}
void *ft_memset(void *s, int c, size_t n)
{
    unsigned long i;
    unsigned char *t;

    t = (unsigned char *)s;
    i = 0;
    while (i != n)
        t[i++] = c;
    return (s);
}
void *ft_calloc(size_t elementCount, size_t elementSize)
{
    size_t mem_size;
    void *mem_init;

    if (elementCount <= 0 || elementSize <= 0)
        return (malloc(0));
    if ((long long)elementCount < 0 || (long long)elementSize < 0)
        return (0);
    mem_size = elementCount * elementSize;
    mem_init = malloc(mem_size);
    if (!(mem_init))
        return (NULL);
    return (ft_bzero(mem_init, mem_size));
}
char *ft_strjoin(char const *s1, char const *s2)
{
    char *str_dest;
    size_t len_dest;
    size_t i;

    if (!s1 || !s2)
        return (0);
    len_dest = (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
    str_dest = (char *)ft_calloc(len_dest, 1);
    if (str_dest == 0)
        return (0);
    i = 0;
    while (*s1 != 0)
    {
        str_dest[i] = *s1++;
        i++;
    }
    while (*s2 != 0)
    {
        str_dest[i] = *s2++;
        i++;
    }
    str_dest[i] = 0;
    return (str_dest);
}

char **split_string(char *str, int *len)
{
    int count = 0;
    int i = 0;
    int j = 0;
    int in_quotes = 0;
    char **tokens = malloc(sizeof(char *) * 100);

    while (str[i] != '\0')
    {
        if (str[i] == '"')
            in_quotes = !in_quotes;
        if (str[i] == '|' && !in_quotes)
        {
            str[i] = '\0';
            tokens[count] = malloc(sizeof(char) * (i - j + 1));
            strcpy(tokens[count], str + j);
            count++;
            j = i + 1;
        }
        i++;
    }
    tokens[count] = malloc(sizeof(char) * (i - j + 1));
    strcpy(tokens[count], str + j);
    count++;
    *len = count;
    return tokens;
}

char *ft_strdup(char *src)
{
    int i;
    char *dest;

    if (!src)
        return (NULL);
    i = ft_strlen(src);
    dest = (char *)malloc(sizeof(char) * (i + 1));
    if (dest == 0)
        return (0);
    dest[i] = '\0';
    while (i-- != 0)
        dest[i] = src[i];
    return (dest);
}
