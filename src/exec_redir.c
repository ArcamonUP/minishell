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

// If an heredoc is found, the nearsest command traversing the ast
// checking from his left node, right then left, store the heredoc
int	ft_exec_heredoc(t_node *tree, t_shell *data)
{
	int		fd;
	t_node	*leaf;
	t_lstfd	*temp;

	leaf = tree;
	while (leaf->type != CMD)
		leaf = leaf->left;
	fd = data->fdin->fd;
	leaf->fdin = fd;
	temp = data->fdin->next;
	free(data->fdin);
	data->fdin = temp;
	return (ft_execute_tree(tree->left, data));
}

int	ft_exec_input(t_node *tree, t_shell *data)
{
	int		fd;
	t_node	*leaf;
	t_lstfd	*temp;

	leaf = tree;
	while (leaf->type != CMD)
		leaf = leaf->left;
	fd = data->fdin->fd;
	leaf->fdin = fd;
	temp = data->fdin->next;
	free(data->fdin);
	data->fdin = temp;
	return (ft_execute_tree(tree->left, data));
}

int	ft_exec_append(t_node *tree, t_shell *data)
{
	int		fd;
	t_node	*leaf;
	t_lstfd	*temp;

	leaf = tree;
	while (leaf->type != CMD)
		leaf = leaf->left;
	fd = data->fdout->fd;
	leaf->fdout = fd;
	temp = data->fdout->next;
	free(data->fdout);
	data->fdout = temp;
	return (ft_execute_tree(tree->left, data));
}

int	ft_exec_trunc(t_node *tree, t_shell *data)
{
	int		fd;
	t_node	*leaf;
	t_lstfd	*temp;

	leaf = tree;
	while (leaf->type != CMD)
		leaf = leaf->left;
	fd = data->fdout->fd;
	leaf->fdout = fd;
	temp = data->fdout->next;
	free(data->fdout);
	data->fdout = temp;
	return (ft_execute_tree(tree->left, data));
}