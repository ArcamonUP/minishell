/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:03:17 by achu              #+#    #+#             */
/*   Updated: 2025/02/11 18:37:46 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

e_type	ft_opcmp(char *str)
{
	if (ft_strncmp(str, "(", 1) == 0)
		return (SUB);
	else if (ft_strncmp(str, ")", 1) == 0)
		return (SUB);
	else if (ft_strncmp(str, "&&", 0) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", 0) == 0)
		return (OR);
	else if (ft_strncmp(str, "|", 0) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "<", 0) == 0)
		return (IN);
	else if (ft_strncmp(str, "<<", 0) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(str, ">", 0) == 0)
		return (OUT);
	else if (ft_strncmp(str, ">>", 0) == 0)
		return (APPEND);
	return (CMD);
}

int	is_redir(char *str)
{
	if (ft_strncmp(str, "<<", 0) == 0)
		return (1);
	if (ft_strncmp(str, ">>", 0) == 0)
		return (1);
	if (ft_strncmp(str, "<", 0) == 0)
		return (1);
	if (ft_strncmp(str, ">", 0) == 0)
		return (1);
	return (0);
}

t_node	*ft_node_new(char *str, e_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return 	(NULL);
	node->str = str;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	ft_printtree(t_node *tree, int depth)
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
		case IN:
			ft_printf("%s\n", tree->str);
			break ;
		case OUT:
			ft_printf("%s\n", tree->str);
			break ;
		case APPEND:
			ft_printf("%s\n", tree->str);
			break ;
		case HERE_DOC:
			ft_printf("%s\n", tree->str);
			break ;
		case CMD:
			ft_printf("%s\n", tree->str);
			break ;
		case SUB:
			break ;
	}
	ft_printtree(tree->left, depth + 1);
	ft_printtree(tree->right, depth + 1);
}
