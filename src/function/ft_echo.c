/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:31:41 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/28 16:27:26 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

char	*get_var(char *arg, char **envp)
{
	char	*result;
	char	*temp;
	int		i;

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

static int	get_len(char *line)
{
	int	i;
	int	size;
	int	c;

	c = 0;
	size = 0;
	i = 0;
	while (line[i] && (line[i] != ' ' || c != 0))
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (c == line[i])
				c = 0;
			else if (c == 0)
				c = line[i];
		}
		if (line[i] == '$' && c != '\'')
			return (size);
		if ((c == 0 && line[i] != '\"' && line[i] != '\'') || \
		(c != 0 && c != line[i]))
			size++;
		i++;
	}
	return (size);
}

static char	*get_value(char *line, int i, int c)
{
	int		y;
	char	*arg;

	y = 0;
	arg = ft_calloc(sizeof(char), get_len(line) + 1);
	if (!arg)
		return (NULL);
	while (line[i] && (line[i] != ' ' || c != 0))
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (c == line[i])
				c = 0;
			else if (c == 0)
				c = line[i];
		}
		if (line[i] == '$' && c != '\'')
			return (arg);
		if ((c == 0 && line[i] != '\"' && line[i] != '\'') || \
		(c != 0 && c != line[i]))
			arg[y++] = line[i];
		i++;
	}
	return (arg);
}

char	*get_check(char *arg, char **envp)
{
	int		i;
	char	*temp;
	char	*result;

	i = 0;
	while (arg[i] && arg[i] != ' ' && arg[i] != '"')
		i++;
	temp = ft_calloc(sizeof(char), i + 2);
	if (!temp)
		return (NULL);
	while (i-- > 0)
		temp[i] = arg[i];
	result = get_var(temp, envp);
	free(temp);
	return (result);
}

static char	*get_phrase(char *arg, char **envp)
{
	int		i;
	char	*result;
	char	*temp1;
	char	*temp2;

	i = 0;
	result = ft_calloc(1, 1);
	while (arg[i])
	{
		temp1 = get_value(arg, i, 0);
		if (!temp1)
			return (free(result), NULL);
		i = i + ft_strlen(temp1);
		temp2 = ft_strjoin(result, temp1);
		(free(result), free(temp1));
		if (!temp2)
			return (NULL);
		if (!arg[i])
			return (temp2);
		temp1 = get_check(arg + i, envp);
		if (!temp1)
			return (free(temp2), NULL);
		i = i + ft_strlen(temp1);
		result = ft_strjoin(temp2, temp1);
		(free(temp2), free(temp1));
		if (!result)
			return (NULL);
	}
	return (result);
}

int	ft_echo(char *line, char **envp)
{
	int		i;
	char	*temp;
	char	**cmd;

	cmd = ft_split(line, ' ');
	if (!cmd)
		return (127);
	i = 1;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 2) == 0)
		i = 2;
	while (cmd[i])
	{
		if (cmd[i][0] == '$')
			temp = get_var(cmd[i++] + 1, envp);
		else
			temp = get_phrase(cmd[i++], envp);
		if (temp)
			ft_putstr_fd(temp, STDOUT_FILENO);
		if (temp && cmd[i])
			write(1, " ", STDOUT_FILENO);
		free(temp);
	}
	if (!cmd[1] || ft_strncmp(cmd[1], "-n", 2) != 0)
		write(1, "\n", STDOUT_FILENO);
	return (free_tab(cmd), 0);
}

//Pour l'instant : ne fonctionne pas. A fix.
