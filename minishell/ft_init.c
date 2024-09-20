/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/29 17:24:46 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	 if (data == NULL)
	{
		fprintf(stderr, "Memory allocation failed for data\n");
		exit(1);
	}
}
void    ft_init_echo_malloc(t_echo **data_echo)
{
	(*data_echo)->str_w_quot = malloc((*data_echo)->w_quot * sizeof(t_str));
    (*data_echo)->str_s_quot = malloc((*data_echo)->s_quot * sizeof(t_str));
	printf("\nFT_init echo malloc|w=%d|s=%d||\n",(*data_echo)->w_quot, (*data_echo)->s_quot);

}
