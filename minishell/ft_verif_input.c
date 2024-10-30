/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:24:47 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/30 13:20:59 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(char token, char **res)
{
	const char	c[2] = {token, '\0'};
	char		*tmp;

	if (*res == NULL)
		*res = ft_strdup((char *)c);
	else
	{
		tmp = *res;
		*res = ft_strjoin(*res, (char *)c);
		free(tmp);
	}
}

static void	add_quote(char *str, int *x, int *count, char **tmp)
{
	char	d;

	if (str[*x] == '\'' || str[*x] == '"')
	{
		d = str[(*x)++];
		while (str[*x] != d)
		{
			(*x)++;
			(*count)++;
		}
		if (*count != 0)
			add_token('a', tmp);
		(*x)++;
	}
}

char	*ft_verif_input(char *str)
{
	int		x;
	int		count;
	char	*tmp;

	tmp = NULL;
	x = 0;
	while (str[x])
	{
		while (ft_white_space(str[x]))
			x++;
		if (str[x] == '|' || str[x] == '<' || str[x] == '>')
			add_token(str[x++], &tmp);
		count = 0;
		add_quote(str, &x, &count, &tmp);
		if (ft_isalnum(str[x]) == 1 && str[x] != '|' && str[x] != '<'
			&& str[x] != '>' && str[x] != ' ')
		{
			add_token('a', &tmp);
			while (ft_isalnum(str[x]) == 1 && str[x] != '\'' && str[x] != '"')
				x++;
		}
	}
	return (tmp);
}
