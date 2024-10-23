/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/23 17:39:30 by aduriez          ###   ########.fr       */
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
int ft_search_inputs(char *str)
{
	int     i;
	char    c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
			{
				if (!ft_white_space(str[i]))
					return (1);
				i++;
			}
			if (str[i] == c)
				i++;
		}
		else if (!ft_white_space(str[i]))
			return (1);
		i++;
	}
	return (0);
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
		free(*env);
		*env = envt;
	}
}

void ft_free_end(t_node *list, t_env **env)
{
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
	int     i;
	t_env   *head;
	t_env   *current;
	char    *sep;
	t_env   *new_env;

	i = -1;
	head = NULL;
	current = NULL;
	while (envp[++i])
	{
		new_env = (t_env *)ft_calloc(sizeof(t_env), 1);
		sep = strchr(envp[i], '=');
		if (sep != NULL)
		{
			*sep = '\0';
			new_env->value = ft_strdup(sep + 1);
		}        
		new_env->key = ft_strdup(envp[i]);
		if (sep)
			*sep = '=';
		add_env_to_list(&head, &current, new_env);
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
	list = ft_calloc(1, sizeof(t_node));
	if (list == NULL)
		ft_out_exit(3);
	list->pipe[0] = -1;
	list->env = ft_insert_env(envp);
	return (shell_loop(list, &data, &list->env));
}
