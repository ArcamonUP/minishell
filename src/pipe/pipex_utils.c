/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:57:15 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/03 11:51:02 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft.h"
#include "pipex.h"

void	error(char *msg)
{
	ft_putstr_fd(msg, 2);
	perror("Error");
}

void	pipex_end(t_pipex_data data, int i)
{
	if (data.fd[1] != -1)
		close(data.fd[1]);
	if (!i)
	{
		if (data.fd[0] != -1)
			close(data.fd[0]);
	}
	pipex_free(data.cmd);
	error("Unable to open the files\n");
}

void	pipex_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_path(char *cmd, char **envp)
{
	char	**path;
	char	*result;
	char	*temp;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path && path[i])
	{
		temp = ft_strjoin(path[i], "/");
		result = ft_strjoin(temp, cmd);
		free(temp);
		if (access(result, F_OK) == 0)
		{
			pipex_free(path);
			return (result);
		}
		(free(result), i++);
	}
	return (pipex_free(path), NULL);
}

void	wait_children(t_pipex_data data, pid_t p)
{
	int	i;
	int	ac;

	ac = data.ac - 4;
	if (data.fd[0] == -1)
		ac--;
	i = 0;
	while (i < ac)
	{
		if (data.pid_tab[i] != -1)
			waitpid(data.pid_tab[i], NULL, 0);
		i++;
	}
	free(data.pid_tab);
	waitpid(p, NULL, 0);
}
