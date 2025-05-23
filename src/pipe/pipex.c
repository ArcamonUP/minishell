/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:23:58 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/28 10:43:53 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

static void	exec(char *cmd, t_pipex_data data, int fd[2])
{
	char	**args;
	char	*path;

	dispatch_pipex(cmd, data, fd);
	args = ft_argsplit(cmd, data.envp);
	if (args)
		path = get_path(args[0], data.envp);
	if (!args || !path)
	{
		(exec_free(data.cmd, data.envp, data.node), free_tab(args));
		(error("minishell: ", args[0]), error(": command not found\n", NULL));
		(close(data.fd[0]), close(data.fd[1]));
		if (fd)
			close(fd[1]);
		(close(data.s_stdin), close(data.s_stdout), close(fd[1]));
		(free_pidtab((void **)data.pid_tab), free_tab(data.tab), exit(127));
	}
	execve(path, args, data.envp);
	(error("minishell: ", args[0]), error(": command not found\n", NULL));
	(free_tab(args), exec_free(data.cmd, data.envp, data.node), free(path));
	(free_tab(data.tab), close(data.fd[0]), close(data.fd[1]));
	if (fd)
		close(fd[1]);
	(close(data.s_stdin), close(data.s_stdout));
	(free_pidtab((void **)data.pid_tab), exit(127));
}

static pid_t	pre_exec(char *cmd, t_pipex_data data)
{
	pid_t	p;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	signal(SIGQUIT, ctrl_backslash);
	p = fork();
	if (p == -1)
		return (-1);
	if (p == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec(cmd, data, fd);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (p);
}

static int	last_exec(t_pipex_data data, int fd)
{
	pid_t	p;
	int		i;
	int		status;

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
	(signal(SIGINT, parent_ctrl_c), signal(SIGQUIT, parent_ctrl_backslash));
	wait_children(data, p, &status);
	(signal(SIGQUIT, ignore), signal(SIGINT, ctrl_c));
	free_tab(data.cmd);
	if (g_exit_status == 131 || g_exit_status == 130)
		return (g_exit_status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
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
