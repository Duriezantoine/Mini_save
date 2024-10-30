/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve12.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:57:49 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/30 15:01:57 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_flags_and_fd(t_iofile *iofile, int *oflags, int **open_fd,
			t_exec *exec)
{
	if (iofile->type == INFILE || iofile->type == HEREDOC_INFILE)
	{
		*open_fd = &exec->in;
		*oflags = O_RDONLY;
	}
	else
	{
		*open_fd = &exec->out;
		*oflags = O_WRONLY | O_CREAT;
		if (iofile->type == APPEND)
			*oflags |= O_APPEND;
		else
			*oflags |= O_TRUNC;
	}
}

int	handle_file_opening(t_iofile *iofile, int *open_fd, int oflags)
{
	if (*open_fd > 1)
		close(*open_fd);
	*open_fd = open(iofile->file, oflags, 0644);
	if (*open_fd < 0)
	{
		perror("open");
		return (1);
	}
	return (0);
}

void	clean_iofile(t_iofile **iofile)
{
	t_iofile	*tmp;

	tmp = *iofile;
	*iofile = tmp->next;
	free(tmp->file);
	free(tmp);
}

int	open_in_out(t_exec *exec)
{
	int	oflags;
	int	*open_fd;

	while (exec->iofiles)
	{
		set_flags_and_fd(exec->iofiles, &oflags, &open_fd, exec);
		if (handle_file_opening(exec->iofiles, open_fd, oflags))
			return (1);
		clean_iofile(&exec->iofiles);
	}
	return (0);
}
