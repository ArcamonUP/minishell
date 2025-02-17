/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:58:23 by achu              #+#    #+#             */
/*   Updated: 2025/02/17 12:53:28 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_heredoc_count(t_node *node, int *i)
{
	if (!node)
		return ;
	else if (node->type == HEREDOC)
		(*i)++;
	ft_heredoc_count(node->left, i);
	ft_heredoc_count(node->right, i);
}

int	ft_limiter(t_node	*node)
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

void	ft_init_heredoc(t_node *tree, t_shell *data)
{
	if (!tree)
		return ;
	else if (tree->type == HEREDOC)
	{
		data->heredoc_fd[data->heredoc_count] = ft_limiter(tree->right);
		if (data->heredoc_fd < 0)
			return ;
		data->heredoc_count++;
	}
	ft_init_heredoc(tree->left, data);
	ft_init_heredoc(tree->right, data);
}

int	ft_exec_heredoc(t_node *node, t_shell *data)
{
	t_node	*hdoc;

	hdoc = node;
	while (hdoc->left)
		hdoc = hdoc->left;
	hdoc->is_hdoc++;
	return (ft_execute_tree(node->left, data));
}