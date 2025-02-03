/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:14 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/03 12:22:16 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*line;

	((void)ac, (void)av);
	data.envp = envp;
	if (!data.envp)
		return (1);
	line = malloc(1);
	while (1)
	{
		free(line);
		line = readline(NULL);
		if (!line)
			return (1);
		if (ft_strncmp(line, "exit", 0) == 0)
			break ;
		ft_printf("salut\n");
	}
	free(line);
	return (0);
}
