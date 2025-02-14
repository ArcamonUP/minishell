/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:48:44 by achu              #+#    #+#             */
/*   Updated: 2025/02/14 14:22:36 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] && is_operator(line[i]))
		{
			if (line[i] == '(' || line[i] == ')')
				i++;
			else
			{
				while (line[i] && is_operator(line[i]))
					i++;
			}
		}
		else if (line[i] && !is_operator(line[i]))
			i = get_index(line, i);
		count++;
		while (line[i] && is_space(line[i]))
			i++;
	}
	return (count);
}

int	get_index(const char *line, int i)
{
	while (line[i] && !is_operator(line[i]))
	{
		if (line[i] && line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
		}
		else if (line[i] && line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		i++;
	}
	return (i);
}
