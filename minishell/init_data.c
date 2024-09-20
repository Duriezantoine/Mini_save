/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:13:00 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/28 12:22:46 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		exit(2);
    (*data)->index = 0;
	(*data)->value = NULL;
	(*data)->outfile = 0;
    (*data)->arg = NULL;
    (*data)->token = EMPTY;
	(*data)->path = NULL;
    (*data)->next = NULL;
}
