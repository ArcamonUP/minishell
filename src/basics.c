/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:25:31 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/26 11:54:12 by kbaridon         ###   ########.fr       */
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
