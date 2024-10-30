/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve10.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:52:13 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 11:36:13 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_excev_butlin(struct s_exec **lst, t_node **list, int i, t_data *data)
{
	int	built;
	int	ret;

	built = builtin((*lst)[i].exec);
	if (built == -1)
		return (0);
	ret = ft_butlin_first(lst, list, i, built);
	if (built <= 3)
		return (ret);
	ret = ft_butlin_second(lst, list, i, built);
	if (built == 7)
		return (bulting_exit((*lst)[i].argv, (*list), &(*list)->env, data));
	ft_free_env(&(*list)->env);
	(*list)->env = ft_insert_env(lst[i]->envp);
	return (ret);
}

void	handler_void(int sig)
{
	(void)sig;
}

int	lst_len(t_node *list)
{
	int	ret;

	ret = 0;
	while (list)
	{
		ret++;
		list = list->next;
	}
	return (ret);
}

char	*find_path_env(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	get_env_size(t_env *env_list)
{
	t_env	*current;
	int		size;

	size = 0;
	current = env_list;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
