/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:03:17 by achu              #+#    #+#             */
/*   Updated: 2025/03/28 17:45:29 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_type	get_optype(char *str)
{
	if (ft_strncmp(str, "|\0", 2) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "&&\0", 3) == 0)
		return (AND);
	else if (ft_strncmp(str, "||\0", 3) == 0)
		return (OR);
	else if (ft_strncmp(str, "<<\0", 3) == 0)
		return (HEREDOC);
	else if (ft_strncmp(str, ">>\0", 3) == 0)
		return (APPEND);
	else if (ft_strncmp(str, "<\0", 2) == 0)
		return (INPUT);
	else if (ft_strncmp(str, ">\0", 2) == 0)
		return (TRUNC);
	return (CMD);
}

int	is_input(char *str)
{
	if (ft_strncmp(str, "<<\0", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "<\0", 2) == 0)
		return (1);
	return (0);
}

int	is_output(char *str)
{
	if (ft_strncmp(str, ">>\0", 3) == 0)
		return (1);
	else if (ft_strncmp(str, ">\0", 2) == 0)
		return (1);
	return (0);
}

t_node	*ft_node_new(char *str, t_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->str = str;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->fdin = NULL;
	node->fdout = NULL;
	return (node);
}

t_node	*ft_node_parent(char *str, t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->str = str;
	node->type = get_optype(str);
	node->left = left;
	node->right = right;
	node->fdin = NULL;
	node->fdout = NULL;
	return (node);
}
