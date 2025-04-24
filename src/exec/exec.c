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

// Execute custom function
int	ft_custom_exec(char *line, t_shell *data)
{
	int		exit_code;

	if (is_word(line, "echo"))
		exit_code = ft_echo(line, data->envp);
	else if (is_word(line, "pwd"))
		exit_code = ft_pwd();
	else if (is_word(line, "cd"))
		exit_code = ft_cd(line, data->envp);
	else if (is_word(line, "export"))
		exit_code = ft_export(line, &data->envp, 0);
	else if (is_word(line, "unset"))
		exit_code = ft_unset(line, &data->envp);
	else if (is_word(line, "env"))
		exit_code = ft_env(data->envp);
	else
		return (-1);
	return (exit_code);
}

// Dup2 the STDOUT to output file for custom function
// None of the custom function require dup2 STDIN
static int	ft_custom_fdio(t_node *leaf, t_shell *data)
{
	int	fd;
	int	exit_code;

	if (!is_buildin(leaf->str))
		return (-1);
	fd = dup(STDOUT_FILENO);
	if (fd < 0)
		return (ft_perror("Dup failed\n"), -1);
	if (leaf->fdout && leaf->fdout->fd)
	{
		if (dup2(leaf->fdout->fd, STDOUT_FILENO) == 0)
			return (close(fd), ft_perror("Dup2 failed\n"), -1);
	}
	exit_code = ft_custom_exec(leaf->str, data);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), ft_perror("Error\n"), -1);
	close(fd);
	return (exit_code);
}

static void	exec_child(int fd, t_node *node, t_shell *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_argsplit(node->str, data->envp);
	if (!cmd)
		exit(1);
	path = get_path(cmd[0], data->envp);
	if (!path)
	{
		(error("minishell: ", cmd[0]), error(": command not found\n", NULL));
		(free_tab(cmd), free_tab(data->envp));
		exit(127);
	}
	if (node->fdin && node->fdin->fd != -1)
		dup2(node->fdin->fd, STDIN_FILENO);
	if (node->fdout && node->fdout->fd != -1)
		dup2(node->fdout->fd, STDOUT_FILENO);
	if (fd > -1)
		close(fd);
	execve(path, cmd, data->envp);
	(error("minishell: ", cmd[0]), error(": command not found\n", NULL));
	ft_lstfd_clear(&node->fdin);
	ft_lstfd_clear(&node->fdout);
	(free_tab(data->envp), free_tab(cmd));
	exit(127);
}

static int	exec_cmd(t_node *node, t_shell *data, int fd)
{
	pid_t	pid;
	int		status;

	status = ft_custom_fdio(node, data);
	if (status > -1)
		return (status);
	signal(SIGQUIT, ctrl_backslash);
	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
		exec_child(fd, node, data);
	signal(SIGINT, parent_ctrl_c);
	signal(SIGQUIT, parent_ctrl_backslash);
	if (ft_strncmp("./minishell", node->str, 12) == 0)
		(signal(SIGINT, ignore), signal(SIGQUIT, ignore));
	waitpid(pid, &status, 0);
	(signal(SIGINT, ctrl_c), signal(SIGQUIT, ignore));
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
		return (exec_cmd(node, data, fd));
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
