/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:53:45 by kbaridon          #+#    #+#             */
/*   Updated: 2025/01/24 15:28:11 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *str, char sep)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
			result++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (result);
}

void	free_tab(char **tab, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
		free(tab[i++]);
	free(tab);
}

char	*get_word(const char *str, char sep)
{
	char	*result;
	int		i;
	int		count;

	count = 0;
	while (str[count] && str[count] != sep)
		count++;
	result = malloc(sizeof(char) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	**get_tab(char **result, const char *str, char sep)
{
	int	i;
	int	id;

	i = 0;
	id = 0;
	while (str[i])
	{
		if (str[i] == sep)
			i++;
		else
		{
			result[id] = get_word(str + i, sep);
			if (!result[id])
				return (free_tab(result, id), NULL);
			id++;
			while (str[i] && str[i] != sep)
				i++;
		}
	}
	result[id] = NULL;
	return (result);
}

char	**ft_split(const char *str, char c)
{
	char	**result;
	int		tmp;

	tmp = count_words(str, c);
	result = malloc(sizeof(char *) * (tmp + 1));
	if (!result)
		return (NULL);
	return (get_tab(result, str, c));
}
