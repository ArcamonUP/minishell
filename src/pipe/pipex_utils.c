/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:57:15 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/05 11:15:48 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft.h"
#include "pipex.h"
#include "minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	error(char *msg, char *other)
{
	ft_putstr_fd(msg, 2);
	if (other)
		ft_putstr_fd(other, 2);
	ft_putstr_fd("\n", 2);
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
	error("Unable to open the files\n", NULL);
}

void	wait_children(t_pipex_data data, pid_t p)
{
	int	i;

	i = 0;
	while (data.pid_tab[i])
		waitpid(data.pid_tab[i++], NULL, 0);
	free(data.pid_tab);
	waitpid(p, NULL, 0);
}

void	dispatch_pipex(char *line, t_pipex_data data, int fd[2])
{
	//ft_split temporaire en attendant le parsing
	if (ft_strncmp(line, "echo", 4) == 0)
		ft_echo(ft_split(line, ' '));
	else if (ft_strncmp(line, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(line, "cd", 2) == 0)
		ft_cd(ft_split(line, ' '));
	else if (ft_strncmp(line, "export", 6) == 0)
		ft_export(ft_split(line, ' '), data.envp);
	else if (ft_strncmp(line, "unset", 5) == 0)
		ft_unset(ft_split(line, ' '), data.envp);
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_env(data.envp);
	else
		return ;
	free_tab(data.cmd);
	if (fd)
		(close(fd[0]), close(fd[1]));
	if (data.fd[0] != -1)
		close(data.fd[0]);
	close(data.fd[1]);
	exit(EXIT_SUCCESS);
}
