/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 02:00:52 by achu              #+#    #+#             */
/*   Updated: 2025/04/01 15:02:10 by achu             ###   ########.fr       */
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
		if (find[i] == '*')
			return (i);
		i++;
	}
	return (i);
}

static char	*get_token(char *find)
{
	char	*word;
	int		len;
	int		i;

	i = 0;
	if (*find == '*')
		return (ft_strdup("*"));
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
		if (*find && *find == '*')
			i++;
		while (*find && *find == '*')
			find++;
		if (*find && *find != '*')
			i++;
		while (*find && *find != '*')
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
		if (find && *find == '*')
			tokens[i++] = get_token(find);
		while (*find && *find == '*')
			find++;
		if (*find && *find != '*')
			tokens[i++] = get_token(find);
		while (*find && *find != '*')
			find++;
	}
	tokens[i] = 0;
	return (tokens);
}
