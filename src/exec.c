/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:40:53 by achu              #+#    #+#             */
/*   Updated: 2025/03/26 13:50:20 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "pipex.h"
#include <signal.h>

int	dispatch(char *line, t_shell *data)
{
	int		exit_code;
	char	**temp;

	temp = cp_tab(data->envp);
	if (ft_strncmp(line, "echo", 4) == 0)
		exit_code = ft_echo(line, temp);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		exit_code = ft_pwd(temp);
	else if (ft_strncmp(line, "cd", 2) == 0)
		exit_code = ft_cd(line, &temp, data->custom_envp);
	else if (ft_strncmp(line, "export", 6) == 0)
		exit_code = ft_export(line, &temp);
	else if (ft_strncmp(line, "unset", 5) == 0)
		exit_code = ft_unset(line, &temp);
	else if (ft_strncmp(line, "env", 3) == 0)
		exit_code = ft_env(temp);
	else
		return (free_tab(temp), -1);
	if (data->custom_envp == 1)
		free_tab(data->envp);
	data->envp = temp;
	data->custom_envp = 1;
	return (exit_code);
}

static void	child_process(int fd, t_node *node, t_shell *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(node->str, ' ');
	if (!cmd)
		exit(EXIT_FAILURE);
	path = get_path(cmd[0], data->envp);
	if (!path)
		(free_tab(cmd), exit(127));
	if (node->fdin != -1)
		dup2(node->fdin, STDIN_FILENO);
	if (node->fdout != -1)
		dup2(node->fdout, STDOUT_FILENO);
	if (fd > -1)
		close(fd);
	execve(path, cmd, data->envp);
	free_tab(cmd);
	ft_putstr_fd("Error: command failed\n", 2);
	exit(126);
}

static int	ft_exec_cmd(t_node *node, t_shell *data, int fd)
{
	pid_t	pid;
	int		status;

	status = dispatch(node->str, data);
	if (status > -1)
		return (status);
	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
		child_process(fd, node, data);
	signal(SIGINT, parent_ctrl_c);
	waitpid(pid, &status, 0);
	signal(SIGINT, ctrl_c);
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
