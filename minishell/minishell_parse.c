/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/23 16:53:26 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// extern volatile sig_atomic_t signal_recu;


#include "minishell.h"

int	ft_white_spaces(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] != 95 || str[i] != '\n')
			return(1);
	}
	return(0);
}
typedef struct s_split_data
{
	int		in_quotes;
	int		in_single_quotes;
	int		j;
	int		k;
}	t_split_data;

static void	init_split_data(t_split_data *data)
{
	data->in_quotes = 0;
	data->in_single_quotes = 0;
	data->j = 0;
	data->k = 0;
}

static void	handle_quotes(char c, t_split_data *data)
{
	if (c == '"')
		data->in_quotes = !data->in_quotes;
	if (c == '\'')
		data->in_single_quotes = !data->in_single_quotes;
}

static void	handle_whitespace(char *temp, char **result, t_split_data *data)
{
	temp[data->j] = '\0';
	result[data->k] = strdup(temp);
	data->k += 1;
	data->j = 0;
}

void	split_string_d(char *str, char **result)
{
	t_split_data	data;
	char			*temp;
	int				i;

	temp = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	if (!temp)
		return ;
	init_split_data(&data);
	i = -1;
	while (str[++i])
	{
		handle_quotes(str[i], &data);
		if (ft_white_space(str[i]) && !data.in_quotes
			&& !data.in_single_quotes)
			handle_whitespace(temp, result, &data);
		else
			temp[data.j++] = str[i];
	}
	temp[data.j] = '\0';
	result[data.k] = strdup(temp);
	free(temp);
}
int count_dollars( char *str)
{
    int count = 0;
    while (*str)
    {
        if (*str == '$')
        {
            count++;
        }
        str++;
    }
    return count;
}

int count_dollar_followed_by_characters(char *str)
{
    int count = 0;
    while (*str)
    {
        if (*(str + 1) && isalnum(*(str + 1)))
        {
            count++;
            while (*(str + 1) && isalnum(*(str + 1)))
            {
                str++;
            }
        }
        str++;
    }
    return count;
}

char **allocate_result(int len)
{
    char **result;
    
    result = (char **)malloc(sizeof(char *) * (len + 1));
    if (!result)
        return (NULL);
    result[len] = NULL;
    return (result);
}

int	count_segments(char *str)
{
    int	len;
	int	in_quotes;
	int	in_single_quotes;
	int	i;

    len = 0;
    in_quotes = 0;
    in_single_quotes = 0;
	i = -1;
	while (str[++i])
	{
        if (str[i] == '"')
		    in_quotes = !in_quotes;
        if (str[i] == '\'')
            in_single_quotes = !in_single_quotes;
		if (ft_white_space(str[i]) && !in_quotes
			&& !in_single_quotes)
			len++;
	}
	return (len + 1);
}

char **ft_split_d( char *str)
{
    int len = count_segments(str);
    char **result = allocate_result(len);
    if (result)
        split_string_d(str, result);
    return result;
}
static int	is_quote(char c, int *in_single, int *in_double)
{
	if (c == '\'')
	{
		*in_single = !(*in_single);
		return (1);
	}
	else if (c == '\"')
	{
		*in_double = !(*in_double);
		return (1);
	}
	return (0);
}

int	count_dollars_outside_quotes(char *str)
{
	int	count;
	int	i;
	int	in_single;
	int	in_double;

	count = 0;
	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (!is_quote(str[i], &in_single, &in_double))
		{
			if (str[i] == '$' && !in_single && !in_double)
				count++;
		}
		i++;
	}
	return (count);
}
int ft_space_or_null(char *str)
{
	int x;

	x = 0;
	while(str[x])
	{
		if(!ft_white_space(str[x]))
			return (1);
		x++;
	}
	return (0);
}

char    *ft_change_input_v2(char *save)
{
    int x;

    x = 0;
    while(save[x])
    {
        if (save[x] == 32)
            x++;
        if(save[x] != 32)
            break ;
    }
    return (save);
}



void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        signal_recu = sig;
        ft_putstr_fd("^C\n", 2);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}
// int check_syntax_errors(char *input) 
// {
//     int x;
//     char c;
//      x =0;
//     while(input[x])
//     {
//         if(input[x] == ' ')
//             x++;
//         if (ft_islanum(input[x]) ==1)
//             x++;
//         if (input[x] == '\'' || input[x]=='"' )
//         {
//             char c = input[x++];
//             while(input[x] != c)
//                 x++;
            
//         }
//     }


// }




int ft_search_inputs(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
            {
                if (!ft_white_space(str[i]) && str[i] != '\'')
                    return 1;
                i++;
            }
            if (str[i] == '\'')
                i++; // Passe le guillemet simple de fermeture
        }
        else if (str[i] == '"')
        {
            i++;
            while (str[i] && str[i] != '"')
            {
                if (!ft_white_space(str[i]))
                    return 1;
                i++;
            }
            if (str[i] == '"')
                i++; // Passe le guillemet double de fermeture
        }
        else if (!ft_white_space(str[i]))
        {
            return 1;
        }
        i++;
    }
    return 0;
}

