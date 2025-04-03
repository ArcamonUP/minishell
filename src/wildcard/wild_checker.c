/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:46:57 by achu              #+#    #+#             */
/*   Updated: 2025/04/03 14:01:59 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Calculate the len of string after an asterisk
static int	ft_strstrlen(char *str, char *find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (find[j] && str[i + j] != '\0' && str[i + j] == find[j])
			j++;
		if (!find[j])
			return (i + j);
		i++;
	}
	return (-1);
}

// Proceed if this is the last asterisk and the next one is the last word
static int	is_last(char *str, char *token)
{
	size_t	len;
	size_t	tokenlen;

	len = ft_strlen(str);
	tokenlen = ft_strlen(token);
	if (len < tokenlen)
		return (0);
	if (ft_strncmp(str + len - tokenlen, token, len) != 0)
		return (0);
	return (1);
}

int	is_wildcard(char *str, char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i])
	{
		if ((unsigned char)tokens[i][0] == 0xFF)
		{
			if (!tokens[i + 1])
				return (1);
			if (!tokens[i + 2])
				return (is_last(str, tokens[i + 1]));
			if (ft_strstrlen(str, tokens[i + 1]) < 0)
				return (0);
			str += ft_strstrlen(str, tokens[i + 1]);
			i++;
		}
		else
		{
			if (ft_strncmp(str, tokens[i], ft_strlen(tokens[i])) != 0)
				return (0);
			str += ft_strlen(tokens[i]);
		}
		i++;
	}
	return (*str == '\0');
}
