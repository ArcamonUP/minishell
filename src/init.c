/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:58:06 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/19 13:38:18 by kbaridon         ###   ########.fr       */
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

char	**create_env(void)
{
	char	**env;
	char	cwd[1024];

	env = ft_calloc(7, sizeof(char *));
	if (!env)
		return (NULL);
	env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	if (!env[0])
		return (free_tab(env), NULL);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		env[1] = ft_strjoin("PWD=", cwd);
	else
		env[1] = ft_strdup("PWD=/");
	if (!env[1])
		return (free_tab(env), NULL);
	env[2] = ft_strdup("SHLVL=1");
	if (!env[2])
		return (free_tab(env), NULL);
	env[3] = ft_strdup("_=/usr/bin/env");
	if (!env[3])
		return (free_tab(env), NULL);
	env[4] = ft_strdup("TERM=xterm-256color");
	if (!env[4])
		return (free_tab(env), NULL);
	env[5] = ft_strdup("OLDPWD=");
	if (!env[5])
		return (free_tab(env), NULL);
	return (env);
}

t_shell	init(int ac, char **av, char **envp, char **line)
{
	t_shell	data;

	((void)ac, (void)av);
	data.envp = NULL;
	rl_catch_signals = 0;
	if (signal(SIGINT, ctrl_c) == SIG_ERR || \
	signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("Signal failed");
		return (data);
	}
	data.fdin = NULL;
	*line = NULL;
	data.fdout = NULL;
	data.envp = envp;
	if (!data.envp || !data.envp[0])
		data.envp = create_env();
	return (data);
}
