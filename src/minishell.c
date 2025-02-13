/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:14 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/13 12:37:40 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>

void	ft_printtree(t_node *tree, int depth);
t_node	*ft_parse_and_or(char ***token);

int	dispatch(char *line, char **envp, int i)
{
	__pid_t	p;

	//ICI les ft_split sont temporaires, en attendant le parsing.
	if (ft_strncmp(line, "echo", 4) == 0)
		return (ft_echo(ft_split(line, ' '), envp), 1);
	if (ft_strncmp(line, "pwd", 3) == 0)
		return (ft_pwd(), 1);
	if (ft_strncmp(line, "cd", 2) == 0)
		return (ft_cd(ft_split(line, ' ')), 1);
	if (ft_strncmp(line, "export", 6) == 0)
		return (ft_export(ft_split(line, ' '), envp), 1);
	if (ft_strncmp(line, "unset", 5) == 0)
		return (ft_unset(ft_split(line, ' '), envp), 1);
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

char	*check_and_parse(char *line)
{
	t_data	data;
	char	*result;

	data.shell = ft_tokenize(line);
	if (!data.shell)
		return (free(line), rl_clear_history(), exit(0), NULL);
	result = checker(data.shell);
	if (!result)
		return (free(line), NULL);
	if (ft_strncmp(result, "0x20200487515969614000", 23) != 0)
		return (check_and_parse(result));
	return (free_tab(data.shell), line);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_node	*test;
	char	*line;

	data = init(ac, av, envp, &line);
	if (!data.envp)
		return (1);
	while (1)
	{
		if (line)
			free(line);
		line = readline("\033[37mminishell$ ");
		if (!line || ft_strncmp(line, "exit", 0) == 0)
			break ;
		line = check_and_parse(line);
		if (!line)
			break ;
		ft_printf("Output apres le checker : %s\n", line);
		ft_printf("-----\n");
		test = ft_parse_and_or(/*line | tokenize a faie dans la fonction*/);
		ft_printtree(test, 0);
		add_history(line);
		//dispatch(line, data.envp, 0);
	}
	if (line)
		free(line);
	if (data.shell)
		free_tab(data.shell);
	free_node(test);
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
