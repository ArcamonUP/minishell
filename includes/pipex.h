/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:23:56 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/03 11:50:13 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>

typedef struct t_pipex_data
{
	char	**cmd;
	char	**envp;
	pid_t	*pid_tab;
	int		fd[2];
	int		ac;
}	t_pipex_data;

typedef struct t_pipe
{
	char	*infile;
	char	*outfile;
	char	**cmd;
	char	**envp;
	int		ac;
}	t_pipe;

int		pipex_init(int ac, t_pipe pipe, char ***cmd);

int		exec_bonus(t_pipex_data data);
char	*get_path(char *cmd, char **envp);

void	pipex_free(char **tab);
void	error(char *msg);
void	pipex_end(t_pipex_data data, int i);

void	wait_children(t_pipex_data data, pid_t p);

#endif
