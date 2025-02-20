/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:40:53 by achu              #+#    #+#             */
/*   Updated: 2025/02/19 15:14:48 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ft_exec_cmd(t_node *node, t_shell *data)
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

int	ft_execute_tree(t_node *node, t_shell *data)
{
	if (!node)
		return (0);
	else if (node->type == CMD)
		return (ft_exec_cmd(node, data));
	else if (node->type == AND)
		return (ft_exec_and(node, data));
	else if (node->type == OR)
		return (ft_exec_or(node, data));
	else if (node->type == PIPE)
		return (0);
	else if (node->type == HEREDOC)
		return (ft_exec_heredoc(node, data));
	else if (node->type == INPUT)
		return (ft_exec_input(node, data));
	else if (node->type == TRUNC)
		return (ft_exec_trunc(node, data));
	else if (node->type == APPEND)
		return (ft_exec_append(node, data));
	return (1);
}