void ft_init_verif(t_verif_input *verif)
{
    verif->nbr_stack = 0;
    verif->pipe = 0;
    verif->alnum = 0;
    verif->x = 0;
    verif->c = 'a';
    verif->nbr_token = 0;
    verif->token_right = 0;
    verif->token_left = 0;
    verif->stack_start = 0;
    verif->heredoc = 0;
    verif->last_char_special = 0;
    verif->command_before_pipe = 0;

}

// int ft_it_s_ok_input(t_verif_input verif)
// {
//     if(verif.pipe== 1 && verif.nbr_stack==0)
//         return(1);
//     if(verif.token_left==1 && verif.nbr_stack== 0)
//         return(1);
//     if(verif.nbr_token>2)
//         return(1);
//     return(0);
// }
int print_syntax_error(char c, char *str)
{
    fprintf(stderr, "syntax error near unexpected token '%c' in '%s'\n", c, str);
    return (1);
}
int ft_it_s_ok_input(t_verif_input verif)
{
    if (verif.pipe == 1 && verif.nbr_stack == 0)
        return (1);
    if ((verif.token_left > 0 || verif.token_right > 0) && verif.nbr_stack == 0)
        return (1);
    if (verif.nbr_token > 2)
        return (1);
    if (verif.heredoc && verif.token_left > 0)
        return (1);
    return (0);
}

int ft_check_end_input(t_verif_input verif)
{
    if (verif.last_char_special)
        return (1);
    if (verif.pipe > 0 && !verif.command_before_pipe)
        return (1);
    return (0);
}

char *ft_verif_input(char *str)//c'est fonction permet de simplifier la verification de l'input
{   
    // t_verif_input verif;
    int x;
    // ft_init_verif(&verif);
    x = 0;
    char d;
    int count;

    char *tmp=NULL;
    char *tmp_tmp=NULL;
    // int i;
    // printf("Je suis str3%s3", str);
    while(str[x])
    {
        while(str[x]== ' ')
            x++;
        if ( str[x]== '|' || str[x] == '<' || str[x] == '>')
        {
             char c[2] = {str[x], '\0'};
            // printf("\nXXXXXX\n");
            if (tmp== NULL)
            {
                 tmp = ft_strdup((char  *)&c);
                // printf("10{%s}\n", tmp);
            }
            else
            {
                tmp_tmp = ft_strjoin(tmp, (char *)&c );
                // printf("Je sui tmptmp{%s}", tmp_tmp);
                // free(tmp);
                tmp = ft_strdup(tmp_tmp);
                free(tmp_tmp);
            }   
            x++;
        }
    
    
        count = 0;
        if(str[x] == '\'' || str[x] == '"' )
        {
            // printf("END{%c}", str[x]);
            d = str[x];
            x++;    
            while(str[x] != d)
            {
                if (str[x] != ' ') 
                    count++;
                x++;
            }
            if(count !=0)
            {
                if (tmp==NULL)
                {
                    char c[2] = {'a', '\0'};
                    tmp = ft_strdup((char  *)&c);

                }
                else
                {// fzzree(tmp);
                    tmp_tmp = ft_strjoin(tmp, "a");
                    tmp = ft_strdup(tmp_tmp);
                }// free(tmp_tmp);
            }
            x++;
        }
        if(ft_isalnum(str[x])==1 &&  str[x]!= '|' && str[x] != '<' && str[x] != '>' && str[x] != ' ')
        {
            if (tmp==NULL)
            {
                char c[2] = {'a', '\0'};
                tmp = ft_strdup((char  *)&c);
            }
            else
            {
                tmp_tmp = ft_strjoin(tmp, "a");
                free(tmp);
                tmp = ft_strdup(tmp_tmp);
                free(tmp_tmp);
            }
            while(ft_isalnum(str[x])==1 &&  str[x]!= '|' && str[x] != '<' && str[x] != '>')
                x++;
        }
    }
    
    // printf("\nJe suis tmp(%s)|%d|\n ", tmp, ft_strlen(tmp)); 
    return(tmp);
}
int ft_verif_tokens(char *tmp)
{
    int x;

    x = 0;
    while(tmp[x])
    {
        if(tmp[x]=='|')
        {
            if((x==0 ) ||  (tmp[x+1] != 'a' && tmp[x+1] != '<' && tmp[x+1] != '>' ))
            {
                 ft_putstr_fd( "syntax error near unexpected token `|'\n", 2);
                return(1);
            }
        }
        if(tmp[x]=='>')
        {
            if(tmp[x+1] == '>')
                x++;
            if(tmp[x+1] != 'a')
            {
                if (tmp[x+1] == '>' || tmp[x+1] == '<')
                {
                    ft_putstr_fd("syntax error near unexpected token `", 2);
                    write(2, &tmp[x+1], 1 + (tmp[x+2] == tmp[x+1]));
                    ft_putstr_fd("'\n", 2);
                }
                else
                 ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
                return(1);
            }
        }
        if(tmp[x]== '<')
        {
            if(tmp[x+1] == '<')
                x++;
            if(tmp[x+1] != 'a')
            {
                if (tmp[x+1] == '>' || tmp[x+1] == '<')
                {
                    ft_putstr_fd("syntax error near unexpected token `", 2);
                    write(2, &tmp[x+1], 1 + (tmp[x+2] == tmp[x+1]));
                    ft_putstr_fd("'\n", 2);
                }
                else
                 ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
                return(1);
            }   

                
        }
        x++;
    }
    return(0);
}
int ft_orga_verif_input(char *str)
{
    char *tmp;

    tmp = ft_verif_input(str);
    if(ft_verif_tokens(tmp)== 1)
    {
        free(tmp);
        return(1);
    }
    free(tmp);
    return(0);  
}

