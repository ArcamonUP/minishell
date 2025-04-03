/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:33:04 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/28 14:30:20 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int	get_env_size(char **cmd, char ***envp)
{
	int		i;
	int		size;
	char	*temp;

	size = 0;
	i = 0;
	while ((*envp)[i++])
		size++;
	i = 1;
	while (cmd[i])
	{
		temp = get_var(cmd[i], *envp);
		if (temp)
		{
			free(temp);
			size--;
		}
		i++;
	}
	return (size);
}

void	unset(char **cmd, char ***result, char **envp)
{
	int	i;
	int	y;
	int	c;

	i = 0;
	c = 0;
	while (envp[i])
	{
		y = 1;
		while (cmd[y])
		{
			if (ft_strncmp(envp[i], cmd[y], ft_strlen(cmd[y])) == 0)
				break ;
			y++;
		}
		if (!cmd[y])
			(*result)[c++] = ft_strdup(envp[i]);
		i++;
	}
}

int	ft_unset(char *line, char ***envp)
{
	int		size;
	char	**cmd;
	char	**result;

	cmd = ft_split(line, ' ');
	if (!cmd)
		return (127);
	size = get_env_size(cmd, envp);
	result = ft_calloc(sizeof(char *), size + 1);
	if (!result)
		return (free_tab(cmd), 127);
	unset(cmd, &result, *envp);
	free_tab(*envp);
	*envp = result;
	return (free_tab(cmd), 0);
}
