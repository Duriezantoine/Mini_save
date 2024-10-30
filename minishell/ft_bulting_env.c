/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:48:02 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 13:24:08 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bulting_env(t_node *list)
{
	t_env	*tmp;
	t_env	*current;
	t_env	*next;

	tmp = copy_env(list->env);
	sort_envp(&tmp);
	current = tmp;
	while (current != NULL)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	current = tmp;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	return (0);
}

void	sort_envp(t_env **env)
{
	t_env	*current;
	t_env	*index;
	char	*tmp_key;
	char	*tmp_value;

	current = *env;
	while (current)
	{
		index = current->next;
		while (index != NULL)
		{
			if (ft_strcmp(current->key, index->key) > 0)
			{
				tmp_key = current->key;
				current->key = index->key;
				index->key = tmp_key;
				tmp_value = current->value;
				current->value = index->value;
				index->value = tmp_value;
			}
			index = index->next;
		}
		current = current->next;
	}
}

t_env	*copy_env(t_env *env)
{
	t_env	*copy;
	t_env	*current;
	t_env	*prev;
	t_env	*new_node;

	current = env;
	copy = NULL;
	while (current != NULL)
	{
		new_node = (t_env *)ft_calloc(sizeof(t_env), 1);
		if (new_node != NULL)
		{
			new_node->key = ft_strdup(current->key);
			if (current->value)
				new_node->value = ft_strdup(current->value);
			if (copy == NULL)
				copy = new_node;
			else
				prev->next = new_node;
			prev = new_node;
		}
		current = current->next;
	}
	return (copy);
}