int shell_loop(t_node *list, t_data *data, t_env **env)
{
    char *input;

    // Configuration du gestionnaire de signaux

    while (1)
    {   
        // printf("Exitcode|%d|", data->exit_code );

        signal_recu = 0;   
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, signal_handler);

        input = readline("minishell$ ");

        if (signal_recu == SIGINT)
            data->exit_code = 130;

        // printf("INPUT |%s|", input);    
        if (input == NULL)  // Gestion de Ctrl+D (EOF)
        {
            write(1, "exit\n", 5);
            break;
        }
        if (ft_search_inputs(input) == 0 )//&& check_syntax_errors(input)==1
        {
            // printf("ICI");
            free(input);
            continue;
        }
        if(ft_orga_verif_input(input))
        {
            add_history(input);     
            free(input);
            data->exit_code = 2;
            // printf("\nProbleme\n");
            continue;
        }
        ft_init_data(data);
        add_history(input);  // Ajout de la commande à l'historique
        // printf("Je suis input\n|%s|\n", input);
        input = ft_change_input(&input, *env, data);//Il faudra le refaire a la suite 
        // printf("New_input\n|%s|\n", input);
        if (ft_strlen(input) == 0 || ft_white_spaces(input) == 0)
        {
            //printf("\nICIC\n");
            free(input);
            continue;
        }


        if (ft_parsing(list, data, input, *env) == 1)
        {
            free(input);
            break;
        }

        free(input);
        lexer(list);
       // print_list(list);
        if (lexer_cmd(list, data) == 0)
            data->exit_code = ft_exceve(list, data, &list->env);
        ft_free_return_loop(list);
        
        // printf("Exitcode|%d|", data->exit_code );
    }

    ft_free_end(list, env);
    return data->exit_code;

}
void 	ft_free_return_loop(t_node *list)
{
		free_node(list->next);
		list->next = NULL;
		ft_free_arg(list->arg);
		ft_free_cmd(list->cmd);
		list->arg = NULL;
		list->cmd = NULL;
		list->pipe[0] = -1;

}

void    ft_free_env(t_env **env)
{
    t_env *envt;
    while(*env)
    {
            envt = (*env)->next;
            free((*env)->key);
            free((*env)->value);
            // printf("freeing ptr %p\n", *env);
            free(*env);
            *env = envt;
    }
}

void ft_free_end(t_node *list, t_env **env)
{
        // if(list->save[0] >= 0) close(list->save[0]);
        // if(list->save[1] >= 0) close(list->save[1]);
        ft_free_env(env);
        free(list);
        rl_clear_history();
}

void add_env_to_list(t_env **head, t_env **current, t_env *new_env)
{
	if (*head == NULL)
	{
		*head = new_env;
		*current = new_env;
	}
	else
	{
		(*current)->next = new_env;
		*current = new_env;
	}

}


t_env *ft_insert_env(char **envp)
{
        int i;
        t_env *head = NULL;
        t_env *current = NULL;
        char    *sep;

        i = 0;
        while (envp[i])
        {
                t_env *new_env = (t_env *)malloc(sizeof(t_env));
                sep = strchr(envp[i], '=');
                // printf("sep: (%s) %s\n", envp[i], sep);
                if (sep == NULL)
                    new_env->value = NULL;
                else
                {
                    *sep = '\0';
                    new_env->value = ft_strdup(sep + 1);
                }
				// printf("allocating ptr %p\n", new_env);
                new_env->key = ft_strdup(envp[i]);
                if (sep)
                    *sep = '=';
                // printf("%s => \n\n%s\n\n\n\n\n\n", new_env->key, new_env->value);
                new_env->next = NULL;
                add_env_to_list(&head, &current, new_env);
                i++;
        }
        return (head);
}
int main(int argc, char **argv, char **envp)
{
	t_data data;
	t_node *list;
	(void)argv;
	(void)argc;

    rl_catch_signals = 0;
    data.exit_code = 0;
	if (argc == 2)
		ft_out_exit(1);
	// if (!envp || !*envp)
	// 	ft_out_exit(2);
	list = ft_calloc(1, sizeof(t_node));
	if (list == NULL)
		ft_out_exit(3);
	// list->save[0] = dup(STDIN_FILENO);
	// list->save[1] = dup(STDOUT_FILENO);
	list->pipe[0] = -1;
	list->env = ft_insert_env(envp);
	//print_env(list->env);
    return (shell_loop(list, &data, &list->env));
}
