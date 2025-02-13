/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:58:06 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/03 17:29:05 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void	clear_double(char **ptr);

char	**ft_parse_env(char *envp[])
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i], ':');
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	**ft_parse_paths(char **env)
{
	int		i;
	char	**sub;
	char	*temp;

	i = 0;
	sub = (char **)malloc((ft_strlen_dbl(env) + 1) * sizeof(char *));
	if (!sub)
		return (NULL);
	while (env[i])
	{
		sub[i] = ft_strjoin(env[i], "/");
		if (!sub[i])
			return (clear_double(sub), NULL);
		i++;
	}
	temp = ft_substr(sub[0], 5, ft_strlen(env[0]));
	if (!temp)
		return (clear_double(sub), NULL);
	free(sub[0]);
	sub[0] = temp;
	sub[i] = 0;
	return (sub);
}

t_shell	init(int ac, char **av, char **envp, char **line)
{
	t_shell	data;

	((void)ac, (void)av);
	data.envp = NULL;
	*line = NULL;
	rl_catch_signals = 0;
	if (signal(SIGINT, ctrl_c) == SIG_ERR || \
	signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("Signal failed");
		return (data);
	}
	if (getenv("PATH") == NULL)
	{
		perror("Envp missing");
		return (data);
	}
	data.envp = envp;
	return (data);
}
