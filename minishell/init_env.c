/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:58:32 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/28 14:50:49 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_env **env)
{
	*env = malloc(sizeof(t_env));
	if (!(*env))
		exit(2);
	(*env)->key = NULL;
	(*env)->value = NULL;
	(*env)->next = NULL;
}
void	free_envw(t_env *env)
{
	t_env	*cursor;
	t_env	*next;
	int		i;

	cursor = env;
	while (cursor)
	{
		next = cursor->next;
		i = 0;
		while (cursor->value && cursor->value[i])
		{
			free(cursor->value[i]);
			i++;
		}
		free(cursor->value);
		free(cursor->key);
		free(cursor);
		cursor = next;
	}
}

void	env_copy(t_env *env, char **envp)
{
	t_env	*cursor;
	char	**tmp;
	int		i;

	cursor = env;
	i = 0;
	while (envp[i])
	{
		cursor->value = ft_split(envp[i], ':');
		if (envp[i + 1] && !cursor->next)
			init_env(&cursor->next);
		cursor = cursor->next;
		i++;
	}
	cursor = env;
	while (cursor && cursor->value)
	{
		tmp = ft_split(cursor->value[0], '=');
		cursor->key = ft_strdup(tmp[0]);
		free(cursor->value[0]);
		cursor->value[0] = ft_strdup(tmp[1]);
		free_split(tmp);
		cursor = cursor->next;
	}
	free_envw(env);
}
