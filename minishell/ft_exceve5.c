/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:42:58 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/30 15:03:40 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_exec	dup_exec(struct s_exec e)
{
	struct s_exec	ret;
	int				i;

	ret.exec = ft_strdup(e.exec);
	ret.argv = ft_calloc(cdt_len(e.argv) + 1, sizeof(char *));
	ret.envp = ft_calloc(cdt_len(e.envp) + 1, sizeof(char *));
	i = 0;
	while (ret.argv && e.argv[i])
	{
		ret.argv[i] = ft_strdup(e.argv[i]);
		i++;
	}
	i = 0;
	while (ret.envp && e.envp[i])
	{
		ret.envp[i] = ft_strdup(e.envp[i]);
		i++;
	}
	ret.in = e.in;
	ret.out = e.out;
	return (ret);
}

int	strequ(char *s1, char *s2)
{
	return (ft_strcmp(s1, s2) == 0);
}

int	builtin(char *name)
{
	int	founded;

	founded = 0;
	if (name == NULL)
		return (-1);
	if (strequ(name, "env"))
		founded = 1;
	if (strequ(name, "echo"))
		founded = 2;
	if (strequ(name, "export"))
		founded = 3;
	if (strequ(name, "cd"))
		founded = 4;
	if (strequ(name, "unset"))
		founded = 5;
	if (strequ(name, "pwd"))
		founded = 6;
	if (strequ(name, "exit"))
		founded = 7;
	return (founded);
}

int	exec(char *name, char **argv, char ***envp)
{
	if (!builtin(name))
	{
		if (!ft_strchr(name, '/'))
			name = get_path(name, *envp);
		if (name)
		{
			execve(name, argv, (*envp));
			ft_putstr_fd(name, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			if (errno == 13)
				return (126);
		}
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	return (0);
}

void	sort_envp_ex(char **copy_envp)
{
	char	*tmp;
	int		num_envp;
	int		i;
	int		j;

	num_envp = 0;
	while (copy_envp[num_envp] != NULL)
		num_envp++;
	i = -1;
	while (++i < num_envp - 1)
	{
		j = -1;
		while (++j < num_envp - i - 1)
		{
			if (ft_strcmp(copy_envp[j], copy_envp[j + 1]) > 0)
			{
				tmp = copy_envp[j];
				copy_envp[j] = copy_envp[j + 1];
				copy_envp[j + 1] = tmp;
			}
		}
	}
}
