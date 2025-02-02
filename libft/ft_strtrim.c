/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:36:26 by kbaridon          #+#    #+#             */
/*   Updated: 2024/11/06 20:18:12 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		i;
	int		y;
	int		x;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && is_set(set, s1[i]))
		i++;
	y = ft_strlen(s1) - 1;
	while (s1[y] && is_set(set, s1[y]) && y > i)
		y--;
	result = malloc(sizeof(char) * (y - i + 2));
	if (result == NULL)
		return (NULL);
	x = 0;
	while (i <= y)
	{
		result[x] = s1[i];
		x++;
		i++;
	}
	result[x] = '\0';
	return (result);
}
