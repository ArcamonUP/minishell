/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:31:41 by kbaridon          #+#    #+#             */
/*   Updated: 2025/04/01 14:11:13 by kbaridon         ###   ########.fr       */
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

char	*get_value(char *cmd, char *result, char **envp, int *y)
{
	int		temp;
	char	*name;
	char	*joined;
	char	*var;

	(*y)++;
	temp = *y;
	while (cmd[*y] && cmd[*y] != ' ' && \
	cmd[*y] != '\"' && cmd[*y] != '\'')
		(*y)++;
	if (cmd[*y] == '\'' || cmd[*y] == '\"')
		return (result);
	name = ft_substr(cmd, temp, *y - temp);
	if (!name)
		return (result);
	if (!cmd[*y])
		(*y)--;
	var = get_var(name, envp);
	free(name);
	if (!var)
		return (result);
	joined = ft_strjoin(result, var);
	if (!joined)
		return (free(var), result);
	return (free(result), free(var), joined);
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

	y = 0;
	while (cmd[y])
	{
		if (cmd[y] == '\"' || cmd[y] == '\'')
		{
			if (*c == cmd[y])
				*c = 0;
			else if (*c == 1)
				*c = cmd[y];
		}
		if (cmd[y] == '$' && *c != '\'')
			str = get_value(cmd, str, envp, &y);
		else if ((*c == 0 && cmd[y] != '\"' && cmd[y] != '\'') || \
		(*c != 0 && *c != cmd[y]))
			str = ft_strjoin_char(str, cmd[y]);
		y++;
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
		//ft_printf("-----\ntemp = %s\n cmd[%d] = %s\n", temp, i, cmd[i]);
		if (temp && cmd[i])
			write(STDOUT_FILENO, " ", 1);
		free(temp);
	}
	if (!cmd[1] || ft_strncmp(cmd[1], "-n", 2) != 0)
		write(STDOUT_FILENO, "\n", 1);
	return (free_tab(cmd), 0);
}
