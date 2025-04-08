/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:06:25 by kbaridon          #+#    #+#             */
/*   Updated: 2025/04/08 14:18:47 by kbaridon         ###   ########.fr       */
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

static char	*get_next(char *line, int *y, char **envp, int c)
{
	char	*result;

	(*y)--;
	result = ft_calloc(1, 1);
	while (line[++(*y)] && (line[*y] != ' ' || c != 0) && result)
	{
		c = get_c_value(line[*y], c);
		if (line[*y] == '$' && c != '\'' && line[*y + 1] && \
			(ft_isalnum(line[*y + 1]) || line[*y + 1] == '?'))
		{
			if (c != 0)
				line[*y] = c;
			result = get_value(line, result, envp, y);
		}
		else if (c == 0 && line[*y] == '*')
			result = ft_strjoin_char(result, (char)0xFF);
		else if ((c == 0 && line[*y] != '\"' && line[*y] != '\'') || \
		(c != 0 && c != line[*y]))
			result = ft_strjoin_char(result, line[*y]);
	}
	if (!result)
		return (NULL);
	if (line[*y])
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

char	*get_wildcards(char *str)
{
	char	**tab;
	char	*temp;
	int		i;

	pre_asterisk(str);
	tab = get_file(str);
	if (!tab)
		return (NULL);
	free(str);
	str = ft_strdup(tab[0]);
	i = 1;
	while (tab[i])
	{
		temp = ft_strjoin_char(str, ' ');
		str = ft_strjoin(temp, tab[i]);
		free(temp);
		if (!str)
			return (free_tab(tab), NULL);
		i++;
	}
	return (free_tab(tab), str);
}

char	**ft_divise(char *line, char **envp, int y)
{
	char	**result;
	char	*temp;

	result = ft_calloc(2, sizeof(char *));
	if (!result)
		return (NULL);
	while (*line && *line != ' ')
		line++;
	if (*line)
		line++;
	while (line[y] && result)
	{
		temp = get_next(line, &y, envp, 0);
		if (!temp || !temp[0])
		{
			if (temp)
				free(temp);
			continue ;
		}
		if (ft_strchr(temp, (unsigned char)0xFF))
			temp = get_wildcards(temp);
		result = add_str(result, temp);
	}
	return (result);
}
