/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:25:31 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/28 12:33:07 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "pipex.h"

char	**cp_tab(char **tab)
{
	char	**new_tab;
	int		i;

	i = 0;
	new_tab = ft_calloc(sizeof(char *), ft_tablen(tab) + 1);
	if (!new_tab)
		return (NULL);
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
			return (free_tab(new_tab), NULL);
		i++;
	}
	return (new_tab);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*dupcheck(char **env, int i, char *str)
{
	char	*temp;

	if (i > 0 && !env[i - 1])
		return (NULL);
	temp = ft_strdup(str);
	if (!temp)
		return (NULL);
	return (temp);
}

void	print_sorted_tab(char **tab)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strncmp(tab[i], tab[j], ft_strlen(tab[i])) > 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		ft_putstr_fd(tab[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcat(result, s2, len1 + len2 + 1);
	free(s1);
	free(s2);
	return (result);
}
