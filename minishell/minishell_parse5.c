/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:10:04 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 12:26:58 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_white_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 95 || str[i] != '\n')
			return (1);
	}
	return (0);
}

int	count_dollars(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '$')
		{
			count++;
		}
		str++;
	}
	return (count);
}

int	count_dollar_followed_by_characters(char *str)
{
	int	count;

	count = 0;
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
	return (count);
}

char	**allocate_result(int len)
{
	char	**result;

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
		if (ft_white_space(str[i]) && !in_quotes && !in_single_quotes)
			len++;
	}
	return (len + 1);
}
