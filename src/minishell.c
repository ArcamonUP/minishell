/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:14 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/13 16:22:42 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>

void	ft_print_tree(t_node *tree, int depth);
t_node	*ft_parse_and_or(char ***token);
char	**ft_parse_env(char *envp[]);
char	**ft_parse_paths(char **env);
int		ft_count_hdoc(t_node *node);
void	ft_init_heredoc(t_node *tree, t_shell *data);

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
	char	*result;
	char	**tokens;

	tokens = ft_tokenize(line);
	if (!tokens)
		return (free(line), rl_clear_history(), exit(0), NULL);
	result = checker(tokens);
	free_tab(tokens);
	if (!result)
		return (ft_printf("\nCa fonctionne pas\n"), free(line), NULL);
	if (ft_strncmp(result, "ok\0", 3) != 0)
		return (check_and_parse(result));
	else
		return (line);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	data;
	int		i;
	char	*line;
	char	**tokens;

	((void)ac, (void)av);
	i = 0;
	data.envp = envp;
	while (1)
	{
		if (line)
			free(line);
		line = readline("\033[37mminishell$ ");
		if (!line || ft_strncmp(line, "exit", 0) == 0)
			break ;
		// line = check_and_parse(line);
		// if (!line)
		// 	break ;
		tokens = ft_tokenize(line);
		if (!tokens)
			return (free(line), rl_clear_history(), exit(0), 0);
	
		// for (size_t i = 0; tokens[i]; i++)
		// 	ft_printf("%s\n", tokens[i]);
		// ft_printf("-----------\n");
		data.heredoc_idx = 0;
		data.heredoc_count = 0;
		t_node *test = ft_parse_shell(tokens);
		data.heredoc_fd = (int *)ft_calloc(ft_count_hdoc(test) + 1, sizeof(int));
		if (!data.heredoc_fd)
			return (1);
		ft_init_heredoc(test, &data);
		int i = 0;
		ft_print_tree(test, i);
		ft_printf("----------------\n");
		//ft_execute_tree(test, &data);
		add_history(line);
		//dispatch(line, data.envp, 0);
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
