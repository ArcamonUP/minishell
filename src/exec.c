/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:40:53 by achu              #+#    #+#             */
/*   Updated: 2025/02/13 17:15:36 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_exec_input(char *file);
int	ft_exec_trunc(char *file);
int	ft_exec_append(char *file);
int	ft_exec_here_doc(char *file);

static int	ft_exec_cmd(t_node *node, char *envp[])
{
	pid_t	pid;
	int		status;
	char	**cmd;
	char	*temp;

	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		cmd = ft_split(node->str, ' ');
		if (!cmd)
			exit (EXIT_FAILURE);
		execve(get_path(cmd[0], envp), cmd, NULL);
		free_tab(cmd);
		ft_printf("Error: command failed\n");
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	ft_execute_tree(t_node *node, char *envp[])
{
	int	left;

	if (!node)
		return (0);
	else if (node->type == PIPE)
		return (0);
	else if (node->type == CMD)
		return (ft_exec_cmd(node, envp));
	else if (node->type == AND)
	{
		left = ft_execute_tree(node->left, envp);
		if (left == 0)
			return (ft_execute_tree(node->right, envp));
		return (left);
	}
	else if (node->type == OR)
	{
		left = ft_execute_tree(node->left, envp);
		if (left != 0)
			return (ft_execute_tree(node->right, envp));
		return (left);
	}
	else if (node->type == INPUT)
		return (ft_exec_append(node->right->str));
	else if (node->type == TRUNC)
		return (ft_exec_trunc(node->right->str));
	else if (node->type == APPEND)
		return (ft_exec_append(node->right->str));
	else if (node->type == HERE_DOC)
		return (ft_exec_append(node->right->str));
	return (1);
}
