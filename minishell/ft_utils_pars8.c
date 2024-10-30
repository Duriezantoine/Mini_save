/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pars8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:14:39 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/30 15:13:52 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_insert_data_loop(char *input, int *i, char *c, int *occ)
{
	while (input[*i] != '\0' && input[*i] != *c)
	{
		(*i)++;
		(*occ)++;
	}
	if (input[*i] == '\0')
		return (1);
	(*occ)++;
	if (ft_isalnum(input[*i]) == 0)
		return (1);
	if (ft_process_input(input, i, occ))
		return (1);
	if (input[*i] == '\'' || input[*i] == '"')
	{
		*c = input[*i];
		(*occ)++;
		(*i)++;
	}
	return (0);
}

void	ft_insert_data_w_quot(t_echo *data, char *input, int *i,
		int *place_tab_w_quot)
{
	int		occ;
	char	c;

	c = input[*i];
	(*i) = (*i) + 1;
	occ = 1;
	while (input[*i] != '\0' && input[*i] != c)
	{
		if (ft_insert_data_loop(input, i, &c, &occ))
			break ;
	}
	data->str_w_quot[(*place_tab_w_quot)].order = data->order_occurence++;
	data->str_w_quot[(*place_tab_w_quot)].str = malloc(sizeof(char *) * occ
			+ 1);
	(*place_tab_w_quot)++;
}

static void	handle_redirection_malloc(t_echo *data_echo, char *input, int *i,
		int *place_s_quot)
{
	data_echo->str_s_quot[*place_s_quot].order = data_echo->order_occurence++;
	if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>'
			&& input[*i + 1] == '>'))
	{
		data_echo->str_s_quot[*place_s_quot].str = malloc(sizeof(char *) * 2
				+ 1);
		(*place_s_quot)++;
		*i += 2;
	}
	else
	{
		data_echo->str_s_quot[*place_s_quot].str = malloc(sizeof(char *) * 1
				+ 1);
		(*place_s_quot)++;
		(*i)++;
	}
}

static void	handle_quotes_malloc(t_echo *data_echo, char *input, int *i,
		int *place_tab_w_quot)
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
			handle_quotes_malloc(data_echo, input, &i, &place_tab_w_quot);
		if (input[i] == '<' || input[i] == '>')
			handle_redirection_malloc(data_echo, input, &i, &place_tab_s_quot);
		if (ft_isalnum(input[i]) == 1 && !ft_white_space(input[i]))
			ft_insert_data_s_quot(data_echo, input, &i, &place_tab_s_quot);
	}
}
