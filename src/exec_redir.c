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
int	ft_exec_heredoc(t_node *node, t_shell *data)
{
	
	return (ft_execute_tree(node->left, data));
}

int	ft_exec_input(t_node *node, t_shell *data)
{
	
	return (ft_execute_tree(node->left, data));
}

int	ft_exec_append(t_node *node, t_shell *data)
{
	
	return (ft_execute_tree(node->left, data));
}

int	ft_exec_trunc(t_node *node, t_shell *data)
{
	
	return (ft_execute_tree(node->left, data));
}