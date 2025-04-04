/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 02:00:52 by achu              #+#    #+#             */
/*   Updated: 2025/04/03 13:49:28 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	cal_tokenlen(char *find)
{
	int	i;

	i = 0;
	while (find[i])
	{
		if ((unsigned char)find[i] == 0xFF)
			return (i);
		i++;
	}
	return (i);
}

static char	*get_token(char *find)
{
	char	*word;
	char	astk[2];
	int		len;
	int		i;

	i = 0;
	if (*find && (unsigned char)*find == 0xFF)
	{
		astk[0] = (char)0xFF;
		astk[1] = '\0';
		return (ft_strdup(astk));
	}
	len = cal_tokenlen(find);
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = find[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	cal_tokenslen(char *find)
{
	int	i;

	i = 0;
	while (*find)
	{
		if (*find && (unsigned char)*find == 0xFF)
			i++;
		while (*find && (unsigned char)*find == 0xFF)
			find++;
		if (*find && (unsigned char)*find != 0xFF)
			i++;
		while (*find && (unsigned char)*find != 0xFF)
			find++;
	}
	return (i);
}

// TODO: free double
char	**get_tokens(char *find)
{
	char	**tokens;
	int		len;
	int		i;

	i = 0;
	len = cal_tokenslen(find);
	tokens = (char **)malloc((len + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	while (*find)
	{
		if (find && (unsigned char)*find == 0xFF)
			tokens[i++] = get_token(find);
		while (*find && (unsigned char)*find == 0xFF)
			find++;
		if (*find && (unsigned char)*find != 0xFF)
			tokens[i++] = get_token(find);
		while (*find && (unsigned char)*find != 0xFF)
			find++;
	}
	tokens[i] = 0;
	return (tokens);
}
