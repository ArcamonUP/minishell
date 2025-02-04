/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:14 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/04 15:58:38 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>

int	dispatch(char *line, char **envp, int i)
{
	__pid_t	p;

	if (ft_strncmp(line, "echo", 4) == 0)
		return (ft_echo(line), 1);
	if (ft_strncmp(line, "pwd", 3) == 0)
		return (ft_pwd(), 1);
	if (ft_strncmp(line, "cd", 2) == 0)
		return (ft_cd(line, envp), 1);
	if (ft_strncmp(line, "export", 6) == 0)
		return (ft_export(line, envp), 1);
	if (ft_strncmp(line, "unset", 5) == 0)
		return (ft_unset(line, envp), 1);
	if (ft_strncmp(line, "env", 3) == 0)
		return (ft_env(envp), 1);
	if (i == 0)
	{
		p = ft_exec(line, envp);
		waitpid(p, NULL, 0);
		signal(SIGINT, ctrl_c);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*line;

	data = init(ac, av, envp, &line);
	if (!data.envp)
		return (1);
	while (1)
	{
		if (line)
			free(line);
		line = readline("minishell$ ");
		if (!line || ft_strncmp(line, "exit", 0) == 0)
			break ;
		add_history(line);
		dispatch(line, data.envp, 0);
	}
	free(line);
	rl_clear_history();
	return (exit(0), 0);
}

/*
//Pour appeller pipex:
int	main(int ac, char **av, char **envp)
{
	t_pipex_data	data;

	(void)ac;
	(void)av;
	data.infile = "Makefile";
	data.outfile = "outfile";
	data.limiter = NULL;
	data.cmd = ft_split("env*ls", '*');
	data.envp = envp;
	pipex(data);
	return (0);
}
*/
