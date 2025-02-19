/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:03:17 by achu              #+#    #+#             */
/*   Updated: 2025/02/13 16:55:26 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

e_type	get_optype(char *str)
{
	if (ft_strncmp(str, "|", 0) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "&&", 0) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", 0) == 0)
		return (OR);
	else if (ft_strncmp(str, "<<", 0) == 0)
		return (HEREDOC);
	else if (ft_strncmp(str, ">>", 0) == 0)
		return (APPEND);
	else if (ft_strncmp(str, "<", 0) == 0)
		return (INPUT);
	else if (ft_strncmp(str, ">", 0) == 0)
		return (TRUNC);
	return (CMD);
}

int	is_redir(char *str)
{
	if (ft_strncmp(str, "<<", 0) == 0)
		return (1);
	else if (ft_strncmp(str, ">>", 0) == 0)
		return (1);
	else if (ft_strncmp(str, "<", 0) == 0)
		return (1);
	else if (ft_strncmp(str, ">", 0) == 0)
		return (1);
	return (0);
}

t_node	*ft_node_new(char *str, e_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->str = str;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->fdin = -1;
	node->fdout = -1;
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
	node->fdin = -1;
	node->fdout = -1;
	return (node);
}

void	ft_print_tree(t_node *tree, int depth)
{
	if (!tree)
		return;
	for (int i = 0; i < depth; i++)
		ft_printf("    ");
	switch (tree->type)
	{
		case PIPE:
			ft_printf("%s\n", tree->str);
			break ;
		case AND:
			ft_printf("%s\n", tree->str);
			break ;
		case OR:
			ft_printf("%s\n", tree->str);
			break ;
		case INPUT:
			ft_printf("%s\n", tree->str);
			break ;
		case TRUNC:
			ft_printf("%s\n", tree->str);
			break ;
		case APPEND:
			ft_printf("%s\n", tree->str);
			break ;
		case HEREDOC:
			ft_printf("%s\n", tree->str);
			break ;
		case CMD:
			ft_printf("%s\n", tree->str);
			break ;
		case FILENAME:
			ft_printf("%s\n", tree->str);
			break ;
	}
	ft_print_tree(tree->left, depth + 1);
	ft_print_tree(tree->right, depth + 1);
}
