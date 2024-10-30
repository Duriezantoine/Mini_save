/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:10:37 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 13:22:18 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_d(char *str)
{
	int		len;
	char	**result;

	len = count_segments(str);
	result = allocate_result(len);
	if (result)
		split_string_d(str, result);
	return (result);
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

int	ft_space_or_null(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (!ft_white_space(str[x]))
			return (1);
		x++;
	}
	return (0);
}

// char	*ft_change_input_v2(char *save)
// {
// 	int	x;

// 	x = 0;
// 	while (save[x])
// 	{
// 		if (save[x] == 32)
// 			x++;
// 		if (save[x] != 32)
// 			break ;
// 	}
// 	return (save);
// }
