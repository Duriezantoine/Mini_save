/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pars4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:14:15 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 14:47:26 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_white_space(char c)
{
	if ((c >= 8 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_handle_redirection(char *input, int *i, int *ss_quot)
{
	if (input[*i] == '<' || input[*i] == '>')
	{
		if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>'
				&& input[*i + 1] == '>'))
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
	return (0);
}

void	free_tokens(char **tokens, int len)
{
	int	i;

	if (tokens == NULL)
		return ;
	i = 0;
	while (i < len)
	{
		if (tokens[i] != NULL)
			free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	ft_isalnum(int c)
{
	if (c == '|' || c == '>' || c == '<' || ft_white_space(c) || c == '\0')
		return (0);
	else
		return (1);
}

int	ft_nbr_quot(char *input, int i)
{
	int	search;
	int	result;

	result = 0;
	search = i;
	while (input[search])
	{
		if (input[search] == '"')
			result++;
		search++;
	}
	if (result % 2 == 0)
		return (0);
	else
		return (1);
}
