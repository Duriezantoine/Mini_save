/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:32:46 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 11:43:13 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_last_process(struct s_exec *execs, int len, int status)
{
	pid_t	last_pid;
	int		last_exit_status;

	last_exit_status = -1;
	last_pid = execs[len - 1].pid;
	if (ft_exceve_bulting(execs[len - 1].argv[0], 1))
	{
		if (waitpid(last_pid, &status, 0) == -1)
			perror("waitpid");
		if (WIFEXITED(status))
			last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			last_exit_status = 128 + WTERMSIG(status);
			if (last_exit_status == 130 || last_exit_status == 131)
				write(2, "\n", 2);
		}
	}
	return (last_exit_status);
}

int	ft_wait_all(struct s_exec *execs, int len)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < len - 1)
	{
		if (ft_exceve_bulting(execs[i].argv[0], 1))
		{
			if (waitpid(execs[i].pid, &status, 0) == -1)
				perror("waitpid");
		}
		i++;
	}
	return (handle_last_process(execs, len, status));
}

static void	free_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_iofile_list(t_iofile *file)
{
	t_iofile	*tmp;

	while (file)
	{
		free(file->file);
		tmp = file->next;
		free(file);
		file = tmp;
	}
}

void	free_exec(struct s_exec e)
{
	free(e.exec);
	free_str_array(e.argv);
	free_str_array(e.envp);
	if (e.in > 2)
		close(e.in);
	if (e.out > 2)
		close(e.out);
	free_iofile_list(e.infile);
	free_iofile_list(e.outfile);
}
