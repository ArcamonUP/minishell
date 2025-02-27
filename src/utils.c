/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:49:10 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/27 14:51:15 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	parent_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
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
			free_tab(path);
			return (result);
		}
		(free(result), i++);
	}
	return (free_tab(path), NULL);
}

__pid_t	ft_exec(char *cmd, char **envp)
{
	char	**args;
	char	*path;
	__pid_t	p;

	p = fork();
	if (p == -1)
		return (-1);
	if (p != 0)
		signal(SIGINT, parent_ctrl_c);
	if (p == 0)
	{
		path = NULL;
		args = ft_split(cmd, ' ');
		if (args)
			path = get_path(args[0], envp);
		if (!args || !path)
		{
			//gestion d'erreurs avec free...
			exit(0);
		}
		execve(path, args, envp);
		//gestion d'erreurs avec free...
		exit(0);
	}
	return (p);
}
