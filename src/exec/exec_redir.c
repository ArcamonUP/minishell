/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:16:37 by achu              #+#    #+#             */
/*   Updated: 2025/03/28 18:21:03 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>

// If an heredoc is found, the nearsest command traversing the ast
// checking from his left node, right then left, store the heredoc
int	ft_exec_heredoc(t_node *tree, t_shell *data, int pipe_fd)
{
	t_node	*leaf;
	t_lstfd	*temp;

	leaf = tree;
	temp = data->fdin;
	while (leaf->left && leaf->type != CMD)
		leaf = leaf->left;
	while (temp && temp->visited == 1)
		temp = temp->next;
	temp->visited = 1;
	leaf->fdin = temp;
	return (ft_execute_tree(tree->left, data, pipe_fd));
}

int	ft_exec_input(t_node *tree, t_shell *data, int pipe_fd)
{
	t_node	*leaf;
	t_lstfd	*temp;

	leaf = tree;
	temp = data->fdin;
	while (leaf->left && leaf->type != CMD)
		leaf = leaf->left;
	while (temp && temp->visited == 1)
		temp = temp->next;
	temp->visited = 1;
	leaf->fdin = temp;
	return (ft_execute_tree(tree->left, data, pipe_fd));
}

int	ft_exec_append(t_node *tree, t_shell *data, int pipe_fd)
{
	t_node	*leaf;
	t_lstfd	*temp;

	leaf = tree;
	temp = data->fdout;
	while (leaf->left && leaf->type != CMD)
		leaf = leaf->left;
	while (temp && temp->visited == 1)
		temp = temp->next;
	temp->visited = 1;
	leaf->fdin = temp;
	return (ft_execute_tree(tree->left, data, pipe_fd));
}

int	ft_exec_trunc(t_node *tree, t_shell *data, int pipe_fd)
{
	t_node	*leaf;
	t_lstfd	*temp;

	leaf = tree;
	temp = data->fdout;
	while (leaf->left && leaf->type != CMD)
		leaf = leaf->left;
	while (temp && temp->visited == 1)
		temp = temp->next;
	temp->visited = 1;
	leaf->fdin = temp;
	return (ft_execute_tree(tree->left, data, pipe_fd));
}

int	is_buildin(char *line)
{
	if (ft_strncmp(line, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(line, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(line, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(line, "env", 3) == 0)
		return (1);
	return (0);
}
