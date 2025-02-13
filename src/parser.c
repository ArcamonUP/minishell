/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:03:14 by achu              #+#    #+#             */
/*   Updated: 2025/02/13 09:52:35 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int		is_redir(char *str);
t_type	ft_opcmp(char *shell);
t_node	*ft_node_new(char *str, t_type type);
t_node	*ft_parse_and_or(char ***token);

static t_node	*ft_parse_cmd(char ***token)
{
	t_node	*node;

	if (**token && (ft_strncmp("(", **token, 0) == 0))
	{
		(*token)++;
		node = ft_parse_and_or(token);
		if (node && (ft_strncmp(")", **token, 0) == 0))
			(*token)++;
		else
			return (NULL);
		return (node);
	}
	else
	{
		node = ft_node_new(**token, CMD);
		if (!node)
			return (NULL);
		(*token)++;
		return (node);
	}
}

static t_node	*ft_parse_redir(char ***token)
{
	t_node	*node;
	t_node	*parent;
	t_node	*right;
	char	*op;
	char	*file;

	node = ft_parse_cmd(token);
	if (!node)
		return (NULL);
	while (**token && is_redir(**token))
	{
		op = **token;
		(*token)++;
		file = **token;
		(*token)++;
		right = ft_node_new(file, ft_opcmp(op));
		if (!right)
			return (NULL);
		parent = (t_node *)malloc(sizeof(t_node));
		if (!parent)
			return (NULL);
		parent->str = op;
		parent->type = ft_opcmp(op);
		parent->left = node;
		parent->right = right;
		node = parent;
	}
	return (node);
}

static t_node	*ft_parse_pipe(char ***token)
{
	t_node	*node;
	t_node	*parent;
	t_node	*right;
	char	*op;

	node = ft_parse_redir(token);
	if (!node)
		return (NULL);
	while (**token && (ft_strncmp("|", **token, 0) == 0))
	{
		op = **token;
		(*token)++;
		right = ft_parse_redir(token);
		if (!right)
			return (NULL);
		parent = (t_node *)malloc(sizeof(t_node));
		if (!parent)
			return (NULL);
		parent->str = op;
		parent->type = ft_opcmp(op);
		parent->left = node;
		parent->right = right;
		node = parent;
	}
	return (node);
}

t_node	*ft_parse_and_or(char ***token)
{
	//echo number1 && echo hello || echo salut
	t_node	*node;
	t_node	*parent;
	t_node	*right;
	char	*op;

	node = ft_parse_pipe(token);
	if (!node)
		return (NULL);
	while (**token && (ft_strncmp("&&", **token, 0) == 0 || ft_strncmp("||", **token, 0) == 0))
	{
		op = **token;
		(*token)++;
		right = ft_parse_pipe(token);
		if (!right)
			return (NULL);
		parent = (t_node *)malloc(sizeof(t_node));
		if (!parent)
			return (NULL);
		parent->str = op;
		parent->type = ft_opcmp(op);
		parent->left = node;
		parent->right = right;
		node = parent;
	}
	return (node);
}
