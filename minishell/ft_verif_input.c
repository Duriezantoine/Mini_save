/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:24:47 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/23 17:26:35 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_special_char(char c, char **tmp)
{
	char	special[2];
    char	*tmp_tmp;

	special[0] = c;
	special[1] = '\0';
	if (*tmp == NULL)
		*tmp = ft_strdup(special);
	else
	{
		tmp_tmp = ft_strjoin(*tmp, special);
		free(*tmp);
		*tmp = ft_strdup(tmp_tmp);
		free(tmp_tmp);
	}
}

static void	handle_quotes(char *str, int *x, char **tmp)
{
	char	d;
	int		count;

	d = str[*x];
	count = 0;
	(*x)++;
	while (str[*x] != d)
	{
		if (str[*x] != ' ')
			count++;
		(*x)++;
	}
	if (count != 0)
		handle_special_char('a', tmp);
	(*x)++;
}

static void	handle_alnum(char *str, int *x, char **tmp)
{
	handle_special_char('a', tmp);
	while (ft_isalnum(str[*x]) == 1 && str[*x] != '|'
		&& str[*x] != '<' && str[*x] != '>')
		(*x)++;
}

static int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*ft_verif_input(char *str)
{
	int		x;
	char	*tmp;

	x = 0;
	tmp = NULL;
	while (str[x])
	{
		while (str[x] == ' ')
			x++;
		if (is_special_char(str[x]))
		{
			handle_special_char(str[x], &tmp);
			x++;
		}
		else if (str[x] == '\'' || str[x] == '"')
			handle_quotes(str, &x, &tmp);
		else if (ft_isalnum(str[x]) == 1 && !is_special_char(str[x])
			&& str[x] != ' ')
			handle_alnum(str, &x, &tmp);
		else
			x++;
	}
	return (tmp);
}
