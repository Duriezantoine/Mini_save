/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:10:22 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 14:03:33 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_env **env)
{
	t_env	*envt;

	while (*env)
	{
		envt = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = envt;
	}
}

void	ft_free_end(t_node *list, t_env **env)
{
	ft_free_env(env);
	free(list);
	rl_clear_history();
}

void	add_env_to_list(t_env **head, t_env **current, t_env *new_env)
{
	if (*head == NULL)
	{
		*head = new_env;
		*current = new_env;
	}
	else
	{
		(*current)->next = new_env;
		*current = new_env;
	}
}

t_env	*ft_insert_env(char **envp)
{
	int		i;
	t_env	*head;
	t_env	*current;
	char	*sep;
	t_env	*new_env;

	i = -1;
	head = NULL;
	current = NULL;
	while (envp[++i])
	{
		new_env = (t_env *)ft_calloc(sizeof(t_env), 1);
		sep = ft_strchr(envp[i], '=');
		if (sep != NULL)
		{
			*sep = '\0';
			new_env->value = ft_strdup(sep + 1);
		}
		new_env->key = ft_strdup(envp[i]);
		if (sep)
			*sep = '=';
		add_env_to_list(&head, &current, new_env);
	}
	return (head);
}
