/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:48:44 by achu              #+#    #+#             */
/*   Updated: 2025/03/12 11:18:55 by kbaridon         ###   ########.fr       */
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
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_operator(line[i]))
			get_operator(line, &i, 1);
		else
			get_cmd(line, &i, 1);
		count++;
		while (line[i] && is_space(line[i]))
			i++;
	}
	return (count);
}
