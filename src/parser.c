/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:03:14 by achu              #+#    #+#             */
/*   Updated: 2025/03/10 12:35:25 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_type			get_optype(char *shell);
t_node			*ft_node_new(char *str, t_type type);
t_node			*ft_node_parent(char *str, t_node *left, t_node *right);
static t_node	*ft_parse_and_or(char ***token);

static t_node	*ft_parse_cmd(char ***tokens)
{
	t_node	*node;
	t_node	*parent;
	t_node	*right;
	char	*op;
	char	*file;

	if (**tokens && (ft_strncmp("(", **tokens, 0) == 0))
	{
		(*tokens)++;
		node = ft_parse_and_or(tokens);
		if (**tokens && (ft_strncmp(")", **tokens, 0) == 0))
			(*tokens)++;
		else
			return (NULL);
		return (node);
	}
	else if (**tokens && is_redir(**tokens))
	{
		op = **tokens;
		(*tokens)++;
		file = **tokens;
		(*tokens)++;
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
	else
	{
		node = ft_node_new(**tokens, CMD);
		if (!node)
			return (NULL);
		(*tokens)++;
		return (node);
	}
}

static t_node	*ft_parse_redir(char ***tokens)
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
		op = **tokens;
		(*tokens)++;
		file = **tokens;
		(*tokens)++;
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

static t_node	*ft_parse_pipe(char ***tokens)
{
	t_node	*node;
	t_node	*parent;
	t_node	*right;
	char	*op;

	node = ft_parse_redir(tokens);
	if (!node)
		return (NULL);
	while (**tokens && (ft_strncmp("|", **tokens, 0) == 0))
	{
		op = **tokens;
		(*tokens)++;
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

static t_node	*ft_parse_and_or(char ***tokens)
{
	t_node	*node;
	t_node	*parent;
	t_node	*right;
	char	*op;

	node = ft_parse_pipe(tokens);
	if (!node)
		return (NULL);
	while (**tokens && (ft_strncmp("&&", **tokens, 0) == 0 || \
	ft_strncmp("||", **tokens, 0) == 0))
	{
		op = **tokens;
		(*tokens)++;
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
