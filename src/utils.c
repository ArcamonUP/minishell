/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:49:10 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/26 11:47:41 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "^C\n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	parent_ctrl_c(int sig)
{
	(void)sig;
}

char	*dupcheck(char **env, int i, char *str)
{
	char	*temp;

	if (i > 0 && !env[i - 1])
		return (NULL);
	temp = ft_strdup(str);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*get_exec(char *cmd)
{
	char	*path;
	char	*temp;

	temp = getcwd(NULL, 0);
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, "/");
	free(temp);
	if (!path)
		return (NULL);
	temp = path;
	path = ft_strjoin(temp, cmd);
	if (!path)
		return (free(temp), NULL);
	return (free(temp), path);
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
	return (free_tab(path), get_exec(cmd));
}
