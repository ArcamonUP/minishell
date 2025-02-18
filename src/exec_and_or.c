/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:16:56 by achu              #+#    #+#             */
/*   Updated: 2025/02/13 17:17:21 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// If the left node executed successfully
// then the right node is executed
int	ft_exec_and(t_node *node, t_shell *data)
{
	int	left;

	left = ft_execute_tree(node->left, data);
	if (left == 0)
		return (ft_execute_tree(node->right, data));
	return (left);
}

// If the left node executed unsuccessfully
// then the right node is executed
int	ft_exec_or(t_node *node, t_shell *data)
{
	int	left;

	left = ft_execute_tree(node->left, data);
	if (left != 0)
		return (ft_execute_tree(node->right, data));
	return (left);
}