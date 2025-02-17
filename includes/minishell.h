/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:37 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/13 16:55:26 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "pipex.h"

# define RET_PARENTHESIS 1
# define RET_OPERATOR 2
# define RET_NOTIMPLEMENTED 3
# define RET_NOFILE 4
# define RET_NOPERMISSIONS 5
# define RET_NEWLINE 6

typedef struct s_shell
{
	char	**envp;
	int		heredoc_idx;
	int		heredoc_count;
	int		*heredoc_fd;
}	t_shell;

typedef enum
{
	PIPE,
	AND,
	OR,
	INPUT,
	TRUNC,
	APPEND,
	HEREDOC,
	FILENAME,
	CMD,
}	e_type;

typedef struct s_node
{
	e_type			type;
	char			*str;
	int				is_hdoc;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

//init
t_shell	init(int ac, char **av, char **envp, char **line);

//minishell
char	*check_and_parse(char *line);
int		dispatch(char *line, char **envp, int i);
char	**ft_tokenize(const char *line);
t_node	*ft_parse_shell(char **token);

//executing tree
int		ft_execute_tree(t_node *node, t_shell *data);
int		ft_exec_and(t_node *node, t_shell *data);
int		ft_exec_or(t_node *node, t_shell *data);
int		ft_exec_heredoc(t_node *node, t_shell *data);
int		ft_exec_input(t_node *node, t_shell *data);
int		ft_exec_trunc(t_node *node, t_shell *data);
int		ft_exec_append(t_node *node, t_shell *data);

//checkers_utils
void	check_error(char *line, int ret);
char	*handle_missings(void);
char	*add_space(char *str);

//checker
char	*checker(char **line);

//functions
void	ft_cd(char **cmd);
void	ft_echo(char **cmd, char **envp);
void	ft_env(char **envp);
void	ft_export(char **cmd, char **envp);
void	ft_pwd(void);
void	ft_unset(char **cmd, char **envp);

//pipex
int		pipex(t_pipex_data data);

//utils
void	ctrl_c(int sig);
void	parent_ctrl_c(int sig);
__pid_t	ft_exec(char *cmd, char **envp);

#endif