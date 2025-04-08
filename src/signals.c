/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:07:27 by kbaridon          #+#    #+#             */
/*   Updated: 2025/04/08 13:30:07 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ctrl_c(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "^C\n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	parent_ctrl_c(int sig)
{
	(void)sig;
	//write(1, "\n", 1);
	g_exit_status = 130;
}

void	parent_ctrl_backslash(int sig)
{
	(void)sig;
	write(1, "Quit (core dumped)\n", 19);
	g_exit_status = 131;
}

void	ctrl_backslash(int sig)
{
	(void)sig;
	write(1, "^\\", 2);
	g_exit_status = 131;
}

void	ignore(int sig)
{
	(void)sig;
}
