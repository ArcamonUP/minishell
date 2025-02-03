/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:23:58 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/03 12:19:19 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

static void	exec(char *cmd, t_pipex_data data, int fd[2], int i)
{
	char	**args;
	char	*path;

	path = NULL;
	args = ft_split(cmd, ' ');
	if (args)
		path = get_path(args[0], data.envp);
	if (!args || !path)
	{
		pipex_free(data.cmd);
		free(data.pid_tab);
		if (i == 1)
			error("Execution failed.\n");
		pipex_free(args);
		if (fd)
			(close(fd[0]), close(fd[1]));
		if (data.fd[0] != -1)
			close(data.fd[0]);
		close(data.fd[1]);
		exit(EXIT_FAILURE);
	}
	execve(path, args, data.envp);
	pipex_free(args);
	free(path);
	exit(EXIT_FAILURE);
}

static pid_t	pre_exec(char *cmd, t_pipex_data data)
{
	pid_t	p;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	p = fork();
	if (p == -1)
		return (-1);
	if (p == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec(cmd, data, fd, 0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
	close(fd[0]);
	return (p);
}

static int	last_exec(t_pipex_data data, int fd)
{
	pid_t	p;
	int		i;

	dup2(fd, STDOUT_FILENO);
	p = fork();
	if (p == -1)
	{
		pipex_free(data.cmd);
		return (error("Execution failed."), 1);
	}
	i = 0;
	while (data.cmd[i + 1])
		i++;
	if (p == 0)
		exec(data.cmd[i], data, NULL, 1);
	wait_children(data, p);
	pipex_free(data.cmd);
	return (0);
}

static int	do_cmd(t_pipex_data data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	if (data.fd[0] == -1)
	{
		x = 1;
		i = 1;
	}
	data.pid_tab = ft_calloc(sizeof(pid_t), data.ac - 3 - x);
	if (!data.pid_tab)
		return (pipex_end(data, 0), 1);
	while (data.cmd[i + 1])
	{
		data.pid_tab[i - x] = pre_exec(data.cmd[i], data);
		i++;
	}
	y = last_exec(data, data.fd[1]);
	if (data.fd[0] != -1)
		close(data.fd[0]);
	close(data.fd[1]);
	return (y);
}

int	pipex(t_pipe pipe)
{
	t_pipex_data	data;

	data.envp = pipe.envp;
	data.ac = pipe.ac;
	if (!pipex_init(pipe.ac, pipe, &data.cmd))
		return (1);
	if (ft_strncmp(pipe.infile, "here_doc", 8) == 0)
	{
		data.fd[1] = open(pipe.outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
		data.fd[0] = -1;
		if (data.fd[1] == -1 || !exec_bonus(data))
			return (pipex_end(data, 1), 1);
	}
	else
	{
		data.fd[0] = open(pipe.infile, O_RDONLY);
		data.fd[1] = open(pipe.outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (data.fd[0] == -1 || data.fd[1] == -1)
			return (pipex_end(data, 0), 1);
		dup2(data.fd[0], STDIN_FILENO);
	}
	return (do_cmd(data));
}
