/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:19:51 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/27 13:47:08 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

int	get_fd_file(t_node *node, char *str, int bonus)
{
	int	fd;

	fd = -1;
	while (node->right && ft_strncmp(node->str, str, 2) != 0)
		node = node->right;
	if (ft_strncmp(node->str, str, 2) == 0 && node->right)
	{
		if (bonus)
			fd = open(node->right->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(node->right->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return (error("Failed to open file.", NULL), -1);
	}
	else
		return (-1);
	return (fd);
}

char	*get_limiter(t_node node)
{
	char	*result;

	result = NULL;
	while (node.right && ft_strncmp(node.str, ">>\0", 3) != 0)
		node = *(node.right);
	if (ft_strncmp(node.str, ">>\0", 3) == 0 && node.right)
	{
		result = ft_strdup(node.right->str);
		if (!result)
			return (error("Malloc failed.", NULL), NULL);
	}
	return (result);
}

char	*get_result(t_node *node, t_shell *shell_data)
{
	char	*result;
	char	*temp;
	char	*line;
	int		fd[2];

	line = NULL;
	if (pipe(fd) == -1)
		return (NULL);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	ft_execute_tree(node, shell_data);
	temp = get_next_line(fd[1]);
	while (temp)
	{
		result = ft_strjoin(line, temp);
		if (line)
			free(line);
		free(temp);
		if (!result)
			return (NULL);
		line = result;
		temp = get_next_line(fd[1]);
	}
	result = ft_strjoin("echo ", line);
	return (free(line), result);
}

t_pipex_data	init_pipex(t_node *node, t_shell *shell_data)
{
	t_pipex_data	data;
	char			**temp;

	data.cmd = NULL;
	temp = ft_calloc(sizeof(char *), 3);
	if (!temp)
		return (error("Malloc failed.", NULL), data);
	temp[0] = get_result(node, shell_data);
	if (!temp[0])
		return (error("Execution failed.", NULL), free_tab(temp), data);
	temp[1] = get_result(node->right, shell_data);
	if (!temp[1])
		return (error("Execution failed.", NULL), free_tab(temp), data);
	data.cmd = temp;
	data.envp = shell_data->envp;
	data.pid_tab = NULL;
	return (data);
}
