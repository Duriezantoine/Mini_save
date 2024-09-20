/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:40:56 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/25 14:01:18 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(t_env *env)
{
	char	*input;
	char	*user;
	char	*pwd;
	
	t_env   *head;

    head = env;
	while (!ft_strcmp(env->key, "USER"))
        env = env->next;
    user = env->value[0];
    env = head;
    while (!ft_strcmp(env->key, "PWD"))
        env = env->next;
    pwd = env->value[0];
	printf(ANSI_BOLDWHITE ANSI_BLACK_BACKGROUND" 💀 MINISHELL "ANSI_RESET);
    printf(ANSI_BLACK ANSI_GREEN_BACKGROUND "" ANSI_RESET);
	printf(ANSI_GREEN_BACKGROUND " %s " ANSI_RESET, user);
    printf(ANSI_GREEN ANSI_BLUE_BACKGROUND "" ANSI_RESET);
    printf(ANSI_BLUE_BACKGROUND " %s " ANSI_RESET, pwd);
    printf(ANSI_BLUE "" ANSI_RESET);
	input = readline(" ");
	return (input);
}
