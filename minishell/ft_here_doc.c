/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:44:09 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 14:15:06 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_recu = 0;

char	*create_file_name(char *temp_file_name, t_data *data,
		char *write_here_do)
{
	temp_file_name = malloc(256);
	if (temp_file_name == NULL)
	{
		perror("malloc");
		free(write_here_do);
		exit(EXIT_FAILURE);
	}
	ft_strcpy(temp_file_name, "/tmp/heredoc");
	ft_strcat(temp_file_name, data->count);
	return (temp_file_name);
}

int	open_file_here_doc(int tmp_fd, char *temp_file_name, char *write_here_do)
{
	tmp_fd = open(temp_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (tmp_fd == -1)
	{
		perror("open");
		free(temp_file_name);
		free(write_here_do);
		exit(EXIT_FAILURE);
	}
	return (tmp_fd);
}

t_here_doc_data	init_here_doc_data(void)
{
	t_here_doc_data	data;

	data.write_here_do = NULL;
	data.test = 0;
	data.ret = 1;
	data.temp_file_name = NULL;
	data.tmp_fd = 0;
	return (data);
}
