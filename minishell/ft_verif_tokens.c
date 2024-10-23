/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:27:59 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/23 18:21:09 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error_token(char c, char next_c)
{
	if (c == '>' || c == '<')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		write(2, &c, 1 + (next_c == c));
		ft_putstr_fd("'\n", 2);
	}
	else
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	return (1);
}

static int	check_pipe_error(char *tmp, int x)
{
	if ((x == 0) || (tmp[x + 1] != 'a' && tmp[x + 1] != '<'
			&& tmp[x + 1] != '>'))
		return (print_error_token('|', 0));
	return (0);
}

static int	check_redirection(char *tmp, int *x, char c)
{
	if (tmp[*x + 1] == c)
		(*x)++;
	if (tmp[*x + 1] != 'a')
	{
		if (tmp[*x + 1] == '>' || tmp[*x + 1] == '<')
			return (print_error_token(tmp[*x + 1], tmp[*x + 2]));
		return (print_error_token('|', 0));
	}
	return (0);
}

int	ft_verif_tokens(char *tmp)
{
	int	x;

	x = 0;
	while (tmp[x])
	{
		if (tmp[x] == '|')
		{
			if (check_pipe_error(tmp, x))
				return (1);
		}
		else if (tmp[x] == '>')
		{
			if (check_redirection(tmp, &x, '>'))
				return (1);
		}
		else if (tmp[x] == '<')
		{
			if (check_redirection(tmp, &x, '<'))
				return (1);
		}
		x++;
	}
	return (0);
}
