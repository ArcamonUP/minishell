/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:49:10 by kbaridon          #+#    #+#             */
/*   Updated: 2025/04/02 14:15:15 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

char	*get_var(char *arg, char **envp)
{
	char	*result;
	char	*temp;
	int		i;

	if (ft_strncmp(arg, "?\0", 2) == 0)
		return (ft_itoa(g_exit_status));
	temp = ft_strjoin(arg, "=");
	if (!temp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(temp, envp[i], ft_strlen(temp)) == 0)
		{
			result = ft_strdup(envp[i] + ft_strlen(temp));
			free(temp);
			return (result);
		}
		i++;
	}
	free(temp);
	return (NULL);
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
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
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
			return (free_tab(path), result);
		(free(result), i++);
	}
	return (free_tab(path), get_exec(cmd));
}
