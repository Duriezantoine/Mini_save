/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:15:30 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/28 17:20:13 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			count++;
		i++;
	}
	return (count);
}

char	*remove_quotes(char *input)
{
	int		i;
	int		j;
	char	*cpy;

	i = 0;
	j = 0;
	if (count_quotes(input) % 2 != 0)
	{
		free(input);
		return (NULL);
	}
	// printf("|ftstrlen|%d|countq|%d|total = %d\n", ft_strlen(input),
		// count_quotes(input), ft_strlen(input) - count_quotes(input) + 1);
	cpy = malloc(sizeof(char) * ft_strlen(input) - count_quotes(input) + 1);
	while (input[i])
	{
		if (input[i] != 34 && input[i] != 39)
		{
			cpy[j] = input[i];
			j++;
		}
		i++;
	}
	cpy[j] = '\0';
	// printf("\ncpy%s||", cpy);
	free(input);
	return (cpy);
}
