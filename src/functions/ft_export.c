/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:32:20 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/14 11:27:02 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	print_sorted_env(char **envp)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		ft_putstr_fd(envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

char	**add_env(char *arg, char **envp)
{
	int		i;
	char	**temp;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(arg, envp[i], ft_strlen(arg)) == 0)
		{
			free(envp[i]);
			envp[i] = ft_strdup(arg);
			return (envp);
		}
		i++;
	}
	temp = ft_calloc(i + 2, sizeof(char *));
	if (!temp)
		return (free(envp), NULL);
	i = 0;
	while (envp[i])
	{
		temp[i] = ft_strdup(envp[i]);
		free(envp[i++]);
	}
	temp[i] = ft_strdup(arg);
	return (free(envp), temp);
}

int	ft_export(char *line, char **envp)
{
	int		i;
	char	**cmd;

	cmd = ft_split(line, ' ');
	if (!cmd)
		return (127);
	if (!cmd[1])
		return (print_sorted_env(envp), free_tab(cmd), 0);
	i = 1;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
		{
			if (ft_strncmp(cmd[i], "_=", 2) == 0)
				i++;
			else
				envp = add_env(cmd[i], envp);
		}
		else
		{
			if (ft_strncmp(cmd[i], "_", 1) == 0)
				i++;
			else
				envp = add_env(ft_strjoin(cmd[i], "="), envp);
		}
		i++;
	}
	return (free_tab(cmd), 0);
}
