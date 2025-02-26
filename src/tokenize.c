/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:41:17 by achu              #+#    #+#             */
/*   Updated: 2025/02/19 16:31:14 by achu             ###   ########.fr       */
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

static char	*ft_token_file(const char *line)
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
	char	**shell;

	count = 0;
	i = 0;
	shell = (char **)ft_calloc(ft_token_count(line) + 1, sizeof(char *));
	if (!shell)
		return (NULL);
	while (*line)
	{
		if (*line && is_operator(*line))
		{
			shell[count] = ft_token_op(line);
			if (!shell[count])
				return (clear_double(shell), NULL);
			count++;
			if (*line == '(' || *line == ')')
				line++;
			else
			{
				while (*line && is_operator(*line))
					line++;
			}
			if (*line && is_redir(shell[count - 1]))
			{
				while (*line && is_space(*line))
					line++;
				if (*line)
				{
					shell[count] = ft_token_file(line);
					if (!shell[count])
						return (clear_double(shell), NULL);
					count++;
				}
				while (*line && !is_space(*line))
					line++;
			}
		}
		else if (*line && !is_operator(*line))
		{
			shell[count] = ft_token_cmd(line);
			if (!shell[count])
				return (clear_double(shell), NULL);
			count++;
			while (*line && !is_operator(*line))
			{
				if (*line && *line == '"')
				{
					line++;
					while (*line && *line != '"')
						line++;
				}
				else if (*line && *line == '\'')
				{
					line++;
					while (*line && *line != '\'')
						line++;
				}
				line++;
			}
		}
		while (*line && is_space(*line))
			line++;
	}
	shell[count] = 0;
	return (shell);
}
