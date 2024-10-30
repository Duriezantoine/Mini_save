/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:51:14 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/30 13:17:12 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_echo(t_echo *echo)
{
	if (echo == NULL)
		return ;
	if (echo->str_w_quot)
	{
		if (echo->str_w_quot->str)
			free(echo->str_w_quot->str);
		free(echo->str_w_quot);
	}
	if (echo->str_s_quot)
	{
		if (echo->str_s_quot->str)
			free(echo->str_s_quot->str);
		free(echo->str_s_quot);
	}
	free(echo);
}
