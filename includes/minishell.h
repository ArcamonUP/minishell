/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:43:37 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/03 17:13:30 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>

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
char	**ft_token_shell(const char *line);

//functions
void	ft_cd(char *line, t_data data);
void	ft_echo(char *line);
void	ft_env(t_data data);
void	ft_export(char *line, t_data data);
void	ft_pwd(void);
void	ft_unset(char *line, t_data data);

//utils
void	ctrl_c(int sig);
__pid_t	ft_exec(char *cmd, t_data data);

#endif