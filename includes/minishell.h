/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:37 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/10 16:15:45 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include "pipex.h"

# define RET_PARENTHESIS 1
# define RET_OPERATOR 2
# define RET_NOTIMPLEMENTED 3
# define RET_NOFILE 4
# define RET_NOPERMISSIONS 5
# define RET_NEWLINE 6

typedef struct t_data
{
	char	**envp;
	char	**shell;
}	t_data;

typedef enum e_type
{
	SUB,
	PIPE,
	AND,
	OR,
	CMD,
}	t_type;

typedef struct s_node
{
	t_type			type;
	char			*str;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

//init
t_data	init(int ac, char **av, char **envp, char **line);

//minishell
char	*check_and_parse(char *line);
int		dispatch(char *line, char **envp, int i);
char	**ft_token_shell(const char *line);

//checkers_utils
void	check_error(char *line, int ret);
char	*handle_missings(void);
char	*add_space(char *str);

//checker
char	*checker(char **line);

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