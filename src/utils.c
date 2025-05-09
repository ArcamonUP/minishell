/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:49:10 by kbaridon          #+#    #+#             */
/*   Updated: 2025/04/08 11:45:07 by kbaridon         ###   ########.fr       */
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
	if (access(cmd, F_OK) == 0 && ft_strchr(cmd, '/'))
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

void	pre_asterisk(char *str)
{
	int		in_squote;
	int		in_dquote;
	size_t	i;	

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
			in_squote = !in_squote;
		else if (str[i] && str[i] == '"')
			in_dquote = !in_dquote;
		else if (str[i] == '*' && !in_squote && !in_dquote)
			str[i] = (unsigned char)0xFF;
		i++;
	}
}

char	*ft_strjoin_char(char *str, char c)
{
	int		i;
	char	*result;

	if (c == '\n')
		return (str);
	result = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	if (!result)
		return (str);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	return (free(str), result);
}
