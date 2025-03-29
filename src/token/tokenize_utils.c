/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:48:44 by achu              #+#    #+#             */
/*   Updated: 2025/03/28 16:18:48 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

// Return True if the char is an operator symbol
int	is_operator(const char c)
{
	return (c == '<' || c == '>' || c == '|' || \
			c == '(' || c == ')' || c == '&');
}

int	is_redir(char *str)
{
	if (ft_strncmp(str, ">>\0", 3) == 0)
		return (1);
	else if (ft_strncmp(str, ">\0", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "<<\0", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "<\0", 2) == 0)
		return (1);
	return (0);
}

// Copy paste into another char* the src depends on len
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

int	incr_token(const char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (ft_strncmp(">", line + i, 1) == 0 || \
		ft_strncmp("<", line + i, 1) == 0)
			count++;
		if (is_operator(line[i]))
			get_operator(line, &i, 1);
		else
			get_cmd(line, &i, 1);
		count++;
		while (line[i] && ft_isspace(line[i]))
			i++;
	}
	return (count);
}
