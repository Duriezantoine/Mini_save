/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:03:04 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 13:43:33 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_heredoc_end(t_here_doc_data *data, char *limiteur)
{
	data->test = ft_strncmp(data->write_here_do, limiteur, ft_strlen(limiteur));
	if (data->ret == 0 || data->test == 0)
	{
		if (data->ret == 0)
			handle_end_of_file(limiteur);
		return (1);
	}
	return (0);
}

static void	process_command(t_here_doc_data *data)
{
	int	error;

	if (data->list->cmd->cmd != 0)
	{
		error = handle_write_error(data);
		if (error)
			clean_and_exit(data, error);
	}
}

void	heredoc_process(t_here_doc_data here_doc_data, char *limiteur)
{
	signal(SIGQUIT, heredoc_handle_sig);
	signal(SIGINT, heredoc_handle_sig);
	here_doc_data.write_here_do = ft_calloc(sizeof(char), 1023);
	*(get_hd_data()) = here_doc_data;
	while (1)
	{
		if (check_heredoc_end(&here_doc_data, limiteur))
			break ;
		process_command(&here_doc_data);
		read_input(&here_doc_data);
	}
	clean_and_exit(&here_doc_data, 0);
}

char	*wait_heredoc_process(t_here_doc_data here_doc_data,
							t_node *list, int heredoc_pid)
{
	int	status;

	signal(SIGQUIT, handler_void);
	signal(SIGINT, handler_void);
	if (waitpid(heredoc_pid, &status, 0) == -1)
	{
		perror("waitpid");
		free(here_doc_data.temp_file_name);
		close(here_doc_data.tmp_fd);
		return (NULL);
	}
	if (WEXITSTATUS(status) == 130 || WEXITSTATUS(status) == 1)
	{
		free(here_doc_data.temp_file_name);
		close(here_doc_data.tmp_fd);
		return (NULL);
	}
	if (list->cmd->cmd != 0)
		return (close_and_return_temp_file(&here_doc_data));
	return ("No_tmp_name");
}

char	*ft_here_doc(t_data *data, t_node *list, char *limiteur,
		t_node *base_node)
{
	int				heredoc_pid;
	t_here_doc_data	here_doc_data;

	here_doc_data = init_here_doc_data();
	here_doc_data.list = base_node;
	setup_here_doc_files(&here_doc_data, data, list,
		here_doc_data.write_here_do);
	heredoc_pid = fork();
	if (heredoc_pid == -1)
	{
		free(here_doc_data.temp_file_name);
		close(here_doc_data.tmp_fd);
		return (NULL);
	}
	if (heredoc_pid == 0)
	{
		heredoc_process(here_doc_data, limiteur);
		exit(1);
	}
	else
		return (wait_heredoc_process(here_doc_data, list, heredoc_pid));
}
