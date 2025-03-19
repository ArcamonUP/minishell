/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:37 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/19 15:00:29 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>

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

typedef enum e_type
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
}	t_type;

typedef enum e_ret
{
	RET_PARENTHESIS = 1,
	RET_OPERATOR = 2,
	RET_NOTIMPLEMENTED = 3,
	RET_NOFILE = 4,
	RET_NOPERMISSIONS = 5,
	RET_NEWLINE = 6,
}	t_ret;

typedef struct s_node
{
	t_type			type;
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
char	**ft_tokenize(const char *line);
t_node	*ft_parse_shell(char **token);

//executing tree
int		ft_execute_tree(t_node *node, t_shell *data, int fd);
int		ft_exec_and(t_node *tree, t_shell *data, int fd);
int		ft_exec_or(t_node *tree, t_shell *data, int fd);
int		ft_exec_heredoc(t_node *tree, t_shell *data, int pipe_fd);
int		ft_exec_input(t_node *tree, t_shell *data, int pipe_fd);
int		ft_exec_append(t_node *tree, t_shell *data, int pipe_fd);
int		ft_exec_trunc(t_node *tree, t_shell *data, int pipe_fd);

//checkers_utils
void	check_error(char *line, int ret);
char	*handle_missings(char *to_parse);
char	*add_char(char *str, char c);
int		wait_next(char **line, int *i, int *y, char c);

//checker
char	*checker(char **line);

//functions
int		ft_cd(char *line, char ***envp);
int		ft_echo(char *line, char **envp);
char	*get_var(char *arg, char **envp);
int		ft_env(char **envp);
int		ft_export(char *line, char ***envp);
int		ft_pwd(char **envp);
int		ft_unset(char *line, char ***envp);

//utils
void	ctrl_c(int sig);
void	parent_ctrl_c(int sig);
void	ft_tabnfree(char **tab, int i);
char	**cp_tab(char **tab);

//free
void	free_node(t_node *node);
void	free_tab(char **tab);
void	clear_double(char **ptr);

//tokenize
char	**ft_tokenize(const char *line);
char	*ft_token_op(const char *line);
char	*ft_token_cmd(const char *line);
char	*ft_token_file(const char *line);

//tokenize_utils
int		is_space(const char c);
int		is_operator(const char c);
char	*ft_strndup(char *src, int len);
int		ft_token_count(const char *line);

//get_tokenize
char	*get_redir(const char *line, int *i, int count);
char	*get_operator(const char *line, int *i, int count);
char	*get_cmd(const char *line, int *i, int count);

//utils
t_lstfd	*ft_lstfd_new(int fd);
void	ft_lstfd_add_back(t_lstfd **lst, t_lstfd *new);
void	ft_lstfd_clear(t_lstfd **lst);

//parser_utils
int		is_redir(char *str);
char	*get_path(char *cmd, char **envp);
void	ft_print_tree(t_node *tree, int depth);

//pipex
int		pipex(t_node *node, t_shell *shell_data);

/*
/!\
PRINTTREE A ENLEVER A LA FIN
/!\
*/

#endif