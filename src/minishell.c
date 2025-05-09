/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:14 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/28 18:22:42 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>

int	g_exit_status = 0;

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

t_node	*ft_parse_shell(char **tokens)
{
	t_node	*node;

	node = ft_parse_and_or(&tokens);
	if (!node)
		return (NULL);
	return (node);
}

void	free_current(t_shell *data, char *line, t_node *tree)
{
	if (line)
		free(line);
	if (data->tab)
		free_tab(data->tab);
	if (data->fdin)
		ft_lstfd_clear(&data->fdin);
	if (data->fdout)
		ft_lstfd_clear(&data->fdout);
	if (tree)
		free_node(tree);
}

int	routine(t_shell *data, char *line)
{
	t_node	*tree;

	if (line)
		free(line);
	line = readline("\001\033[37m\002minishell$ ");
	if (!line)
		return (free(line), write(1, "exit\n", 5), 1);
	if (empty_line(line))
		return (free(line), 0);
	if (ft_strncmp(line, "exit ", 5) == 0 || ft_strncmp(line, "exit\n", 5) == 0 \
		|| ft_strncmp(line, "exit\0", 5) == 0)
		return (handle_exit(line));
	line = check_and_parse(line);
	if (!line)
		return (0);
	data->tab = ft_tokenize(line);
	if (!data->tab)
		return (1);
	tree = ft_parse_shell(data->tab);
	if (ft_init_fdio(data, tree) == -1)
		return (free_current(data, line, tree), 0);
	g_exit_status = ft_execute_tree(tree, data, -1);
	add_history(line);
	return (free_current(data, line, tree), 0);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	data;
	char	*line;

	((void)ac, (void)av);
	data = init(ac, av, envp, &line);
	if (!data.envp)
		return (1);
	while (1)
	{
		if (routine(&data, line))
			break ;
	}
	if (line)
		free(line);
	if (data.envp)
		free_tab(data.envp);
	rl_clear_history();
	exit(g_exit_status);
}
