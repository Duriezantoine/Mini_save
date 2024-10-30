/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_with_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:36:21 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/30 13:42:25 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_insert_data *data, char *input, int *j,
		t_echo *data_echo)
{
	data->input = input;
	data->iterator = 0;
	data->c = input[*data->i];
	data_echo->str_w_quot[(*j)].str[data->iterator] = input[*data->i];
	data->iterator++;
	data_echo->str_w_quot[(*j)].bool = 1;
	(*data->i) = (*data->i) + 1;
}

static int	goto_quote(t_insert_data *data, t_echo *data_echo, int *j)
{
	while (data->input[*data->i] != '\0' && data->input[*data->i] != data->c)
	{
		data_echo->str_w_quot[(*j)].str[data->iterator] = data->input[*data->i];
		(*data->i)++;
		data->iterator++;
	}
	if (data->input[*data->i] == '\0')
		return (1);
	data_echo->str_w_quot[(*j)].str[data->iterator] = data->input[*data->i];
	(*data->i)++;
	data->iterator++;
	if (ft_white_space(data->input[*data->i]))
		return (1);
	while ((ft_isalnum(data->input[*data->i]) == 1)
		&& data->input[*data->i] != '\'' && data->input[*data->i] != '"')
	{
		data_echo->str_w_quot[(*j)].str[data->iterator] = data->input[*data->i];
		(*data->i)++;
		data->iterator++;
	}
	return (0);
}

void	ft_insert_data_w_whith_tab(t_echo *data_echo, char *input, int *i,
		int *j)
{
	t_insert_data	data;

	data.i = i;
	init_data(&data, input, j, data_echo);
	while (input[*i] != '\0' && input[*i] != data.c)
	{
		if (goto_quote(&data, data_echo, j))
			break ;
		if (ft_isalnum(input[*i]) == 0)
			break ;
		if (input[*i] == '\'' || input[*i] == '"')
		{
			data.c = input[*i];
			data_echo->str_w_quot[(*j)].str[data.iterator] = input[*i];
			(*i)++;
			data.iterator++;
		}
	}
	data_echo->str_w_quot[(*j)].str[data.iterator] = '\0';
	data_echo->str_w_quot[(*j)].bool = 0;
}
