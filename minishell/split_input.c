/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:20:25 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/26 19:25:58 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_not_limiter(char *input, t_data *data, int i, int j)
{
	while (input[i] && input[i] != 34 && input[i] != 39 && input[i] != '|'
		&& input[i] != '<' && input[i] != '>' && input[i] != '$'
		&& input[i] != ' ')
	{
		data->value[j] = input[i];
		i++;
		j++;
	}
	data->value[j] = '\0';
	// printf("\n|datavalue|%s\n", data->value);
	return (i);
}

static int	if_s_quote(char *input, t_data *data, int i, int j)
{
	while (input[i] != 34)
	{
		data->value[j] = input[i];
		i++;
		j++;
	}
	data->value[j] = '\0';
	return (i);
}

static int	if_d_quote(char *input, t_data *data, int i, int j)
{
	while (input[i] == 39)
	{
		data->value[j] = input[i];
		i++;
		j++;
	}
	data->value[j] = '\0';
	return (i);
}

static int	if_pipe(char *input, t_data *data, int i, int j)
{
	while (input[i] == '|')
	{
		data->value[j] = input[i];
		i++;
		j++;
	}
	data->value[j] = '\0';
	return (i);
}

static int	if_l_chev(char *input, t_data *data, int i, int j)
{
	while (input[i] == '<')
	{
		data->value[j] = input[i];
		i++;
		j++;
	}
	data->value[j] = '\0';
	return (i);
}

static int	if_r_chev(char *input, t_data *data, int i, int j)
{
	while (input[i] == '>')
	{
		data->value[j] = input[i];
		i++;
		j++;
	}
	data->value[j] = '\0';
	return (i);
}

static int	if_dollar(char *input, t_data *data, int i, int j)
{
	if (input[i] == '$')
	{
		data->value[j] = input[i];
		i++;
		j++;
	}
	data->value[j] = '\0';
	return (i);
}

void	split_input(char *input, t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (input[i])
	{
		data->value = malloc(sizeof(char) * 255);
		if (!data->value)
			exit(2);
		while (input[i] == ' ')
			i++;
		if (input[i] && input[i] != 34 && input[i] != 39 && input[i] != '|'
			&& input[i] != '<' && input[i] != '>' && input[i] != '$'
			&& input[i] != ' ')
			i = if_not_limiter(input, data, i, j);
		else if (input[i] == 34)
			i = if_s_quote(input, data, i, j);
		else if (input[i] == 39)
			i = if_d_quote(input, data, i, j);
		else if (input[i] == '|')
			i = if_pipe(input, data, i, j);
		else if (input[i] == '<')
			i = if_l_chev(input, data, i, j);
		else if (input[i] == '>')
			i = if_r_chev(input, data, i, j);
		else if (input[i] == '$')
			i = if_dollar(input, data, i, j);
		while (input[i] == ' ')
			i++;
		if (input[i])
		{
			init_data(&data->next);
			data = data->next;
			j = 0;
		}
	}
}