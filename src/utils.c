/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:49:10 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/19 14:41:52 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "^C\n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	parent_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

char	*get_path(char *cmd, char **envp)
{
	char	**path;
	char	*result;
	char	*temp;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path && path[i])
	{
		temp = ft_strjoin(path[i], "/");
		result = ft_strjoin(temp, cmd);
		free(temp);
		if (access(result, F_OK) == 0)
		{
			free_tab(path);
			return (result);
		}
		(free(result), i++);
	}
	return (free_tab(path), NULL);
}

void	ft_tabnfree(char **tab, int i)
{
	i++;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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
