/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:23:56 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/26 12:28:04 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"
# include <sys/types.h>

typedef struct t_pipex_data
{
	char	**cmd;
	char	**envp;
	pid_t	*pid_tab;
	int		fd[2];
	int		s_stdout;
	int		s_stdin;
}	t_pipex_data;

//pipex_init.c
t_pipex_data	init_pipex(t_node *node, t_shell *shell_data);

//pipex_lib.c
char			**ft_pipex_split(char *str, char c);

//pipex_utils.c
void			error(char *msg, char *other);
void			end(t_pipex_data data, int i);
void			wait_children(t_pipex_data data, pid_t p);
void			dispatch_pipex(char *line, t_pipex_data data, int fd[2]);

//pipex.c
int				pipex(t_node *node, t_shell *shell_data);

#endif
