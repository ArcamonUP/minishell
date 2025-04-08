/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:37 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/28 16:16:06 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>

//Exit status
extern int	g_exit_status;

typedef struct s_lstfd
{
	int				fd;
	int				visited;
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
	RET_OPERATOR,
	RET_NOTIMPLEMENTED,
	RET_NOFILE,
	RET_NOPERMISSIONS,
	RET_NEWLINE,
}	t_ret;

typedef enum e_way
{
	LEFT,
	RIGHT,
}	t_way;

typedef struct s_node
{
	t_type			type;
	char			*str;
	struct s_node	*left;
	struct s_node	*right;
	t_lstfd			*fdin;
	t_lstfd			*fdout;
}	t_node;

//ft_cd.c
int		ft_cd(char *line, char **envp);

//ft_divise.c
char	**ft_divise(char *line, char **envp, int y);

//ft_echo.c
int		get_c_value(char letter, int c);
int		ft_echo(char *line, char **envp);

//ft_env.c
int		ft_env(char **envp);

//ft_export.c
int		ft_export(char *line, char ***envp, int i);

//ft_pwd.c
int		ft_pwd(char **envp);

//ft_unset.c
int		ft_unset(char *line, char ***envp);

//basics.c
char	**cp_tab(char **tab);
int		ft_tablen(char **tab);
char	*dupcheck(char **env, int i, char *str);
void	print_sorted_tab(char **tab);
char	*ft_strjoin_free(char *s1, char *s2);

//checker_utils.c
void	check_error(char *line, int ret);
char	*handle_missings(char *to_parse);
char	*missing_elements(char **line);
int		wait_next(char **line, int *i, int *y, char c);

//checker.c
char	*checker(char **line);

//exit.c
int		handle_exit(char *line);

//exec_and_or.c
int		ft_exec_and(t_node *tree, t_shell *data, int fd);
int		ft_exec_or(t_node *tree, t_shell *data, int fd);

//exec_redir.c
int		ft_exec_heredoc(t_node *tree, t_shell *data, int pipe_fd);
int		ft_exec_input(t_node *tree, t_shell *data, int pipe_fd);
int		ft_exec_append(t_node *tree, t_shell *data, int pipe_fd);
int		ft_exec_trunc(t_node *tree, t_shell *data, int pipe_fd);

//exec.c
int		ft_execute_tree(t_node *node, t_shell *data, int fd);

//free.c
void	free_node(t_node *node);
void	free_tab(char **tab);
void	clear_double(char **ptr);
void	ft_tabnfree(char **tab, int i);

//get_tokenize.c
char	*get_redir(const char *line, int *i, int count);
char	*get_operator(const char *line, int *i, int count);
char	*get_cmd(const char *line, int *i, int count);

//init_redir.c
int	ft_init_fdio(t_shell *data, t_node *tree);

//init.c
t_shell	init(int ac, char **av, char **envp, char **line);

//split
char	**ft_argsplit(char *str, char **envp);

//parser
t_type	get_optype(char *str);
t_node	*ft_node_new(char *str, t_type type);
t_node	*ft_node_parent(char *str, t_node *left, t_node *right);
t_node	*ft_parse_shell(char **tokens);

//signals.c
void	ctrl_c(int sig);
void	parent_ctrl_c(int sig);
void	parent_ctrl_backslash(int sig);
void	ctrl_backslash(int sig);
void	ignore(int sig);

//tokenize_utils.c
int		is_operator(const char c);
char	*ft_strndup(char *src, int len);
int		incr_token(const char *line);

//tokenize.c
char	*ft_token_op(const char *line);
char	*ft_token_cmd(const char *line);
char	*ft_token_file(const char *line);
char	**ft_tokenize(const char *line);

// Wildcards
char	**get_file(char *find);

//utils_lstfd.c
t_lstfd	*ft_lstfd_new(int fd);
void	ft_lstfd_add_back(t_lstfd **alst, t_lstfd *new);
void	ft_lstfd_clear(t_lstfd **list);

//utils.c
char	*get_var(char *arg, char **envp);
char	*get_exec(char *cmd);
char	*get_path(char *cmd, char **envp);
void	pre_asterisk(char *str);
char	*ft_strjoin_char(char *str, char c);

//Argsplit
int		expand_realloc(char	***buffer, size_t size);
int		add_join(char **buffer, char *join, size_t *i, size_t *size);
int		add_schar(char **buffer, char **str, size_t *size, size_t *i);
char	*do_var(char **str, char **envp);
char	*do_dquote(char **str, char **envp);
char	*do_squote(char **str);

//Fancy
void	print_banner(void);

#endif