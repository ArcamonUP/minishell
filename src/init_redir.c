/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:58:23 by achu              #+#    #+#             */
/*   Updated: 2025/03/28 17:43:20 by achu             ###   ########.fr       */
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
static int	ft_add_fdio(t_shell *data, int fd, t_type op)
{
	t_lstfd	*newfd;

	newfd = ft_lstfd_new(fd);
	if (!newfd)
		return (0);
	if (op == HEREDOC || op == INPUT)
		ft_lstfd_add_back(&data->fdin, newfd);
	else if (op == APPEND || op == TRUNC)
		ft_lstfd_add_back(&data->fdout, newfd);
	return (1);
}

static char	*req_file(char *str)
{
	char	**files;
	char	*file;

	pre_asterisk(str);
	files = get_file(str);
	if (!files)
		return (NULL);
	if (ft_strlen_dbl(files) > 1)
		return (ft_perror("ambiguous redirect"), free_tab(files), NULL);
	file = ft_strdup(files[0]);
	free_tab(files);
	return (file);
}

static int	is_redir(t_node *tree)
{
	if (tree->type == HEREDOC)
		return (1);
	else if (tree->type == INPUT)
		return (1);
	else if (tree->type == APPEND)
		return (1);
	else if (tree->type == TRUNC)
		return (1);
	return (0);
}

// Init the fd of any redirection to
// his correspondant linked list of fd
int	ft_init_fdio(t_shell *data, t_node *tree)
{
	int		fd;
	char	*file;

	fd = -1;
	if (!tree)
		return (0);
	ft_init_fdio(data, tree->left);
	if (is_redir(tree))
	{
		file = req_file(tree->right->str);
		if (!file)
			return (-1);
		if (tree->type == HEREDOC)
			fd = ft_limiter(tree->right->str);
		else if (tree->type == INPUT)
			fd = open(file, O_RDONLY);
		else if (tree->type == APPEND)
			fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (tree->type == TRUNC)
			fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd != -1)
			ft_add_fdio(data, fd, tree->type);
		free(file);
	}
	return (ft_init_fdio(data, tree->right), 1);
}
