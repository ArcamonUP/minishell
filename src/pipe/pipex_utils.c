/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:57:15 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/28 14:34:38 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft.h"
#include "pipex.h"
#include "minishell.h"

int	get_heredoc_fd(t_shell *data)
{
	int		fd;
	t_shell	*temp;

	temp = data;
	fd = -1;
	while (data->fdin)
	{
		if (data->fdin->visited == 0)
		{
			fd = data->fdin->fd;
			data->fdin->visited = 1;
			break ;
		}
		data->fdin = data->fdin->next;
	}
	data = temp;
	return (fd);
}

void	error(char *msg, char *other)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	if (other)
		ft_putstr_fd(other, STDERR_FILENO);
}

void	end(t_pipex_data data, int i)
{
	if (data.fd[1] != -1)
		close(data.fd[1]);
	if (!i)
	{
		if (data.fd[0] != -1)
			close(data.fd[0]);
	}
	free_tab(data.cmd);
	dup2(data.s_stdin, STDIN_FILENO);
	dup2(data.s_stdout, STDOUT_FILENO);
	close(data.s_stdin);
	close(data.s_stdout);
	error("Error\n", NULL);
}

void	wait_children(t_pipex_data data, pid_t p, int *status)
{
	int	i;

	i = 0;
	while (data.pid_tab[i])
		waitpid(data.pid_tab[i++], NULL, 0);
	free(data.pid_tab);
	waitpid(p, status, 0);
}

void	dispatch_pipex(char *line, t_pipex_data data, int fd[2])
{
	int	exit_code;

	if (is_word(line, "echo"))
		exit_code = ft_echo(line, data.envp);
	else if (is_word(line, "pwd"))
		exit_code = ft_pwd();
	else if (is_word(line, "cd"))
		exit_code = ft_cd(line, data.envp);
	else if (is_word(line, "export"))
		exit_code = ft_export(line, &data.envp, 0);
	else if (is_word(line, "unset"))
		exit_code = ft_unset(line, &data.envp);
	else if (is_word(line, "env"))
		exit_code = ft_env(data.envp);
	else
		return ;
	exec_free(data.cmd, data.envp, data.node);
	(free_tab(data.tab), close(data.fd[0]), close(data.fd[1]));
	(close(data.s_stdin), close(data.s_stdout), close(fd[1]));
	free_pidtab((void **)data.pid_tab);
	exit(exit_code);
}
