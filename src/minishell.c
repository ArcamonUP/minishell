/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:14 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/18 11:51:00 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>

char	*check_and_parse(char *line)
{
	char	*result;
	char	**tokens;

	tokens = ft_tokenize(line);
	if (!tokens)
		return (free(line), NULL);
	result = checker(tokens);
	free_tab(tokens);
	if (!result)
		return (free(line), NULL);
	if (ft_strncmp(result, "0x20200487515969614000", 23) != 0)
		return (free(line), check_and_parse(result));
	return (line);
}

int	routine(t_shell data, char *line)
{
	t_node	*tree;
	char	**temp;

	if (line)
		free(line);
	line = readline("\033[37mminishell$ ");
	if (!line || ft_strncmp(line, "exit\0", 5) == 0)
		return (free(line), write(1, "exit\n", 5), 1);
	line = check_and_parse(line);
	if (!line)
		return (1);
	temp = ft_tokenize(line);
	if (!temp)
		return (1);
	tree = ft_parse_shell(temp);
	ft_init_fdio(&data, tree);
	ft_execute_tree(tree, &data, -1);
	add_history(line);
	free(line);
	free_node(tree);
	free_tab(temp);
	return (0);
}

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	data;
	int		i;
	char	*line;

	((void)ac, (void)av);
	i = 0;
	data = init(ac, av, envp, &line);
	if (!data.envp)
		return (1);
	while (1)
	{
		if (routine(data, line))
			break ;
	}
	if (line)
		free(line);
	rl_clear_history();
	exit(g_exit_status);
}
