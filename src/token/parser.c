/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:03:14 by achu              #+#    #+#             */
/*   Updated: 2025/03/28 17:51:32 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_node	*ft_parse_and_or(char ***tokens);
int		is_redir(char *str);

t_node	*ft_parse_leadcmd(char ***tokens)
{
	t_node	*node;
	t_node	*parent;
	t_node	*right;
	char	*op;
	char	*file;

	op = *(*tokens)++;
	file = *(*tokens)++;
	right = ft_node_new(file, FILENAME);
	if (!right)
		return (NULL);
	if (**tokens)
	{
		node = ft_node_new(**tokens, CMD);
		if (!node)
			return (free_node(right), NULL);
		(*tokens)++;
	}
	else
		node = NULL;
	parent = ft_node_parent(op, node, right);
	if (!parent)
		return (NULL);
	node = parent;
	return (node);
}

t_node	*ft_parse_cmd(char ***tokens)
{
	t_node	*node;

	if (**tokens && (ft_strncmp("(", **tokens, 1) == 0))
	{
		(*tokens)++;
		node = ft_parse_and_or(tokens);
		if (!**tokens && (ft_strncmp(")", **tokens, 1) != 0))
			return (NULL);
		(*tokens)++;
		return (node);
	}
	else if (**tokens && is_redir(**tokens))
	{
		node = ft_parse_leadcmd(tokens);
		return (node);
	}
	else if (**tokens)
	{
		node = ft_node_new(**tokens, CMD);
		if (!node)
			return (NULL);
		(*tokens)++;
		return (node);
	}
	return (NULL);
}

t_node	*ft_parse_redir(char ***tokens)
{
	t_node	*node;
	t_node	*parent;
	t_node	*right;
	char	*op;
	char	*file;

	node = ft_parse_cmd(tokens);
	if (!node)
		return (NULL);
	while (**tokens && is_redir(**tokens))
	{
		op = *(*tokens)++;
		file = *(*tokens)++;
		right = ft_node_new(file, FILENAME);
		if (!right)
			return (NULL);
		parent = ft_node_parent(op, node, right);
		if (!parent)
			return (NULL);
		node = parent;
	}
	return (node);
}

t_node	*ft_parse_pipe(char ***tokens)
{
	t_node	*node;
	t_node	*parent;
	t_node	*right;
	char	*op;

	node = ft_parse_redir(tokens);
	if (!node)
		return (NULL);
	while (**tokens && (ft_strncmp("|\0", **tokens, 2) == 0))
	{
		op = *(*tokens)++;
		right = ft_parse_redir(tokens);
		if (!right)
			return (NULL);
		parent = ft_node_parent(op, node, right);
		if (!parent)
			return (NULL);
		node = parent;
	}
	return (node);
}

t_node	*ft_parse_and_or(char ***tokens)
{
	t_node	*node;
	t_node	*parent;
	t_node	*right;
	char	*op;

	node = ft_parse_pipe(tokens);
	if (!node)
		return (NULL);
	while (**tokens && (ft_strncmp("&&\0", **tokens, 3) == 0 || \
	ft_strncmp("||\0", **tokens, 3) == 0))
	{
		op = *(*tokens)++;
		right = ft_parse_pipe(tokens);
		if (!right)
			return (NULL);
		parent = ft_node_parent(op, node, right);
		if (!parent)
			return (NULL);
		node = parent;
	}
	return (node);
}

t_node	*ft_parse_shell(char **tokens)
{
	t_node	*node;

	node = ft_parse_and_or(&tokens);
	if (!node)
		return (NULL);
	return (node);
}
