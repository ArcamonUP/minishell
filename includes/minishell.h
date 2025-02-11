/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:37 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/11 16:37:33 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include "pipex.h"

typedef struct t_data
{
	char	**envp;
	char	**shell;
}	t_data;

typedef enum
{
	SUB,
	PIPE,
	AND,
	OR,
	IN,
	OUT,
	APPEND,
	HERE_DOC,
	CMD,
}	e_type;

typedef struct s_node
{
	e_type	type;
	char	*str;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

//init
t_data	init(int ac, char **av, char **envp, char **line);

//minishell
int		dispatch(char *line, char **envp, int i);
char	**ft_tokenize(const char *line);

//functions
void	ft_cd(char **line);
void	ft_echo(char **line);
void	ft_env(char **envp);
void	ft_export(char **line, char **envp);
void	ft_pwd(void);
void	ft_unset(char **line, char **envp);

//pipex
int		pipex(t_pipex_data data);

//utils
void	ctrl_c(int sig);
void	parent_ctrl_c(int sig);
__pid_t	ft_exec(char *cmd, char **envp);

#endif