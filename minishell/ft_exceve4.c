/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:36:07 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 11:39:08 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_env_tab(char **env_tab, t_env *current, int i)
{
	char	*tmp;

	tmp = ft_strjoin(current->key, "=");
	if (!tmp)
		return (0);
	env_tab[i] = ft_strjoin(tmp, current->value);
	free(tmp);
	if (!env_tab[i])
		return (0);
	return (1);
}

char	**convert_env_to_tab(t_env *env_list)
{
	char	**env_tab;
	t_env	*current;
	int		i;

	env_tab = malloc(sizeof(char *) * (get_env_size(env_list) + 1));
	if (!env_tab)
		return (NULL);
	i = 0;
	current = env_list;
	while (current)
	{
		if (!fill_env_tab(env_tab, current, i))
		{
			free_tab_error(env_tab, i);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

void	free_env_tab(char **env_tab)
{
	int	i;

	if (!env_tab)
		return ;
	i = 0;
	while (env_tab[i])
	{
		free(env_tab[i]);
		i++;
	}
	free(env_tab);
}

int	ft_butlin_first(struct s_exec **lst, t_node **list, int i, int built)
{
	int	ret;

	ret = 0;
	if (built == 1)
		return (bulting_env((*list)));
	if (built == 2)
		return (bulting_echo((*lst)[i].argv, 1));
	if (built == 3)
		if (ft_choose_export(lst, i, &ret))
			return (1);
	return (ret);
}

int	ft_butlin_second(struct s_exec **lst, t_node **list, int i, int built)
{
	int	ret;

	ret = 0;
	if (built == 4)
	{
		ret = bulting_cd((*lst)[i].argv, (*list), &(*list)->env);
		free_env_tab(lst[i]->envp);
		lst[i]->envp = convert_env_to_tab((*list)->env);
	}
	if (built == 5 && i == 0)
		ft_start_unset(lst, list, i);
	if (built == 6)
		bulting_pwd();
	return (ret);
}
