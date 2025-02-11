/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:33:04 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/11 14:12:42 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int	unset(char *arg, char **envp)
{
	char	*temp;
	int		i;

	if (!arg || !envp)
		return (1);
	i = 0;
	temp = ft_strjoin(arg, "=");
	if (!temp)
		return (1);
	while (envp[i] && ft_strncmp(temp, envp[i], ft_strlen(temp)) != 0)
		i++;
	if (!envp[i])
		return (free(temp), 1);
	free(envp[i]);
	while (envp[i + 1])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	return (free(temp), 0);
}

void	ft_unset(char **cmd, char **envp)
{
	int	i;

	if (!cmd[1])
	{
		ft_printf("unset: not enough arguments\n");
		exit(1);
	}
	i = 1;
	while (cmd[i])
	{
		if (unset(cmd[i], envp))
			exit(1);
		i++;
	}
	exit(0);
}
