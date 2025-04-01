/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:31:41 by kbaridon          #+#    #+#             */
/*   Updated: 2025/04/01 17:52:28 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

char	*get_value(char *cmd, char *result, char **envp, int *y)
{
	int		temp;
	char	*name;
	char	*joined;
	char	*var;

	(*y)++;
	temp = *y;
	while (cmd[*y] && ft_isalnum(cmd[*y]))
		(*y)++;
	if ((cmd[*y] == '\'' || cmd[*y] == '\"') && cmd[temp - 1] != cmd[*y])
		return ((*y)--, result);
	if (cmd[*y - 1] == ',')
		(*y)--;
	if (cmd[*y] == '?')
		(*y)++;
	name = ft_substr(cmd, temp, *y - temp);
	if (!name)
		return (result);
	if (!cmd[*y] || !ft_isalnum(cmd[*y]) || cmd[*y - 1] == '?')
		(*y)--;
	var = get_var(name, envp);
	joined = ft_strjoin(result, var);
	if (!joined)
		return (free(var), free(name), result);
	return (free(result), free(var), free(name), joined);
}

static char	*ft_strjoin_char(char *str, char c)
{
	int		i;
	char	*result;

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

static char	*get_arg(char *str, char *cmd, char **envp, int *c)
{
	int		y;

	y = -1;
	while (cmd[y++ + 1])
	{
		if (cmd[y] == '\"' || cmd[y] == '\'')
		{
			if (*c == cmd[y])
				*c = 0;
			else if (*c == 0)
				*c = cmd[y];
		}
		if (cmd[y] == '$' && *c != '\'' && cmd[y + 1] && \
			(ft_isalnum(cmd[y + 1]) || cmd[y + 1] == '?'))
		{
			if (*c != 0)
				cmd[y] = *c;
			str = get_value(cmd, str, envp, &y);
		}
		else if ((*c == 0 && cmd[y] != '\"' && cmd[y] != '\'') || \
		(*c != 0 && *c != cmd[y]))
			str = ft_strjoin_char(str, cmd[y]);
	}
	return (str);
}

static char	*get_phrase(char **cmd, int *i, char **envp)
{
	int		c;
	char	*result;

	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	c = 1;
	while (cmd[*i] && c != 0)
	{
		if (c == 1)
			c = 0;
		else
			result = ft_strjoin_char(result, ' ');
		result = get_arg(result, cmd[*i], envp, &c);
		if (!result)
			return (NULL);
		(*i)++;
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
		temp = get_phrase(cmd, &i, envp);
		if (temp)
			ft_putstr_fd(temp, STDOUT_FILENO);
		if (temp && cmd[i])
			write(STDOUT_FILENO, " ", 1);
		free(temp);
	}
	if (!cmd[1] || ft_strncmp(cmd[1], "-n", 2) != 0)
		write(STDOUT_FILENO, "\n", 1);
	return (free_tab(cmd), 0);
}
