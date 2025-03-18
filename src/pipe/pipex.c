/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:23:58 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/18 13:04:42 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

static void	exec(char *cmd, t_pipex_data data, int fd[2])
{
	char	**args;
	char	*path;

	dispatch_pipex(cmd, data, fd);
	path = NULL;
	args = ft_pipex_split(cmd, ' ');
	if (args)
		path = get_path(args[0], data.envp);
	if (!args || !path)
	{
		free_tab(data.cmd);
		free(data.pid_tab);
		error("no such file or directory: ", args[0]);
		free_tab(args);
		if (fd)
			(close(fd[0]), close(fd[1]));
		if (data.fd[0] != -1)
			close(data.fd[0]);
		close(data.fd[1]);
		exit(EXIT_FAILURE);
	}
	execve(path, args, data.envp);
	free_tab(args);
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
		exec(cmd, data, fd);
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
		free_tab(data.cmd);
		return (error("Execution failed.", NULL), 1);
	}
	i = 0;
	while (data.cmd[i + 1])
		i++;
	if (p == 0)
		exec(data.cmd[i], data, NULL);
	wait_children(data, p);
	free_tab(data.cmd);
	return (0);
}

static int	do_cmd(t_pipex_data data)
{
	int	i;
	int	y;

	i = 0;
	data.pid_tab = ft_calloc(sizeof(pid_t), ft_tablen(data.cmd) + 1);
	if (!data.pid_tab)
		return (end(data, 0), 1);
	while (data.cmd[i + 1])
	{
		data.pid_tab[i] = pre_exec(data.cmd[i], data);
		i++;
	}
	y = last_exec(data, data.fd[1]);
	if (data.fd[0] != -1)
		close(data.fd[0]);
	close(data.fd[1]);
	dup2(data.s_stdin, STDIN_FILENO);
	dup2(data.s_stdout, STDOUT_FILENO);
	close(data.s_stdin);
	close(data.s_stdout);
	return (y);
}

int	pipex(t_node *node, t_shell *shell_data)
{
	t_pipex_data	data;

	data = init_pipex(node, shell_data);
	if (!data.cmd)
		return (end(data, 1), 1);
	return (do_cmd(data));
}
