/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:23:56 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/20 13:50:55 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>

typedef struct t_pipex_data
{
	char	*infile;
	char	*limiter;
	char	*outfile;
	char	**cmd;
	char	**envp;
	pid_t	*pid_tab;
	int		fd[2];
}	t_pipex_data;

//init
t_pipex_data	init_pipex(t_node node, char **envp);
int				get_fd_file(t_node node, char c, int bonus);

//pipex
int				exec_bonus(t_pipex_data data);
char			*get_path(char *cmd, char **envp);

//utils
void			error(char *msg, char *other);
void			end(t_pipex_data data, int i);
void			dispatch_pipex(char *line, t_pipex_data data, int fd[2]);

void			wait_children(t_pipex_data data, pid_t p);

//basics
int				ft_tablen(char **tab);
void			free_tab(char **tab);

#endif
