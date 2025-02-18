/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:58:23 by achu              #+#    #+#             */
/*   Updated: 2025/02/18 01:19:13 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Count recursively the number of heredoc
int	ft_count_hdoc(t_node *node)
{
	int	i;

	i = 0;
	if (!node)
		return (0);
	if (node->type == HEREDOC)
		i = 1;
	return (i + ft_count_hdoc(node->left) + ft_count_hdoc(node->right));
}

// Write the content of the standard input until
// the limiter is found and return the fd
int	ft_limiter(t_node *node)
{
	int		len;
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (1);
	len = ft_strlen(node->str);
	while (1)
	{
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, node->str, len) == 0 && (line[len] == '\0' || line[len] == '\n'))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

// Write the content of every heredoc found to an array of fd
void	ft_init_heredoc(t_node *tree, t_shell *data)
{
	if (!tree)
		return ;
	ft_init_heredoc(tree->left, data);
	if (tree->type == HEREDOC)
	{
		data->heredoc_fd[data->heredoc_count] = ft_limiter(tree->right);
		if (data->heredoc_fd < 0)
			return ;
		data->heredoc_count++;
	}
	ft_init_heredoc(tree->right, data);
}

// If an heredoc is found, the most left branch from this
// node is now signed with an heredoc tag to know when 
// do we need to dup2 the heredoc in the stdin
int	ft_exec_heredoc(t_node *node, t_shell *data)
{
	t_node	*hdoc;

	hdoc = node;
	while (hdoc)
	{
		hdoc = hdoc->left;
		if (hdoc->right->type == CMD)
		{
			hdoc->right->fdin = data->heredoc_fd[data->heredoc_idx];
			data->heredoc_idx++;
		}
		else if (hdoc->left->type == CMD)
		{
			hdoc->left->fdin = data->heredoc_fd[data->heredoc_idx];
			data->heredoc_idx++;
		}
	}
	return (ft_execute_tree(node->left, data));
}
