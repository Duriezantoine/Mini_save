/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:51:14 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/19 17:05:57 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char    *ft_change_var_environnement(char *search, t_env **env, t_data *data)
{
	t_env *tmp;
	tmp = *env;
    char *save;
    char *tmp_save;
    save = ft_copy_end(search, '$');
    char *tmp_tmp;
    if (save[0] == '?')
    { 
        tmp_tmp = ft_itoa(data->exit_code);
        tmp_save = ft_strjoin(tmp_tmp, save + 1);
        free(tmp_tmp);
        free(save);
        free(search);
        return (tmp_save);
    }
        
	while(tmp)
	{
        if(strequ(save, tmp->key)) {
				tmp_save = ft_strdup(tmp->value);
                 free(save);
                 free(search);
                return(tmp_save);
        }		
		tmp = tmp->next;
	}
    free(save);
    return(search);
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
    char *original_dest = dest; // Sauvegarder la position initiale de dest

    // Copier chaque caractère de src vers dest
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }

    // Ajouter le caractère de fin de chaîne à dest
    *dest = '\0';

    return original_dest; // Retourner la position initiale de dest
}

int ft_strcmp(char *s1, char *s2)
{
    int c;

    c = 0;
   // printf("S1=|%s|S2=|%s|", s1, s2);
    while (s1[c] == s2[c] && (s1[c] != '\0' && s2[c] != '\0'))
        c++;
    return (s1[c] - s2[c]);
}

int ft_split_with_space(t_echo *data_echo, char *input)
{
    // printf("INPUT = |%s|", input);
    if (ft_init_token_space(data_echo, input, 0) == 1)//it's ok;
        return (1);
    ft_init_echo_malloc(data_echo);
    // printf("1\n");
    ft_init_tab_echo_malloc(data_echo, input, 0);
        // printf("2\n");

    ft_insert_tab_echo(data_echo, input, 0);
        // printf("3\n");

    // Il faut recrer une fonction permettant de free a la toutes fin ne pas
    return (0);
}

void ft_insert_data_data_echo_w(t_save **save, t_echo *data_echo, int iterateur_w)
{
    t_save *new_node = malloc(sizeof(t_save));
    if (!new_node)
    {
        // Gestion de l'erreur d'allocation
        return;
    }

    new_node->str = malloc(sizeof(char) * ft_strlen(data_echo->str_w_quot[iterateur_w].str) + 1);
    if (!new_node->str)
    {
        // Gestion de l'erreur d'allocation
        free(new_node);
        return;
    }

    strcpy(new_node->str, data_echo->str_w_quot[iterateur_w].str);
   printf("Voila ce que je viens d'inserer |%s|\n", new_node->str);

    new_node->bool = data_echo->str_w_quot[iterateur_w].bool; // Initialisation de l'attribut bool (vous pouvez le définir selon vos besoins)
    new_node->next = NULL;

    // Insérer le nouveau nœud à la fin de la liste
    if (*save == NULL)
    {
        *save = new_node;
    }
    else
    {
        t_save *current = *save;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

void ft_insert_data_data_echo_s(t_save **save, t_echo *data_echo, int iterateur_s, t_env *env)
{
    (void)env;
    t_save *new_node = ft_calloc(sizeof(t_save), 1);//Calloc plus propre//Des noe
    if (!new_node)
    {
        // Gestion de l'erreur d'allocation
        return;
    }

    
    new_node->str= ft_strdup(data_echo->str_s_quot[iterateur_s].str );
    printf("1Voila ce que je viens d'inserer |%s|\n", new_node->str);
    data_echo->str_s_quot[iterateur_s].order =-2;
    new_node->bool = 0; // Initialisation de l'attribut bool (vous pouvez le définir selon vos besoins)
    new_node->next = NULL;

    // Insérer le nouveau nœud à la fin de la liste
    if (*save == NULL)
    {
        // printf("\nDebut du noeuds\n");
        *save = new_node;
    }
    else
    {
        t_save *current = *save;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }

    // Libération de la mémoire si nécessaire
    // free(data_echo->str_s_quot[iterateur_s].str); // Assurez-vous que cela est correct dans votre contexte
}

void ft_insert_new_data_with_data(t_save **save, t_echo *data_echo, t_env *env)
{
    (void)data_echo;
    int i;
    int iterateur_w;
    int iterateur_s;
    i = -1;
    // IL faut commencer a Introduire les nouvelles valeurs a l'interieuds de la base de donne
    while (++i < data_echo->w_quot + data_echo->s_quot)//Bonne pratique
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
            // printf("NBRQUOT|data_echo->|%d|",data_echo->w_quot );
            if (data_echo->str_w_quot[iterateur_w].order == i)
                ft_insert_data_data_echo_w(save, data_echo, iterateur_w);
            iterateur_w++;
        }
    }
    // save[i] = NULL;
}

