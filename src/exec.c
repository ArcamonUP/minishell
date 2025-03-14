/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:40:53 by achu              #+#    #+#             */
/*   Updated: 2025/03/14 11:19:18 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	dispatch(char *line, t_shell *data, int fd)
{
	int	exit_code;

	if (ft_strncmp(line, "echo", 4) == 0)
		exit_code = ft_echo(line, data->envp);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		exit_code = ft_pwd();
	else if (ft_strncmp(line, "cd", 2) == 0)
		exit_code = ft_cd(line);
	else if (ft_strncmp(line, "export", 6) == 0)
		exit_code = ft_export(line, data->envp);
	else if (ft_strncmp(line, "unset", 5) == 0)
		exit_code = ft_unset(line, data->envp);
	else if (ft_strncmp(line, "env", 3) == 0)
		exit_code = ft_env(data->envp);
	else
		return ;
	if (fd > -1)
		close(fd);
	exit(exit_code);
}

static int	ft_exec_cmd(t_node *node, t_shell *data, int fd)
{
	pid_t	pid;
	int		status;
	char	**cmd;
	char	*path;

	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		dispatch(node->str, data, 1);
		cmd = ft_split(node->str, ' ');
		if (!cmd)
			exit (EXIT_FAILURE);
		path = get_path(cmd[0], data->envp);
		if (!path)
			exit(127);
		if (node->fdin)
			dup2(node->fdin, STDIN_FILENO);
		if (node->fdout)
			dup2(node->fdout, STDOUT_FILENO);
		if (fd > -1)
			close(fd);
		execve(path, cmd, NULL);
		free_tab(cmd);
		ft_printf("Error: command failed\n");
		exit(126);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	ft_execute_tree(t_node *node, t_shell *data, int fd)
{
	//ft_print_tree(node, 0);
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
