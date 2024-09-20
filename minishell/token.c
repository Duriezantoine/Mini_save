/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:50:29 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/27 09:56:24 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_pipe(char *value)
{
	int	i;

	i = 0;
	while (value[i] == '|')
		i++;
	return (i);
}

static int	token_pipe(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (if_pipe(cursor->value) == 1)
			cursor->token = PIPE;
		else if (if_pipe(cursor->value) > 1)
		{
			free_data(&data);
			printf(ANSI_BOLDRED "minishell: syntax error `|'\n" ANSI_RESET);
			return (2);
		}
		cursor = cursor->next;
	}
	return (1);
}

static int	if_l_chev(char *value)
{
	int	i;

	i = 0;
	while (value[i] == '<')
		i++;
	return (i);
}

static int	token_l_chev(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (if_l_chev(cursor->value) == 1)
			cursor->token = L_CHEV;
		else if (if_l_chev(cursor->value) == 2)
			cursor->token = D_L_CHEV;
		else if (if_l_chev(cursor->value) > 2)
		{
			free_data(&data);
			printf(ANSI_BOLDRED "minishell: syntax error `<'\n" ANSI_RESET);
			return (2);
		}
		cursor = cursor->next;
	}
	return (1);
}

static int	if_r_chev(char *value)
{
	int	i;

	i = 0;
	while (value[i] == '>')
		i++;
	return (i);
}

static int	token_r_chev(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (if_r_chev(cursor->value) == 1)
			cursor->token = R_CHEV;
		else if (if_r_chev(cursor->value) == 2)
			cursor->token = D_R_CHEV;
		else if (if_r_chev(cursor->value) > 2)
		{
			free_data(&data);
			printf(ANSI_BOLDRED "minishell: syntax error `>'\n" ANSI_RESET);
			return (2);
		}
		cursor = cursor->next;
	}
	return (1);
}

static int	if_s_quote(char *value)
{
	int	i;

	i = 0;
	while (value[i] == 39)
		i++;
	return (i);
}

static void	token_s_quote(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (if_s_quote(cursor->value) > 0)
			cursor->token = S_QUOTE;
		cursor = cursor->next;
	}
}

static int	if_d_quote(char *value)
{
	int	i;

	i = 0;
	while (value[i] == 34)
		i++;
	return (i);
}

static void	token_d_quote(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (if_d_quote(cursor->value) > 0)
			cursor->token = D_QUOTE;
		cursor = cursor->next;
	}
}

static int	if_dollar(char *value)
{
	int	i;

	i = 0;
	while (value[i] == '$')
		i++;
	return (i);
}

static void	token_dollar(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (if_dollar(cursor->value) > 0)
			cursor->token = DOLLAR;
		cursor = cursor->next;
	}
}

static int	if_arg(char *value)
{
	if (value[0] == '-')
		return (1);
	return (0);
}

static void	token_arg(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (if_arg(cursor->value))
			cursor->token = ARG;
		cursor = cursor->next;
	}
}

static void	token_echo(t_data *data)
{
	int		i;
	char	*tmp;

	t_data *cursor;   // Le cursor de data
	t_data *full_tmp; // qui permet de sauter ce qui  a ete mis
	t_data *arg;      // qui permet d'introduire l'arg
	cursor = data;
	i = 0;
	while (cursor)
	{
		 
		if (ft_strcmp(cursor->value, "echo"))
		{
			cursor->token = ECHO_CMD;
			cursor = cursor->next;
			cursor = cursor->prev;
			cursor->arg = malloc(sizeof(char *) * 255);
			data = cursor;
			arg = data;
			cursor = cursor->next;
			// printf("||AVbcl%s|", cursor->value);
			while (cursor && *(cursor->value) != 124 && *(cursor->value) != 60
				&& *(cursor->value) != 62 && *(cursor->value) != 36)
			// Il faut maintenant faire la une difference avec ou sans les chevrons
			{
				tmp = cursor->value;
				arg->arg[i] = strdup(tmp);
				i++;
				cursor = data;
				if (cursor->next->next == NULL)
				{
					full_tmp = cursor;
					data = full_tmp;
					free(data->next);
					data->next = NULL;
					return ;
				}
				else
				{
					full_tmp = cursor->next->next;
					free(data->next);
					data->next = full_tmp;
				}
				cursor = data;
				cursor = cursor->next;
			}
			// Mise en place de la suppresion du prochain token
			// data = cursor;
			// printf("\nJe suis le cursor value|%s|||\n", cursor->value);
			// data = cursor;
			// cursor = cursor->next;
		}
		cursor = cursor->next;
	}
}

static void	token_cd(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (ft_strcmp(cursor->value, "cd"))
		{
			cursor->token = CD;
			printf("|TAAAAO|\n");
		}
		cursor = cursor->next;
	}
}

static void	token_pwd(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (ft_strcmp(cursor->value, "pwd"))
			cursor->token = PWD;
		cursor = cursor->next;
	}
}

static void	token_export(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (ft_strcmp(cursor->value, "export"))
			cursor->token = EXPORT;
		cursor = cursor->next;
	}
}

static void	token_unset(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (ft_strcmp(cursor->value, "unset"))
			cursor->token = UNSET;
		cursor = cursor->next;
	}
}

static void	token_env(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (ft_strcmp(cursor->value, "env"))
			cursor->token = CMD;
		cursor = cursor->next;
	}
}

static void	token_exit(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (ft_strcmp(cursor->value, "exit"))
			cursor->token = EXIT;
		cursor = cursor->next;
	}
}

static void	token_cmd(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if (cursor->token == EMPTY)
			cursor->token = CMD;
		cursor = cursor->next;
	}
}

int	token_data(t_data *data)
{
	token_s_quote(data);
	token_d_quote(data);
	if (token_pipe(data) != 1)
		return (2);
	if (token_l_chev(data) != 1)
		return (2);
	if (token_r_chev(data) != 1)
		return (2);
	token_dollar(data);
	token_arg(data);
	token_echo(data);
	token_pwd(data);
	token_export(data);
	token_unset(data);
	token_cd(data);
	token_env(data);
	token_exit(data);
	token_cmd(data);
	token_here_doc(data);
	return (1);
}

void	token_infile(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if ((cursor->token == L_CHEV || cursor->token == D_L_CHEV
				|| cursor->token == CMD || cursor->token == ARG)
			&& (cursor->next && cursor->next->token == CMD
				&& !cursor->next->path))
			cursor->next->token = INFILE;
		cursor = cursor->next;
	}
}

void	token_outfile(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	while (cursor)
	{
		if ((cursor->token == R_CHEV || cursor->token == D_R_CHEV)
			&& (cursor->next && cursor->next->token == CMD
				&& !cursor->next->path))
			cursor->next->token = OUTFILE;
		cursor = cursor->next;
	}
}

void	token_here_doc(t_data *data)
{
	t_data	*cursor;

	cursor = data;
	if (cursor->token == D_L_CHEV && cursor->next)
	{
		cursor->token = HERE_DOC;
		cursor->next->token = END_HERE_DOC;
		return ;
	}
	while (cursor)
	{
		if (ft_strcmp(cursor->value, "here_doc") && cursor->next
			&& cursor->next->token == D_R_CHEV && cursor->next->next)
		{
			cursor->token = HERE_DOC;
			cursor->next->next->token = END_HERE_DOC;
			cursor = cursor->next->next;
		}
		cursor = cursor->next;
	}
}
