/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:58:23 by achu              #+#    #+#             */
/*   Updated: 2025/03/14 11:40:49 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>

// Write the content of the standard input until
// the limiter is found and return the fd
static int	ft_limiter(char *limit)
{
	int		len;
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (1);
	len = ft_strlen(limit);
	while (1)
	{
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limit, len) == 0 && (line[len] == '\0' || \
		line[len] == '\n'))
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

// Add the fd to the right linked list
static void	ft_add_fdio(t_shell *data, int fd, t_type op)
{
	t_lstfd	*newfd;

	newfd = ft_lstfd_new(fd);
	if (!newfd)
		return ;
	if (op == HEREDOC || op == INPUT)
		ft_lstfd_add_back(&data->fdin, newfd);
	else if (op == APPEND || op == TRUNC)
		ft_lstfd_add_back(&data->fdout, newfd);
}

// Init the fd of any redirection to
// his correspondant linked list of fd
void	ft_init_fdio(t_shell *data, t_node *tree)
{
	int		fd;

	fd = -1;
	if (!tree)
		return ;
	ft_init_fdio(data, tree->left);
	if (tree->type == HEREDOC)
		fd = ft_limiter(tree->right->str);
	else if (tree->type == INPUT)
		fd = open(tree->right->str, O_RDONLY);
	else if (tree->type == APPEND)
		fd = open(tree->right->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (tree->type == TRUNC)
		fd = open(tree->right->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd != -1)
		ft_add_fdio(data, fd, tree->type);
	ft_init_fdio(data, tree->right);
}
