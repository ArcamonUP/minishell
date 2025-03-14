/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:19:51 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/14 10:15:45 by kbaridon         ###   ########.fr       */
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

int	setup_get(char **line, t_node *node, t_shell *shell_data)
{
	int	stdout;
	int	fd[2];

	stdout = dup(STDOUT_FILENO);
	if (stdout == -1)
		return (error("Dup failed.\n", NULL), -1);
	*line = ft_calloc(1, sizeof(char));
	if (!*line)
		return (error("Malloc failed.\n", NULL), close(stdout), -1);
	if (pipe(fd) == -1)
		return (free(*line), close(stdout), error("Pipe error.\n", NULL), -1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		(close(fd[0]), close(fd[1]), close(stdout));
		return (free(*line), error("Dup2 failed.\n", NULL), -1);
	}
	close(fd[1]);
	ft_execute_tree(node, shell_data, fd[0]);
	if (dup2(stdout, STDOUT_FILENO) == -1)
	{
		(close(fd[0]), close(stdout));
		return (free(*line), error("Error.\n", NULL), -1);
	}
	return (close(stdout), close(fd[0]), fd[0]);
}

char	*get_result(t_node *node, t_shell *shell_data)
{
	char	*result;
	char	*temp;
	char	*line;
	int		fd;

	if (node->type == CMD)
		return (ft_strdup(node->str));
	fd = setup_get(&line, node, shell_data);
	if (fd < 0)
		return (NULL);
	temp = get_next_line(fd);
	while (temp)
	{
		result = ft_strjoin(line, temp);
		(free(line), free(temp));
		if (!result)
			return (error("Malloc failed.", NULL), NULL);
		line = result;
		temp = get_next_line(fd);
	}
	close(fd);
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
	temp[0] = get_result(node->left, shell_data);
	if (!temp[0])
		return (error("Execution failed.", NULL), free_tab(temp), data);
	temp[1] = get_result(node->right, shell_data);
	if (!temp[1])
		return (error("Execution failed.", NULL), free_tab(temp), data);
	data.cmd = temp;
	data.envp = shell_data->envp;
	data.pid_tab = NULL;
	data.fd[0] = get_fd_file(node, "<\0", 0);
	data.fd[1] = get_fd_file(node, ">\0", 0);
	if (data.fd[1] == -1)
		data.fd[1] = STDOUT_FILENO;
	return (data);
}
