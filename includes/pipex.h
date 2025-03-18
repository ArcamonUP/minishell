/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:23:56 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/18 12:11:48 by kbaridon         ###   ########.fr       */
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

//init
t_pipex_data	init_pipex(t_node *node, t_shell *shell_data);
int				get_fd_file(t_node *node, char *str, int bonus);

//pipex
int				exec_bonus(t_pipex_data data);
char			*get_path(char *cmd, char **envp);

//utils
void			error(char *msg, char *other);
void			end(t_pipex_data data, int i);
void			dispatch_pipex(char *line, t_pipex_data data, int fd[2]);
void			wait_children(t_pipex_data data, pid_t p);

//pipex_lib
char			**ft_pipex_split(char *str, char c);

//basics
int				ft_tablen(char **tab);
void			free_tab(char **tab);

#endif
