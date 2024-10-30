/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:11:33 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 15:40:53 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_here_doc_files(t_here_doc_data *here_data, t_data *data,
		t_node *list, char *write_here_do)
{
	if (list->cmd->cmd != 0)
	{
		here_data->temp_file_name = create_file_name(here_data->temp_file_name,
				data, write_here_do);
		here_data->tmp_fd = open_file_here_doc(here_data->tmp_fd,
				here_data->temp_file_name, write_here_do);
	}
}

int	handle_write_error(t_here_doc_data *here_doc_data)
{
	if (write(here_doc_data->tmp_fd, here_doc_data->write_here_do,
			here_doc_data->ret) == -1)
	{
		perror("write");
		free(here_doc_data->write_here_do);
		return (1);
	}
	return (0);
}

void	read_input(t_here_doc_data *here_doc_data)
{
	here_doc_data->ret = read(0, here_doc_data->write_here_do, 1023);
	here_doc_data->write_here_do[here_doc_data->ret] = '\0';
}

char	*close_and_return_temp_file(t_here_doc_data *here_doc_data)
{
	close(here_doc_data->tmp_fd);
	if (here_doc_data->write_here_do)
	{
		free(here_doc_data->write_here_do);
	}
	return (here_doc_data->temp_file_name);
}

t_here_doc_data	*get_hd_data(void)
{
	static t_here_doc_data	data;

	return (&data);
}
