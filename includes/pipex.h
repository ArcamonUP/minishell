/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:23:56 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/03 11:19:13 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>

typedef struct t_data
{
	char	**cmd;
	char	**envp;
	pid_t	*pid_tab;
	int		fd[2];
	int		ac;
}	t_data;

int		pipex_init(int ac, char **av, char ***cmd);

int		exec_bonus(t_data data);
char	*get_path(char *cmd, char **envp);

void	pipex_free(char **tab);
void	error(char *msg);
void	pipex_end(t_data data, int i);

void	wait_children(t_data data, pid_t p);

#endif
