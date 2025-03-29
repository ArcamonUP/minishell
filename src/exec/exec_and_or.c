/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:16:56 by achu              #+#    #+#             */
/*   Updated: 2025/03/14 09:07:00 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// If the left node executed successfully
// then the right node is executed
int	ft_exec_and(t_node *tree, t_shell *data, int fd)
{
	int	left;

	left = ft_execute_tree(tree->left, data, fd);
	if (left == 0)
		return (ft_execute_tree(tree->right, data, fd));
	return (left);
}

// If the left node executed unsuccessfully
// then the right node is executed
int	ft_exec_or(t_node *tree, t_shell *data, int fd)
{
	int	left;

	left = ft_execute_tree(tree->left, data, fd);
	if (left != 0)
		return (ft_execute_tree(tree->right, data, fd));
	return (left);
}
