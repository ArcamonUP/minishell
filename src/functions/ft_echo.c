/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:31:41 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/14 11:26:35 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

char	*get_var(char *arg, char **envp)
{
	char	*result;
	char	*temp;
	int		i;

	temp = ft_strjoin(arg, "=");
	if (!temp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(temp, envp[i], ft_strlen(temp)) == 0)
		{
			result = ft_strdup(envp[i] + ft_strlen(temp));
			free(temp);
			return (result);
		}
	}
	return (NULL);
}

int	ft_echo(char *line, char **envp)
{
	int		i;
	char	*temp;
	char	**cmd;

	cmd = ft_split(line, ' ');
	if (!cmd)
		return (127);
	i = 1;
	if (ft_strncmp(cmd[1], "-n", 2) == 0)
		i = 2;
	while (cmd[i])
	{
		if (cmd[i][0] == '$')
		{
			temp = get_var(cmd[i] + 1, envp);
			if (temp)
				ft_putstr_fd(temp, STDOUT_FILENO);
		}
		else
			ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[i + 1])
			write(1, " ", STDOUT_FILENO);
		i++;
	}
	if (ft_strncmp(cmd[1], "-n", 2) != 0)
		write(1, "\n", STDOUT_FILENO);
	return (free_tab(cmd), 0);
}
