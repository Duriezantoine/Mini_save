/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pars7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:14:34 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/30 13:41:14 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_insert_data_s_whith_tab(t_echo *data, char *input, int *i,
		int *c_tab_s_quot)
{
	int		i_tab_s_quot;
	char	sep;

	i_tab_s_quot = 0;
	while (ft_isalnum(input[*i]) && input[*i] != '\0')
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			sep = input[*i];
			data->str_s_quot[(*c_tab_s_quot)].str[i_tab_s_quot] = input[*i];
			(*i)++;
			i_tab_s_quot++;
			while (input[*i] != sep && input[*i] != '\0')
			{
				data->str_s_quot[(*c_tab_s_quot)].str[i_tab_s_quot] = input[*i];
				(*i)++;
				i_tab_s_quot++;
			}
		}
		data->str_s_quot[(*c_tab_s_quot)].str[i_tab_s_quot] = input[*i];
		(*i)++;
		i_tab_s_quot++;
	}
	data->str_s_quot[(*c_tab_s_quot)].str[i_tab_s_quot] = '\0';
	data->str_s_quot[(*c_tab_s_quot)].bool = 0;
}

static void	handle_redirection(t_echo *data_echo, char *input, int *i,
		int *clef_tab_s_quot)
{
	if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>'
			&& input[*i + 1] == '>'))
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

static void	handle_quotes(t_echo *data_echo, char *input, int *i,
		int *clef_tab_w_quot)
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
			ft_insert_data_s_whith_tab(data_echo, input, &i, &clef_tab_s_quot);
			clef_tab_s_quot++;
		}
	}
}

void	ft_insert_data_s_quot(t_echo *data_echo, char *input, int *i,
		int *p_tab_s_quot)
{
	int		occurence;
	char	c;

	occurence = 0;
	while (ft_isalnum(input[*i]) == 1 && input[*i] != '\0')
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			c = input[*i];
			(*i)++;
			occurence++;
			while (input[*i] != c)
			{
				(*i)++;
				occurence++;
			}
		}
		((*i)++);
		occurence++;
	}
	data_echo->str_s_quot[(*p_tab_s_quot)].order = data_echo->order_occurence;
	data_echo->order_occurence++;
	data_echo->str_s_quot[(*p_tab_s_quot)].str = malloc(sizeof(char *)
			* occurence + 1);
	(*p_tab_s_quot)++;
}
