/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:09:59 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/18 14:35:11 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"
#include "libft.h"

static int	count_words(const char *str, char sep)
{
	int	i;
	int	count;
	int	c;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
			count++;
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
		}
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

static int	pipex_word_len(const char *str, char sep)
{
	int	i;
	int	c;

	i = 0;
	if (str[i] == '"' || str[i] == '\'')
	{
		c = str[i++];
		while (str[i] && str[i] != c)
			i++;
		while (str[i] && str[i] != sep)
			i++;
		return (i - 2);
	}
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

static char	*get_word(const char *str, char sep, int *i)
{
	char	*result;
	int		len;
	int		j;
	int		c;

	len = pipex_word_len(&str[*i], sep);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	j = 0;
	if (str[*i] == '"' || str[*i] == '\'')
	{
		c = str[(*i)++];
		while (str[*i] && str[*i] != c)
			result[j++] = str[(*i)++];
		if (str[*i])
			(*i)++;
		while (str[*i] && str[*i] != sep)
			result[j++] = str[(*i)++];
		return (result);
	}
	while (str[*i] && str[*i] != sep)
		result[j++] = str[(*i)++];
	return (result);
}

static char	**get_tab(char **result, const char *str, char sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
		{
			result[j] = get_word(str, sep, &i);
			if (!result[j])
				return (free_tab(result), NULL);
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

char	**ft_pipex_split(char *str, char c)
{
	int		count;
	char	**result;

	count = count_words(str, c);
	result = ft_calloc(count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	return (get_tab(result, str, c));
}
