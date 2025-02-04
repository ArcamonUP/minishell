/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:57:15 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/04 14:08:00 by kbaridon         ###   ########.fr       */
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