void ft_insert_data_s_whith_tab(t_echo *data_echo, char *input, int *i, int *clef_tab_s_quot)
{
    int iterateur_tab_s_quot;
    iterateur_tab_s_quot = 0;
    while (ft_isalnum(input[*i]) && input[*i] != '\0')
    {
        // if(input[*i]== '<' || input[*i] == '>')
        // {
        //     (*i)--;
        //     break;

        // }
          if(input[*i]=='\'')
            {
                data_echo->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = input[*i];
                (*i)++;
                iterateur_tab_s_quot++;
                while(input[*i] != '\'' && input[*i] != '\0')
                {
                    data_echo->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = input[*i];
                    (*i)++;
                    iterateur_tab_s_quot++;
                }
                data_echo->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = input[*i];
                iterateur_tab_s_quot++;
                (*i)++;
            }
          else  if(input[*i]=='"')
            {
                data_echo->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = input[*i];
                (*i)++; 
                iterateur_tab_s_quot++;
                while(input[*i] != '"'  )
                {
                    data_echo->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = input[*i];
                    (*i)++;
                    iterateur_tab_s_quot++;

                }
                data_echo->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = input[*i];
                iterateur_tab_s_quot++;
                (*i)++;
            }
        else
        {
            data_echo->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = input[*i];
            (*i)++;
            iterateur_tab_s_quot++;
        }
        
    }
    data_echo->str_s_quot[(*clef_tab_s_quot)].str[iterateur_tab_s_quot] = '\0';
    // printf("\n1Sorti de la boucle|%c|save=|%s|clefTab=|%d|\n", input[*i],  data_echo->str_s_quot[(*clef_tab_s_quot)].str,(*clef_tab_s_quot));

    data_echo->str_s_quot[(*clef_tab_s_quot)].bool = 0;

//    printf("\nSave_with_tab_s|Nbr_occurence=%d|clef=%d|Save=|%s|Sorti=%c\n", iterateur_tab_s_quot, (*clef_tab_s_quot), data_echo->str_s_quot[(*clef_tab_s_quot)].str, input[*i]);
    // printf("\n2Sorti de la boucle|%c|\n", input[*i]);

}

void ft_insert_data_w_whith_tab(t_echo *data_echo, char *input, int *i, int *clef_tab_w_quot)
{
    int iterateur_tab_w_quot;
    (void)data_echo;
    iterateur_tab_w_quot = 0;
    // printf("\nICI|%c|\n", input[*i]);
    char c = input[*i];
    // printf("1\ninput|%c|    ",input[*i]);
    data_echo->str_w_quot[(*clef_tab_w_quot)].str[iterateur_tab_w_quot] = input[*i];
    iterateur_tab_w_quot++;


    if (input[*i] == '\'')
        data_echo->str_w_quot[(*clef_tab_w_quot)].bool = 1;
    else
        data_echo->str_w_quot[(*clef_tab_w_quot)].bool = 0;
    (*i) = (*i) + 1;
    // printf("2\ninput|%c|    ",input[*i]);



    while (input[*i] != '\0' && input[*i] != c)
    {
        while (input[*i] != '\0' && input[*i] != c)
        {
                    // printf("3\ninput|%c|    ", input[*i]);

                data_echo->str_w_quot[(*clef_tab_w_quot)].str[iterateur_tab_w_quot] = input[*i];
                (*i)++;
                iterateur_tab_w_quot++;
        }
        if (input[*i] == '\0')
            break;   
        // printf("4\ninput|%c|    ",input[*i]);
        
        data_echo->str_w_quot[(*clef_tab_w_quot)].str[iterateur_tab_w_quot] = input[*i];
        (*i)++;
        iterateur_tab_w_quot++;
        // printf("4=input|%c|d|%d|\n", input[*i], *i);
        if(input[*i] == ' ')
            break;
         while ((ft_isalnum(input[*i]) == 1) && input[*i] != '\'' && input[*i] != '"')
        {
            // printf("5Je suis c|%c|i=|%d|input|%c|\n", c, *i, input[*i]);
            data_echo->str_w_quot[(*clef_tab_w_quot)].str[iterateur_tab_w_quot] = input[*i];
            (*i)++;
            iterateur_tab_w_quot++;
        }
            // printf("6=input|%c|d|%d|\n", input[*i], *i);
        if(input[*i]== '\'' || input[*i]== '"')
        {
            c = input[*i];
            data_echo->str_w_quot[(*clef_tab_w_quot)].str[iterateur_tab_w_quot] = input[*i];
            (*i)++;
            iterateur_tab_w_quot++;
        }
        // printf("7 =input|%c|d|%d|\n", input[*i], *i);

    }
    data_echo->str_w_quot[(*clef_tab_w_quot)].str[iterateur_tab_w_quot] = '\0';
    // printf("\nSave_with_tab_w|Nbr_occurence=%d|clef=%d|Save=|%s|Sorti=%c\n", iterateur_tab_w_quot, (*clef_tab_w_quot), data_echo->str_w_quot[(*clef_tab_w_quot)].str, input[*i]);
}

