/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:41:17 by achu              #+#    #+#             */
/*   Updated: 2025/02/14 14:21:27 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*ft_token_op(const char *line)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (line[len] && is_operator(line[len]))
		len++;
	if (ft_strncmp("(", line, 1) == 0 || ft_strncmp(")", line, 1) == 0)
		len = 1;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static int	ft_quote_count(const char *line)
{
	int	len;

	len = 0;
	while (line[len] && !is_operator(line[len]))
	{
		if (line[len] && line[len] == '"')
		{
			len++;
			while (line[len] && line[len] != '"')
				len++;
		}
		else if (line[len] && line[len] == '\'')
		{
			len++;
			while (line[len] && line[len] != '\'')
				len++;
		}
		len++;
	}
	return (len);
}

static char	*ft_token_cmd(const char *line)
{
	int		i;
	int		len;
	char	*str;
	char	*trim;

	i = 0;
	len = ft_quote_count(line);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = 0;
	trim = ft_strtrim(str, " ");
	free(str);
	if (!trim)
		return (NULL);
	return (trim);
}

char	*is_something(const char *line, int *i)
{
	char	*result;

	if (line[*i] && is_operator(line[*i]))
	{
		result = ft_token_op(line);
		if (result)
			return (NULL);
		if (line[*i] == '(' || line[*i] == ')')
			(*i)++;
		else
		{
			while (line[*i] && is_operator(line[*i]))
				(*i)++;
		}
	}
	else if (line[*i] && !is_operator(line[*i]))
	{
		result = ft_token_cmd(line);
		if (result)
			return (NULL);
		(*i) = get_index(line, *i);
	}
	return (result);
}

char	**ft_tokenize(const char *line)
{
	int		count;
	int		i;
	char	**shell;

	count = 0;
	i = 0;
	shell = (char **)ft_calloc(ft_token_count(line) + 1, sizeof(char *));
	if (!shell)
		return (NULL);
	while (line[i])
	{
		shell[count] = is_something(line, &i);
		if (!shell[count])
			return (clear_double(shell), NULL);
		count++;
		while (line[i] && is_space(line[i]))
			i++;
	}
	shell[count] = 0;
	return (shell);
}
