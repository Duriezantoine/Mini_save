/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:31:49 by aduriez           #+#    #+#             */
/*   Updated: 2024/09/28 10:31:38 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_env(t_env **env)//ce qui permet d'enregistrer l'environnement
{
	(*env) = malloc(sizeof(t_env));
	if (!((*env)))
		exit(2);
	(*env)->key = NULL;
	(*env)->value = NULL;
	(*env)->next = NULL;
}
