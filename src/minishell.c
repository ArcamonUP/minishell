/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:14 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/03 15:39:53 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>

void	dispatch(char *line, t_data data)
{
	__pid_t	p;

	if (ft_strncmp(line, "echo -n", 7) == 0)
		ft_echo(line);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(line, "cd", 2) == 0)
		ft_cd(line, data);
	else if (ft_strncmp(line, "export", 6) == 0)
		ft_export(line, data);
	else if (ft_strncmp(line, "unset", 5) == 0)
		ft_unset(line, data);
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_env(data);
	else
	{
		p = ft_exec(line, data);
		waitpid(p, NULL, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*line;

	((void)ac, (void)av);
	data.envp = envp;
	if (!data.envp)
		return (1);
	line = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (line)
			free(line);
		line = readline("minishell$ ");
		if (!line || ft_strncmp(line, "exit", 0) == 0)
			break ;
		add_history(line);
		dispatch(line, data);
	}
	free(line);
	rl_clear_history();
	return (exit(0), 0);
}
