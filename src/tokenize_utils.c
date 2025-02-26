/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:48:44 by achu              #+#    #+#             */
/*   Updated: 2025/02/19 16:28:09 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int	is_space(const char c)
{
	return (c == '\n' || c == '\t' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ');
}

int	is_operator(const char c)
{
	return (c == '<' || c == '>' || c == '|' || \
			c == '(' || c == ')' || c == '&');
}

char	*ft_strndup(char *src, int len)
{
	int		i;
	char	*dest;

	i = 0;
	if (len < 0)
		return (NULL);
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_token_count(const char *line)
{
	int		count;
	char	op;

	count = 0;
	while (*line)
	{
		if (*line && is_operator(*line))
		{
			op = *line;
			count++;
			if (ft_strncmp("(", line, 1) == 0 || ft_strncmp(")", line, 1) == 0)
				line++;
			else
			{
				while (*line && is_operator(*line))
					line++;
			}
			if (*line && (op == '<' || op == '>'))
			{
				while (*line && is_space(*line))
					line++;
				if (*line)
					count++;
				while (*line && !is_space(*line))
					line++;
			}
		}
		else if (*line && !is_operator(*line))
		{
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
	return (count);
}
