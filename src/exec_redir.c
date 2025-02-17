/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:16:37 by achu              #+#    #+#             */
/*   Updated: 2025/02/13 17:44:59 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>

int	ft_exec_input(t_node *node, t_shell *data)
{
	int	fd;

	fd = open(node->right->str, O_RDONLY);
	if (fd < 0)
		return (1);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (ft_execute_tree(node->left, data));
}

int	ft_exec_trunc(t_node *node, t_shell *data)
{
	int	fd;

	fd = open(node->right->str, O_WRONLY | O_TRUNC | O_CREAT | 0644);
	if (fd < 0)
		return (1);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (ft_execute_tree(node->left, data));
}

int	ft_exec_append(t_node *node, t_shell *data)
{
	int	fd;

	fd = open(node->right->str, O_WRONLY | O_APPEND | O_CREAT | 0644);
	if (fd < 0)
		return (1);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (ft_execute_tree(node->left, data));
}