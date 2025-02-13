/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:40:53 by achu              #+#    #+#             */
/*   Updated: 2025/02/13 05:25:50 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Search through every paths for the current commmand
// and return the path with the command if found, or Null if not
static char	*ft_check_cmd(char **path, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], cmd);
		if (!temp)
			return (NULL);
		if (access(temp, X_OK) == 0)
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
}

static int	ft_exec_cmd(t_node *node, char *path[])
{
	pid_t	pid;
	int		status;
	char	**args;
	char	*temp;

	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		args = ft_split(node->str, ' ');
		if (!args)
			exit (EXIT_FAILURE);
		if (access(args[0], X_OK) < 0)
		{
			temp = ft_check_cmd(path, args[0]);
			if (!temp)
				return (1);
			free(args[0]);
			args[0] = temp;
		}
		execve(args[0], args, NULL);
		ft_printf("Error: command failed\n");
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	ft_execute_tree(t_node *node, char *path[])
{
	int	left;

	if (!node)
		return (0);
	if (node->type == CMD)
		return (ft_exec_cmd(node, path));
	if (node->type == AND)
	{
		left = ft_execute_tree(node->left, path);
		if (left == 0)
			return (ft_execute_tree(node->right, path));
		return (left);
	}
	if (node->type == OR)
	{
		left = ft_execute_tree(node->left, path);
		if (left != 0)
			return (ft_execute_tree(node->right, path));
		return (left);
	}
	return (1);
}
