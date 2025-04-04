/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:06:25 by kbaridon          #+#    #+#             */
/*   Updated: 2025/04/04 10:00:41 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*get_value(char *cmd, char *result, char **envp, int *y)
{
	int		temp;
	char	*name;
	char	*joined;
	char	*var;

	(*y)++;
	temp = *y;
	while (cmd[*y] && ft_isalnum(cmd[*y]))
		(*y)++;
	if (cmd[*y] == '?')
		(*y)++;
	name = ft_substr(cmd, temp, *y - temp);
	if (!name)
		return (result);
	if (!cmd[*y] || !ft_isalnum(cmd[*y]) || cmd[*y - 1] == '?')
		(*y)--;
	var = get_var(name, envp);
	if (!var)
		return (free(name), result);
	joined = ft_strjoin(result, var);
	if (!joined)
		return (free(var), free(name), result);
	return (free(result), free(var), free(name), joined);
}

static char	*ft_strjoin_char(char *str, char c)
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

static char	*get_next(char *line, int *y, char **envp, int c)
{
	int		i;
	char	*result;

	i = *y - 1;
	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	while (line[++i] && (line[i] != ' ' || c != 0))
	{
		if (c == 0 && (line[i] == '\"' || line[i] == '\''))
			c = line[i];
		else if (c == line[i])
			c = 0;
		if (line[i] == '$' && c != '\'' && line[i + 1] && \
			(ft_isalnum(line[i + 1]) || line[i + 1] == '?'))
		{
			if (c != 0)
				line[i] = c;
			result = get_value(line, result, envp, &i);
			if (!result)
				return (NULL);
		}
		else if ((c == 0 && line[i] != '\"' && line[i] != '\'') || \
		(c != 0 && c != line[i]))
			result = ft_strjoin_char(result, line[i]);
	}
	*y = i;
	if (line[i])
		(*y)++;
	return (result);
}

static char	**add_str(char **tab, char *str)
{
	char	**result;
	int		i;
	int		size;

	i = 0;
	size = ft_tablen(tab) + 1;
	result = ft_calloc(sizeof(char *), size + 1);
	if (!result)
		return (free(str), free_tab(tab), NULL);
	while (tab[i])
	{
		result[i] = ft_strdup(tab[i]);
		if (!result[i])
			return (free(str), free_tab(result), free_tab(tab), NULL);
		i++;
	}
	result[i] = str;
	free_tab(tab);
	return (result);
}

char	**ft_divise(char *line, char **envp, int y)
{
	char	**result;
	char	*temp;

	result = ft_calloc(2, sizeof(char *));
	if (!result)
		return (NULL);
	while (*line != ' ')
		line++;
	line++;
	while (line[y])
	{
		temp = get_next(line, &y, envp, 0);
		if (!temp || !temp[0])
		{
			if (temp)
				free(temp);
			continue ;
		}
		result = add_str(result, temp);
		if (!result)
			return (NULL);
	}
	if (!result[0])
		return (free_tab(result), NULL);
	return (result);
	//Does not handle wildcards (for now)
}
