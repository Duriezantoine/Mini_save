/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:43:21 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 13:32:59 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_unset(t_env **env, char *search)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !*env || !search)
		return ;
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, search) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	bulting_unset(char ***env, t_cmd *cmd, t_node *list)
{
	char	**tmp;
	int		x;

	tmp = cmd->cmd_and_args;
	x = 1;
	while (tmp[x])
	{
		if (ft_search_envp((*env), cmd->cmd_and_args[x]) == 0)
		{
			return (1);
		}
		else
		{
			ft_delete_unset(&list->env, cmd->cmd_and_args[x]);
		}
		x++;
	}
	return (0);
}

static int	check_plus_sign(char *key, char *key_envp)
{
	int	count;

	count = ft_strlen(key);
	if (key[count - 1] == '+')
	{
		free(key);
		free(key_envp);
		return (2);
	}
	return (0);
}

static int	compare_keys(char *key, char *key_envp, char *search)
{
	if (ft_strncmp(key_envp, key, ft_strlen(search)) == 0)
	{
		free(key);
		free(key_envp);
		return (3);
	}
	return (0);
}

int	ft_search_envp(char **env, char *search)
{
	char	*key;
	char	*key_envp;
	int		x;
	int		result;

	x = -1;
	key = ft_copy_start(search, '=');
	while (env[++x])
	{
		key_envp = ft_copy_start(env[x], '=');
		result = check_plus_sign(key, key_envp);
		if (result)
			return (result);
		result = compare_keys(key, key_envp, search);
		if (result)
			return (result);
		free(key_envp);
	}
	free(key);
	return (0);
}
