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
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

t_data	init(int ac, char **av, char **envp, char **line)
{
	t_data	data;

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
