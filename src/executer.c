/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:40:53 by achu              #+#    #+#             */
/*   Updated: 2025/02/12 23:16:39 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_split_args(char *cmd)
{
	
}

static pid_t	ft_exec_cmd(t_node *node)
{
	pid_t	pid;
	char	**args;

	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		args = ft_split(cmd, ' ');
		if (args)
			path = get_path(args[0], envp);
		if (!args || !path)
		{
			//gestion d'erreurs avec free...
			exit(0);
		}
		execve(path, args, envp);
		//gestion d'erreurs avec free...
		exit(0);
	}
}

int	ft_traverse(t_node *node)
{
	if (!node)
		return ;
	if (node->type == CMD)
		return (ft_exec_cmd(node));
}