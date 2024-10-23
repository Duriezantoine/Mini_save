/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:51:14 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/23 16:26:43 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_white_space(char c)
{
    if ((c >= 8 && c <=13) || c == ' ')
        return(1);
    return(0);
}
static unsigned int	get_sign(int n, int *sign, int *inc)
{
	if (n < 0)
	{
		*sign = 1;
		(*inc)++;
		return (-n);
	}
	*sign = 0;
	return (n);
}

static unsigned int	get_len(unsigned int nd)
{
	unsigned int	i;

	i = 0;
	while (nd)
	{
		nd /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				i;
	int				sign;
	unsigned int	nd;
	char			*ret;

	i = 0;
	sign = 0;
	nd = get_sign(n, &sign, &i);
	i += get_len(nd);
	if (n == 0)
		return (ft_strdup("0"));
	ret = (char *)ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	if (sign)
		ret[0] = '-';
	while (nd)
	{
		ret[--i] = nd % 10 + '0';
		nd /= 10;
	}
	return (ret);
}

static char	*handle_exit_code(char *save, char *search, t_data *data)
{
   char	*tmp_tmp;
   char	*tmp_save;

   tmp_tmp = ft_itoa(data->exit_code);
   tmp_save = ft_strjoin(tmp_tmp, save + 1);
   free(tmp_tmp);
   free(save);
   free(search);
   return (tmp_save);
}

static char	*find_env_value(char *save, char *search, t_env *env)
{
    char	*tmp_save;

    while (env)
    {
        if (strequ(save, env->key))
        {
            tmp_save = ft_strdup(env->value);
            free(save);
            free(search);
            return (tmp_save);
        }
        env = env->next;
    }
    free(save);
    return (search);
}

char	*ft_change_var_environnement(char *search, t_env **env, t_data *data)
{
    char	*save;

    save = ft_copy_end(search, '$');
    if (save[0] == '?')
        return (handle_exit_code(save, search, data));
    return (find_env_value(save, search, *env));
}

char *ft_strcat(char *dest, char src)
{
    char *original_dest = dest;
    while (*dest != '\0')
    {
        dest++;
    }
    *dest = src;
    dest++;
    *dest = '\0';
    return original_dest;
}

char *ft_strcpy(char *dest, char *src)
{
    char *original_dest;
    
    original_dest = dest;
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return original_dest;
}

int ft_strcmp(char *s1, char *s2)
{
    int c;

    c = 0;
    while (s1[c] == s2[c] && (s1[c] != '\0' && s2[c] != '\0'))
        c++;
    return (s1[c] - s2[c]);
}

int ft_split_with_space(t_echo *data_echo, char *input)
{
    if (ft_init_token_space(data_echo, input, 0) == 1)
        return (1);
    ft_init_echo_malloc(data_echo);
    ft_init_tab_echo_malloc(data_echo, input, 0);
    ft_insert_tab_echo(data_echo, input, 0);
    return (0);
}

void ft_insert_data_data_echo_w(t_save **save, t_echo *data_echo, int iterateur_w)
{
    t_save *new_node;
    t_save *current;

    new_node = malloc(sizeof(t_save));
    if (!new_node)
        return;
    new_node->str = malloc(sizeof(char) * ft_strlen(data_echo->str_w_quot[iterateur_w].str) + 1);
    if (!new_node->str)
    {
        free(new_node);
        return;
    }
    strcpy(new_node->str, data_echo->str_w_quot[iterateur_w].str);
    new_node->bool = data_echo->str_w_quot[iterateur_w].bool;
    new_node->next = NULL;
    if (*save == NULL)
        *save = new_node;
    else
    {
        current = *save;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void ft_insert_data_data_echo_s(t_save **save, t_echo *data_echo, int iterateur_s, t_env *env)
{
    t_save *new_node = ft_calloc(sizeof(t_save), 1);
    t_save *current;

    (void)env;
    if (!new_node)
        return;
    new_node->str = ft_strdup(data_echo->str_s_quot[iterateur_s].str);
    data_echo->str_s_quot[iterateur_s].order = -2;
    new_node->bool = data_echo->str_s_quot[iterateur_s].bool;
    new_node->next = NULL;
    if (*save == NULL)
        *save = new_node;
    else
    {
        current = *save;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void ft_insert_new_data_with_data(t_save **save, t_echo *data_echo, t_env *env)
{
    int i;
    int iterateur_w;
    int iterateur_s;

    (void)data_echo;
    i = -1;
    while (++i < data_echo->w_quot + data_echo->s_quot)
    {
        iterateur_s = 0;
        while (iterateur_s < data_echo->s_quot)
        {
            if (data_echo->str_s_quot[iterateur_s].order == i)
                ft_insert_data_data_echo_s(save, data_echo, iterateur_s, env);
            iterateur_s++;
        }
        iterateur_w = 0;
        while (iterateur_w < data_echo->w_quot)
        {
            if (data_echo->str_w_quot[iterateur_w].order == i)
                ft_insert_data_data_echo_w(save, data_echo, iterateur_w);
            iterateur_w++;
        }
    }
}

void ft_insert_data_s_whith_tab(t_echo *data_echo, char *input, int *i, int *clef_tab_s_quot)
{
    int     iterateur_tab_s_quot;
    char    sep;

    iterateur_tab_s_quot = 0;
    while (ft_isalnum(input[*i]) && input[*i] != '\0')
    {
        if (input[*i]=='\'' || input[*i]=='"')
        {
            sep = input[*i];
            data_echo->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = input[*i];
            (*i)++;
            iterateur_tab_s_quot++;
            while(input[*i] != sep && input[*i] != '\0')
            {
                data_echo->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = input[*i];
                (*i)++;
                iterateur_tab_s_quot++;
            }
        }
        data_echo->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = input[*i];
        (*i)++;
        iterateur_tab_s_quot++;
    }
    data_echo->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = '\0';
    data_echo->str_s_quot[(*clef_tab_s_quot)].bool = 0;
}
static void	handle_redirection(t_echo *data_echo, char *input, 
	int *i, int *clef_tab_s_quot)
{
	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
	{
		data_echo->str_s_quot[*clef_tab_s_quot].str[0] = input[*i];
		data_echo->str_s_quot[*clef_tab_s_quot].str[1] = input[*i];
		data_echo->str_s_quot[*clef_tab_s_quot].str[2] = '\0';
		data_echo->str_s_quot[*clef_tab_s_quot].bool = 2;
		*i += 2;
	}
	else
	{
		data_echo->str_s_quot[*clef_tab_s_quot].str[0] = input[*i];
		data_echo->str_s_quot[*clef_tab_s_quot].str[1] = '\0';
		data_echo->str_s_quot[*clef_tab_s_quot].bool = 2;
		(*i)++;
	}
	(*clef_tab_s_quot)++;
}

static void	handle_quotes(t_echo *data_echo, char *input,
	int *i, int *clef_tab_w_quot)
{
	if (input[*i + 1] != input[*i])
	{
		ft_insert_data_w_whith_tab(data_echo, input, i, clef_tab_w_quot);
		(*clef_tab_w_quot)++;
	}
	else
		*i = *i + 2;
}

void	ft_insert_tab_echo(t_echo *data_echo, char *input, int i)
{
	int	clef_tab_w_quot;
	int	clef_tab_s_quot;

	clef_tab_w_quot = 0;
	clef_tab_s_quot = 0;
	while (input[i])
	{
		while (ft_white_space(input[i]))
			i++;
		if ((input[i] == '"' || input[i] == '\'') && input[i] != '\0')
			handle_quotes(data_echo, input, &i, &clef_tab_w_quot);
		if (input[i] == '<' || input[i] == '>')
			handle_redirection(data_echo, input, &i, &clef_tab_s_quot);
		if (ft_isalnum(input[i]) == 1)
		{
			ft_insert_data_s_whith_tab(data_echo, input,
				&i, &clef_tab_s_quot);
			clef_tab_s_quot++;
		}
	}
}

void ft_insert_data_s_quot(t_echo *data_echo, char *input, int *i, int *place_tab_s_quot)
{
    int occurence;
    char c;

    occurence = 0;
    while (ft_isalnum(input[*i]) == 1  && input[*i] != '\0')
    {

            if(input[*i]=='\'' || input[*i]== '"')
            {
                 c = input[*i]; 
                (*i)++;
                occurence++;
                while(input[*i] != c )
                {
                    (*i)++;
                    occurence++;
                }
            }
        ((*i)++);
        occurence++;
     }
    data_echo->str_s_quot[(*place_tab_s_quot)].order = data_echo->order_occurence;
    data_echo->order_occurence++;
    data_echo->str_s_quot[(*place_tab_s_quot)].str = malloc(sizeof(char *) * occurence +1 );
    (*place_tab_s_quot)++;
}

static int  ft_insert_data_loop(char *input, int *i, char *c, int *occ)
{
    while (input[*i] != '\0' && input[*i] != *c)
    {
        (*i)++;
        (*occ)++;
    }
    if(input[*i]== '\0')
        return (1);
    (*occ)++;
    if(ft_white_space(input[(*i)++]) || input[*i]== '\0')
        return (1);
    while (((ft_isalnum(input[*i]) == 1)  && input[*i] != '\0')
        && input[*i] != '\'' && input[*i] != '"')
    {
        (*occ)++;
        (*i)++;
    }
    if(ft_white_space(input[*i]) || input[*i]== '\0')
        return (1);
    if(input[*i]== '\'' || input[*i]== '"')
    {
        *c = input[*i];
        (*occ)++;
        (*i)++;  
    }
    return (0);
}

void ft_insert_data_w_quot(t_echo *data, char *input, int *i, int *place_tab_w_quot)
{
    int     occ;
    char    c;
    
    c = input[*i];
    (*i) = (*i) + 1;
    occ = 1;
    while (input[*i] != '\0' && input[*i] != c)
    {
        if (ft_insert_data_loop(input, i, &c, &occ))
            break;
    }
    data->str_w_quot[(*place_tab_w_quot)].order = data->order_occurence++;
    data->str_w_quot[(*place_tab_w_quot)].str = malloc(sizeof(char *) * occ + 1);
    (*place_tab_w_quot)++;
}

static void	handle_redirection_malloc(t_echo *data_echo, char *input,
	int *i, int *place_tab_s_quot)
{
	data_echo->str_s_quot[*place_tab_s_quot].order
		= data_echo->order_occurence++;
	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
	{
		data_echo->str_s_quot[*place_tab_s_quot].str
			= malloc(sizeof(char *) * 2 + 1);
		(*place_tab_s_quot)++;
		*i += 2;
	}
	else
	{
		data_echo->str_s_quot[*place_tab_s_quot].str
			= malloc(sizeof(char *) * 1 + 1);
		(*place_tab_s_quot)++;
		(*i)++;
	}
}

static void	handle_quotes_malloc(t_echo *data_echo, char *input,
	int *i, int *place_tab_w_quot)
{
	if (input[*i] != input[*i + 1])
		ft_insert_data_w_quot(data_echo, input, i, place_tab_w_quot);
	else
		*i += 2;
}

void	ft_init_tab_echo_malloc(t_echo *data_echo, char *input, int i)
{
	int	place_tab_w_quot;
	int	place_tab_s_quot;

	place_tab_s_quot = 0;
	place_tab_w_quot = 0;
	data_echo->order_occurence = 0;
	while (input[i])
	{
		while (ft_white_space(input[i]))
			i++;
		if (input[i] == '"' || input[i] == '\'')
			handle_quotes_malloc(data_echo, input,
				&i, &place_tab_w_quot);
		if (input[i] == '<' || input[i] == '>')
			handle_redirection_malloc(data_echo, input,
				&i, &place_tab_s_quot);
		if (ft_isalnum(input[i]) == 1 && !ft_white_space(input[i]))
			ft_insert_data_s_quot(data_echo, input,
				&i, &place_tab_s_quot);
	}
}

int ft_handle_alphanumeric(char *input, int *i, int *ss_quot, int x)
{
    // printf("\n2Je suis input[i]|input|%c||\n",input[*i]);
    if(x==1)
    {
        (*ss_quot)++;
    }
    // printf("Je suis i|%c|?", input[*i]);
    char c;
    if(input[*i] == '\0' && ft_white_space(input[*i]))
     {
        return 1;
     }
    if (((ft_isalnum(input[*i]) == 1) && input[*i] != '\0') && (!ft_white_space(input[*i])) )
    {
            // printf("\n3Je suis? input[i]|input|%c||\n",input[*i]);

        while (((ft_isalnum(input[*i]) == 1))  && input[*i] != '\0' && !ft_white_space(input[*i]))
        {
                //  printf(?"XX");
                // printf("\n4.5Je suis in?put[i]|input|%c||\n",input[*i]);

            if(input[*i]=='"' || input[*i] == '\'')
            {
                 c = input[*i];
                //  printf("\n4.6Je s?uis input[i]|input|%c||\n",input[*i]);

                (*i)++; 
                while(input[*i] != c && input[*i] != '\0' )
                {
                    // printf("\n4.5Je ?suis input[i]|input|%c||\n",input[*i]);

                    (*i)++;
                }
                //  printf("\n8e suis? input[i]|input|%c||\n",input[*i]);

            }
            (*i)++;
        }
    }
    // printf("\n5Je suis input[i]|in?put|%c|i=%d|\n",input[*i], *i);

    return 1;
}

int ft_handle_quotes(char *input, int *i, int *wt_quot, char c)//Faire avec plusir char
{
    (*i)++;
    while (input[*i] != '\0'&& input[*i] != c  )
    {
        // printf("1Je suis c|%c|i=|%d|input|%c|\n", c, *i, input[*i]);
        while(input[*i] )
        {
            // printf("2wJe suis c|%c|i=|%d|\n", input[*i], *i);
            (*i)++;
            if(input[*i]== c)
                break;
        }
        // printf("3Je suis c|%c|i=|%d|input|%c|\n", c, *i, input[*i]);
        if (input[*i] == '\0' || ft_white_space(input[*i]))
            break;   
        //  printf("4Je suis c|%c|i=|%d|input|%c|\n", c, *i, input[*i]);

        while (((ft_isalnum(input[*i]) == 1)  && input[*i] != '\0') && input[*i] != '\'' && input[*i] != '"')
        {
            // printf("5Je suis c|%c|i=|%d|input|%c|\n", c, *i, input[*i]);
            (*i)++;
        }
        // printf("6Je suis c|%c|i=|%d|input|%c|\n", c, *i, input[*i]);

        (*i)++;
            if (input[*i] == '\0' || ft_white_space(input[*i]))
            break;   
        // printf("7Je suis c|%c|i=|%d|input|%c|\n", c, *i, input[*i]);

        if(input[*i]== '\'' || input[*i]== '"')
        {
            c = input[*i];
            (*i)++;  
        }

    }
    // printf("2je suis input|%c|\n    ", input[*i]);
    (*wt_quot)++;
    return 0;
}

int ft_init_token_space(t_echo *data_echo, char *input, int i)
{
    // Cette fonction permet de calculer le nombre de quot
    int ss_quot = 0;
    int wt_quot = 0;
        
    // if (ft_nbr_quot(input, i) == 1)//IL faut le faire avant
    // {
    //     printf("Ce n'est pas paire ");//Il faut faire une sortie d'erreur ici
    //     return (1);
    // }
    // printf("\nstr|%s|\n", input);   
    while (input[i])
    {
        while (ft_white_space(input[i]))
            i++;
        if ((input[i] == '"' || input[i] == '\''))
        {
            if(input[i+1] != input[i])
            {// printf("\nStart|%c|\n",input[i]);
                ft_handle_quotes(input, &i, &wt_quot, input[i]);
            // printf("\nEnd|%c|\n",input[i]);
            }
            else
            {
                i++;
                if (input[i] != '\0')
                    i++;
            }
        }

        if(input[i]== '\0')
            break;
        ft_handle_redirection(input, &i, &ss_quot);
    //    printf("\n1Je suis input[i]|input|%c|i=%d|\n",input[i], i);
        if (((ft_isalnum(input[i]) == 1)) && !ft_white_space(input[i]) )
            ft_handle_alphanumeric(input, &i, &ss_quot, 1);
        // printf("\n1End|%c|\n",input[i]);

        if (input[i] == '\0')
            break;
        if(ft_white_space(input[i]))
            i++;    
    }
    data_echo->s_quot = ss_quot;
    data_echo->w_quot = wt_quot;
    // printf("S_quot = |%d| W_quot|%d|\n", data_echo->s_quot, data_echo->w_quot);
    return (0);
}

int ft_handle_redirection(char *input, int *i, int *ss_quot)
{
    if (input[*i] == '<' || input[*i] == '>')
    {
        if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>' && input[*i + 1] == '>'))
        {
            *i += 2;
            (*ss_quot)++;
        }
        else
        {
            (*i)++;
            (*ss_quot)++;
        }
    }
    return 0;
}

int ft_nbr_quot(char *input, int i)
{
    int search;
    int result;

    result = 0;
    search = i;
    while (input[search])
    {
        if (input[search] == '"')
        {

            result++;
        }
        search++;
    }
    if (result % 2 == 0)
        return (0);
    else
        return (1);
}

int ft_isalnum(int c)
{
    // if (c == '<' || c == '>' || c == '|' || c == ' ')
    //     return 0;
    // return (1);
    if ((c =='?')|| (c== '$') || (c == ':') ||(c == ')')||(c== '_') || (c == '^')||(c >= 48 && c <= 57) || (c >= 97 && c <= 122) || (c >= 65 && c <= 90) || (c == 45) || (c == 61) || (c==46) || (c == 126) || (c == 47) || (c == 43) || (c==36) || (c ==95) || c == '"' || (c=='\'') || c == '.' || c == ',' )
    {
        // if (c == 45)
        return (1);
    }
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
        if (str[i] == '"' || str[i]== '\'')
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
    dest = (char *)ft_calloc(i + 1, sizeof(char));
    if (dest == 0)
        return (0);
    while (i-- != 0)
        dest[i] = src[i];
    return (dest);
}
