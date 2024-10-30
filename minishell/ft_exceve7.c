/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:50:06 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 15:47:28 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_path_access(char **split_path, char *str)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		full_path = ft_strjoin(tmp, str);
		free(tmp);
		if (access(full_path, F_OK | X_OK) != -1)
		{
			free(full_path);
			return (1);
		}
		free(full_path);
		i++;
	}
	return (0);
}

int	ft_check_cmd_valid(char *str, t_env *env)
{
	char	*path;
	char	**split_path;
	int		result;

	path = find_path_env(env);
	if (!path)
		return (0);
	split_path = ft_split(path, ':');
	if (!split_path)
		return (0);
	result = check_path_access(split_path, str);
	free_split(split_path);
	return (result);
}

static void	init_exec_struct(struct s_exec *ret, t_node *list, int i, int len)
{
	ret[i].exec = ft_strdup(list->cmd->cmd_and_args[0]);
	ret[i].argv = clone_cdt(list->cmd->cmd_and_args);
	ret[i].nb_exec = len;
	ret[i].infile = list->cmd->input_str;
	ret[i].outfile = list->cmd->output_str;
	ret[i].out = -1;
	ret[i].in = -1;
	ret[i].pid = -1;
}

static void	free_env_array(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

struct s_exec	*lst_to_execs(t_node *list, int *len)
{
	struct s_exec	*ret;
	int				i;
	char			**env;

	*len = lst_len(list);
	ret = ft_calloc(*len, sizeof(struct s_exec));
	if (!ret)
		return (NULL);
	env = get_env_cdt(list->env);
	i = 0;
	while (list)
	{
		init_exec_struct(ret, list, i, *len);
		ret[i].envp = clone_cdt(env);
		i++;
		list = list->next;
	}
	free_env_array(env);
	return (ret);
}