void ft_insert_tab_echo(t_echo *data_echo, char *input, int i)
{
    int clef_tab_w_quot;
    int clef_tab_s_quot;

    clef_tab_s_quot = 0;
    clef_tab_w_quot = 0;
    // printf("INPUT=|%s|", input);
    // Creation d'une boucle permettant d'introduire dans le nouveau tableau
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        // Ce qui permet d'introduire dans le tableau nouvellement cree
        if ((input[i] == '"' || input[i] == '\'')&& input[i] != '\0')
        {
            if(input[i+1]!='\'')
            {
                ft_insert_data_w_whith_tab(data_echo, input, &i, &clef_tab_w_quot);
                clef_tab_w_quot++;
            }
            else
                i= i+2;
        }
        if(input[i]== '<' || input[i]== '>')
        {
            if((input[i]== '<' && input[i+1] == '<')||(input[i]== '>' && input[i+1] == '>'))
            {
                data_echo->str_s_quot[clef_tab_s_quot].str[0] = input[i];
                data_echo->str_s_quot[clef_tab_s_quot].str[1] = input[i];
                data_echo->str_s_quot[clef_tab_s_quot].str[2] = '\0';
                data_echo->str_s_quot[clef_tab_s_quot].bool = 0;
                // printf("\nnnSave_with_tab_s|Nbr_occurence=%d|clef=%d|Save=|%s|Sorti=%c", 1, clef_tab_s_quot, data_echo->str_s_quot[clef_tab_s_quot].str, input[i]);
                clef_tab_s_quot++;
                i = i+2;
            }
            else
            {
            // printf("\nJe suis input=%c\n", input[i]);
                data_echo->str_s_quot[clef_tab_s_quot].str[0] = input[i];
                data_echo->str_s_quot[clef_tab_s_quot].str[1] = '\0';
                data_echo->str_s_quot[clef_tab_s_quot].bool = 0;
                // printf("\nnnSave_with_tab_s|Nbr_occurence=%d|clef=%d|Save=%s|Sorti=%c", 1, clef_tab_s_quot, data_echo->str_s_quot[clef_tab_s_quot].str, input[i]);
                clef_tab_s_quot++;
                i++;
            }

        }
        if ((ft_isalnum(input[i]) == 1))
        {
            ft_insert_data_s_whith_tab(data_echo, input, &i, &clef_tab_s_quot);
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
    //  printf("OCCURRENCE|%d|", occurence);
    // Peux d'autre conditions a verifier ici
    data_echo->str_s_quot[(*place_tab_s_quot)].order = data_echo->order_occurence;
    data_echo->order_occurence++;
    // printf("\nTABS|PLace|%d|Nbr occurence|%d|Place_tab|%d|", data_echo->str_s_quot[(*place_tab_s_quot)].order, occurence, (*place_tab_s_quot));
    data_echo->str_s_quot[(*place_tab_s_quot)].str = malloc(sizeof(char *) * occurence +1 );
    //IL faut faire une protection de mall9oc dans ce cas la
    (*place_tab_s_quot)++;
}

void ft_insert_data_w_quot(t_echo *data_echo, char *input, int *i, int *place_tab_w_quot)
{
    int occurence;
    occurence = 0;
    // char *c;
    char c = input[*i];
    (*i) = (*i) + 1;
    occurence += 1;
    // printf("1IMPUT|%c|",input[*i] );
    while (input[*i] != '\0' && input[*i] != c)
    {
            // printf("2IMPUT|%c|",input[*i] );

        while (input[*i] != '\0'  )
        {
                // printf("3IMPUT|%c|",input[*i] );

            (*i)++;
            occurence++;
            if(input[*i]== c)
                break;
        }
        //  printf("4IMPUT|%c|",input[*i] );
        (*i)++;
        if(input[*i]== ' ')
            break;

         while (((ft_isalnum(input[*i]) == 1)  && input[*i] != '\0') && input[*i] != '\'' && input[*i] != '"')
        {
            // printf("5Je suis c|%c|i=|%d|input|%c|\n", c, *i, input[*i]);
            occurence++;
            (*i)++;
        }
        if(input[*i]== '\'' || input[*i]== '"')
        {
            c = input[*i];
            (*i)++;  
        }
    }
    data_echo->str_w_quot[(*place_tab_w_quot)].order = data_echo->order_occurence;
    // printf("\n|TABW|Place|%d|Nbr occurence|%d|Place_tab|%d|\n", (*data_echo).str_w_quot[(*place_tab_w_quot)].order, occurence, (*place_tab_w_quot));
    data_echo->order_occurence++;
    data_echo->str_w_quot[(*place_tab_w_quot)].str = malloc(sizeof(char *) * occurence + 1);
    // Il faut proteger le malloc
    (*place_tab_w_quot)++;
}

void ft_init_tab_echo_malloc(t_echo *data_echo, char *input, int i)
{

    int place_tab_w_quot;
    int place_tab_s_quot;

    place_tab_s_quot = 0;
    place_tab_w_quot = 0;
    data_echo->order_occurence = 0;
    // Cette fonction permetd e determiner le nombre d'occurence dans le tableau
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        if ((input[i] == '"' || input[i] == '\'') )
        {
            if(input[i]  != input[i+1])
            {
                ft_insert_data_w_quot(data_echo, input, &i, &place_tab_w_quot);
            }
            else 
                i = i + 2;
        }
        if (input[i]== '<' || input[i]== '>')
        {
            if((input[i]== '<' && input[i+1] == '<')||(input[i]== '>' && input[i+1] == '>'))
            {
                data_echo->str_s_quot[place_tab_s_quot].order = data_echo->order_occurence;//Je determine sa place ici 
                data_echo->order_occurence++;//J'incremente la plce ici 
                // printf("\n Insert double TABS|PLace|%d|Nbr occurence|2|Place_tab|%d|\n", data_echo->str_s_quot[place_tab_s_quot].order, place_tab_s_quot);
                data_echo->str_s_quot[place_tab_s_quot].str = malloc(sizeof(char *) * 2 + 1);
                place_tab_s_quot++;//J'incremente ca place dans le tableau
                i = i+2;
            }
            else
            {//C'est ici qu'il faur que j'implemente
                data_echo->str_s_quot[place_tab_s_quot].order = data_echo->order_occurence;//Je determine sa place ici 
                data_echo->order_occurence++;//J'incremente la plce ici 
                // printf("\nNsertSimpleTABS|PLace|%d|Nbr occurence|1|Place_tab|%d|", data_echo->str_s_quot[place_tab_s_quot].order, place_tab_s_quot);

                data_echo->str_s_quot[place_tab_s_quot].str = malloc(sizeof(char *) * 1 + 1);
                place_tab_s_quot++;//J'incremente ca place dans le tableau
                i++;
            }

        }
        if (((ft_isalnum(input[i]) == 1)) && input[i] != ' ' )
        {
            ft_insert_data_s_quot(data_echo, input, &i, &place_tab_s_quot);
        }

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
    if(input[*i] == '\0' && input[*i] == ' ')
     {
        return 1;
     }
    if (((ft_isalnum(input[*i]) == 1) && input[*i] != '\0') && (input[*i] != ' ') )
    {
            // printf("\n3Je suis? input[i]|input|%c||\n",input[*i]);

        while (((ft_isalnum(input[*i]) == 1))  && input[*i] != '\0' && input[*i] != ' ')
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
        if (input[*i] == '\0' || input[*i] == ' ')
            break;   
        //  printf("4Je suis c|%c|i=|%d|input|%c|\n", c, *i, input[*i]);

        while (((ft_isalnum(input[*i]) == 1)  && input[*i] != '\0') && input[*i] != '\'' && input[*i] != '"')
        {
            // printf("5Je suis c|%c|i=|%d|input|%c|\n", c, *i, input[*i]);
            (*i)++;
        }
        // printf("6Je suis c|%c|i=|%d|input|%c|\n", c, *i, input[*i]);

        (*i)++;
            if (input[*i] == '\0' || input[*i] == ' ')
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
        while (input[i] == ' ')
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
       // printf("\n1Je suis input[i]|input|%c|i=%d|\n",input[i], i);
        if (((ft_isalnum(input[i]) == 1)) && input[i] != ' ' )
            ft_handle_alphanumeric(input, &i, &ss_quot, 1);
        // printf("\n1End|%c|\n",input[i]);

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
    if ((c =='?') || (c >= 48 && c <= 57) || (c >= 97 && c <= 122) || (c >= 65 && c <= 90) || (c == 45) || (c == 61) || (c==46) || (c == 126) || (c == 47) || (c == 43) || (c==36) || (c ==95) || c == '"' || (c=='\'') || c == '.' || c == ',' )
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
