/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:33:04 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/14 11:27:24 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	unset(char *arg, char **envp)
{
	char	*temp;
	int		i;

	if (!arg || !envp)
		return ;
	i = 0;
	temp = ft_strjoin(arg, "=");
	if (!temp)
		return ;
	while (envp[i] && ft_strncmp(temp, envp[i], ft_strlen(temp)) != 0)
		i++;
	if (!envp[i])
		return (free(temp), (void)0);
	free(envp[i]);
	while (envp[i + 1])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	return (free(temp), (void)0);
}

int	ft_unset(char *line, char **envp)
{
	int		i;
	char	**cmd;

	cmd = ft_split(line, ' ');
	if (!cmd)
		return (127);
	i = 1;
	while (cmd[i])
	{
		unset(cmd[i], envp);
		i++;
	}
	return (free_tab(cmd), 0);
}
