/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:02:52 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 17:49:37 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handle_sig(int signal)
{
	t_here_doc_data	*here_doc_data;

	if (signal == SIGINT)
	{
		here_doc_data = get_hd_data();
		free(here_doc_data->temp_file_name);
		free(here_doc_data->write_here_do);
		close(here_doc_data->tmp_fd);
		ft_free_return_loop(here_doc_data->list);
		ft_free_end(here_doc_data->list, &(here_doc_data->list->env));
		ft_putstr_fd("\n", 2);
		exit(130);
	}
}

int	ft_putchar_fd(char c, int fd)
{
	int	tmp;

	tmp = write(fd, &c, 1);
	return (tmp);
}

int	ft_putendl_fd(char *str, int fd)
{
	int	ret;

	ret = ft_putstr_fd(str, fd);
	ret += ft_putchar_fd('\n', fd);
	return (ret);
}

void	handle_end_of_file(char *limiteur)
{
	ft_putstr_fd("bash: warning: here-document at line 1 "
		"delimited by end-of-file (wanted `",
		2);
	ft_putstr_fd(limiteur, 2);
	ft_putendl_fd("\')", 2);
}

void	clean_and_exit(t_here_doc_data *data, int exit_code)
{
	free(data->temp_file_name);
	free(data->write_here_do);
	ft_free_return_loop(data->list);
	ft_free_end(data->list, &(data->list->env));
	close(data->tmp_fd);
	exit(exit_code);
}
