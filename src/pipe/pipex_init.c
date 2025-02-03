/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:57:56 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/03 11:47:53 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>

static int	file_access(char *filename)
{
	if (access(filename, F_OK) < 0 || access(filename, R_OK) < 0)
		return (0);
	return (1);
}

static void	open_file(t_pipe pipe)
{
	int	fd;

	fd = open(pipe.outfile, O_WRONLY | O_CREAT, 0644);
	if (fd != -1)
		close(fd);
}

int	pipex_init(int ac, t_pipe pipe, char ***cmd)
{
	if (ac < 5)
		return (error("Missing parameters.\n"), 0);
	if (ft_strncmp(pipe.infile, "here_doc", 8) == 0 && ac < 6)
		return (error("Missing paramaters.\n"), 0);
	if (ft_strncmp(pipe.infile, "here_doc", 8) != 0 && \
	!file_access(pipe.infile))
		return (open_file(pipe), \
		error("Missing permissions on the files given.\n"), 0);
	if (access(pipe.outfile, F_OK) > -1 && access(pipe.outfile, W_OK) < 0)
		return (open_file(pipe), \
		error("Missing permissions on the files given.\n"), 0);
	*cmd = pipe.cmd;
	return (1);
}
