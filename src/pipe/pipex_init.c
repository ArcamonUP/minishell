/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:19:51 by kbaridon          #+#    #+#             */
/*   Updated: 2025/04/04 10:03:28 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

int	get_fd_file(t_node *node, char *str)
{
	int	fd;

	fd = -1;
	while (node)
	{
		if (node->str && ft_strncmp(node->str, str, ft_strlen(str) + 1) == 0)
		{
			if (ft_strncmp(node->str, ">\0", 2) == 0)
				fd = open(node->right->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (ft_strncmp(node->str, ">>\0", 3))
				fd = open(node->right->str, O_CREAT | O_WRONLY | \
					O_APPEND, 0644);
			else if (ft_strncmp(node->str, "<\0", 2) == 0)
				fd = open(node->right->str, O_RDONLY);
			if (fd == -1)
				return (error("Error.\n", NULL), -1);
		}
		if (ft_strncmp(str, "<", 1) == 0 && ft_strncmp(node->str, str, 1) != 0)
			node = node->left;
		else
			node = node->right;
	}
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
	if (node->type == TRUNC && node->left && node->left->type == CMD)
		return (ft_strdup(node->left->str));
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

char	**init_tab_cmd(t_node *node, t_shell *shell_data)
{
	char	**result;
	t_node	*temp;
	int		i;

	i = 1;
	temp = node;
	while (temp && temp->type == PIPE && i++)
		temp = temp->left;
	i--;
	result = ft_calloc(sizeof(char *), i + 2);
	if (!result)
		return (NULL);
	temp = node;
	while (i > -1)
	{
		if (temp->type == PIPE)
			result[i] = get_result(temp->right, shell_data);
		else
			result[i] = get_result(temp, shell_data);
		if (!result[i])
			return (ft_tabnfree(result, i), NULL);
		temp = temp->left;
		i--;
	}
	return (result);
}

int	get_fdin(t_node *node)
{
	int	fd;

	fd = -1;
	while (node)
	{
		if (node->type == CMD)
			return (ft_atoi(node->right->str));
		node = node->left;
	}
	return (fd);
}

t_pipex_data	init_pipex(t_node *node, t_shell *shell_data)
{
	t_pipex_data	data;

	data.cmd = init_tab_cmd(node, shell_data);
	data.envp = shell_data->envp;
	data.pid_tab = NULL;
	data.fd[0] = node->fdin;
	data.fd[1] = node->fdout;
	if (data.fd[1] == -1)
		data.fd[1] = dup(STDOUT_FILENO);
	if (data.fd[0] == -1)
		data.fd[0] = dup(STDIN_FILENO);
	data.s_stdin = dup(STDIN_FILENO);
	data.s_stdout = dup(STDOUT_FILENO);
	//Redirections en attente... (does not work)
	return (data);
}
