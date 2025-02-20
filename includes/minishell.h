/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:37 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/19 16:02:40 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "pipex.h"



typedef struct s_lstfd
{
	int				fd;
	struct s_lstfd	*next;
}	t_lstfd;

typedef struct s_shell
{
	char	**envp;
	t_lstfd	*fdin;
	t_lstfd	*fdout;
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

typedef enum e_ret
{
	RET_PARENTHESIS = 1,
	RET_OPERATOR = 2,
	RET_NOTIMPLEMENTED = 3,
	RET_NOFILE = 4,
	RET_NOPERMISSIONS = 5,
	RET_NEWLINE = 6,
}	t_ret;

typedef struct t_data
{
	char	**envp;
	char	**shell;
}	t_data;

typedef struct s_node
{
	e_type			type;
	char			*str;
	struct s_node	*left;
	struct s_node	*right;
	int				fdin;
	int				fdout;
}	t_node;

//init
t_shell	init(int ac, char **av, char **envp, char **line);
void	ft_init_fdio(t_shell *data, t_node *tree);

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
int		ft_exec_append(t_node *node, t_shell *data);
int		ft_exec_trunc(t_node *node, t_shell *data);

//checkers_utils
void	check_error(char *line, int ret);
char	*handle_missings(char *to_parse);
char	*add_char(char *str, char c);
int		wait_next(char **line, int *i, int *y, char c);

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

//free
void	free_node(t_node *node);
void	free_tab(char **tab);
void	clear_double(char **ptr);

//tokenize
char	**ft_tokenize(const char *line);

//tokenize_utils
int		is_space(const char c);
int		is_operator(const char c);
char	*ft_strndup(char *src, int len);
int		ft_token_count(const char *line);
int		get_index(const char *line, int i);

//parser
t_node	*ft_parse_and_or(char ***token);

//parser_utils
t_type	ft_opcmp(char *str);
int		is_redir(char *str);
t_node	*ft_node_new(char *str, t_type type);
void	ft_printtree(t_node *tree, int depth);

/*
/!\
PRINTTREE A ENLEVER A LA FIN
/!\
*/

#endif