/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:23:56 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/04 13:53:00 by kbaridon         ###   ########.fr       */
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

//pipex
int		exec_bonus(t_pipex_data data);
char	*get_path(char *cmd, char **envp);

//utils
void	error(char *msg, char *other);
void	end(t_pipex_data data, int i);

void	wait_children(t_pipex_data data, pid_t p);

//basics
int		ft_tablen(char **tab);
void	free_tab(char **tab);

#endif
