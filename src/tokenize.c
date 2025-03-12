/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:41:17 by achu              #+#    #+#             */
/*   Updated: 2025/03/12 11:18:32 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*ft_token_op(const char *line)
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
	str = ft_calloc((len + 1), sizeof(char));
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

char	*ft_token_cmd(const char *line)
{
	int		i;
	int		len;
	char	*str;
	char	*trim;

	i = 0;
	len = ft_quote_count(line);
	str = ft_calloc((len + 1), sizeof(char));
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

char	*ft_token_file(const char *line)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (line[len] && !is_space(line[len]))
		len++;
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

char	**ft_tokenize(const char *line)
{
	int		count;
	int		i;
	char	**tokens;

	count = 0;
	i = 0;
	tokens = ft_calloc(ft_token_count(line) + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		if (count > 0 && is_redir(tokens[count - 1]))
			tokens[count] = get_redir(line, &i, 0);
		else if (is_operator(line[i]))
			tokens[count] = get_operator(line, &i, 0);
		else
			tokens[count] = get_cmd(line, &i, 0);
		if (!tokens[count])
			return (clear_double(tokens), NULL);
		count++;
		while (line[i] && is_space(line[i]))
			i++;
	}
	tokens[count] = NULL;
	return (tokens);
}
