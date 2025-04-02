/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:40:53 by achu              #+#    #+#             */
/*   Updated: 2025/03/28 18:16:45 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "pipex.h"
#include <signal.h>

int	dispatch(char *line, t_shell *data)
{
	int		exit_code;

	if (ft_strncmp(line, "echo", 4) == 0)
		exit_code = ft_echo(line, data->envp);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		exit_code = ft_pwd(data->envp);
	else if (ft_strncmp(line, "cd", 2) == 0)
		exit_code = ft_cd(line, data->envp);
	else if (ft_strncmp(line, "export", 6) == 0)
		exit_code = ft_export(line, &data->envp, 0, 0);
	else if (ft_strncmp(line, "unset", 5) == 0)
		exit_code = ft_unset(line, &data->envp);
	else if (ft_strncmp(line, "env", 3) == 0)
		exit_code = ft_env(data->envp);
	else
		return (-1);
	return (exit_code);
}

static int	fdio_process(t_node	*leaf, t_shell *data)
{
	int	fd;
	int	exit_code;

	fd = dup(STDOUT_FILENO);
	if (fd < 0)
		return (error("Dup failed.\n", NULL), -1);
	if (leaf->fdout)
	{
		if (dup2(leaf->fdout, STDOUT_FILENO) == 0)
			return (close(fd), error("Dup2 failed.\n", NULL), -1);
	}
	exit_code = dispatch(leaf->str, data);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), error("Error.\n", NULL), -1);
	close(fd);
	return (exit_code);
}

static void	child_process(int fd, t_node *node, t_shell *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(node->str, ' ');
	if (!cmd || !cmd[0])
		exit(0);
	path = get_path(cmd[0], data->envp);
	if (!path)
		(free_tab(cmd), free_tab(data->envp), exit(127));
	if (node->fdin != -1)
		dup2(node->fdin, STDIN_FILENO);
	if (node->fdout != -1)
		dup2(node->fdout, STDOUT_FILENO);
	if (fd > -1)
		close(fd);
	execve(path, cmd, data->envp);
	(error("minishell: ", cmd[0]), error(": command not found\n", NULL));
	free_tab(cmd);
	free_tab(data->envp);
	exit(127);
}

static int	ft_exec_cmd(t_node *node, t_shell *data, int fd)
{
	pid_t	pid;
	int		status;

	status = fdio_process(node, data);
	if (status > -1)
		return (status);
	signal(SIGQUIT, ctrl_backslash);
	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
		child_process(fd, node, data);
	signal(SIGINT, parent_ctrl_c);
	signal(SIGQUIT, parent_ctrl_backslash);
	waitpid(pid, &status, 0);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ignore);
	if (g_exit_status == 131 || g_exit_status == 130)
		return (g_exit_status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	ft_execute_tree(t_node *node, t_shell *data, int fd)
{
	if (!node)
		return (0);
	else if (node->type == CMD)
		return (ft_exec_cmd(node, data, fd));
	else if (node->type == AND)
		return (ft_exec_and(node, data, fd));
	else if (node->type == OR)
		return (ft_exec_or(node, data, fd));
	else if (node->type == PIPE)
		return (pipex(node, data));
	else if (node->type == HEREDOC)
		return (ft_exec_heredoc(node, data, fd));
	else if (node->type == INPUT)
		return (ft_exec_input(node, data, fd));
	else if (node->type == TRUNC)
		return (ft_exec_trunc(node, data, fd));
	else if (node->type == APPEND)
		return (ft_exec_append(node, data, fd));
	return (1);
}
