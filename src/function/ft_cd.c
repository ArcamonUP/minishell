/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:31:16 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/28 10:49:23 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void	update_env(char **envp, char *arg, char *old_pwd, int i)
{
	char	*pwd;

	while (envp[i] && ft_strncmp("PWD=", envp[i], 4) != 0)
		i++;
	if (!envp[i])
		return ;
	free(envp[i]);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("chdir: error retrieving current directo", STDERR_FILENO);
		ft_putstr_fd("ry: getcwd: cannot access parent ", STDERR_FILENO);
		ft_putstr_fd("directories: No such file or directory\n", STDERR_FILENO);
		pwd = ft_strdup(arg);
	}
	envp[i] = ft_strjoin("PWD=", pwd);
	free(pwd);
	i = 0;
	while (envp[i] && ft_strncmp("OLDPWD=", envp[i], 7) != 0)
		i++;
	if (!envp[i])
		return ;
	free(envp[i]);
	envp[i] = ft_strjoin("OLDPWD=", old_pwd);
}

void	print_error(char *arg)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	else if (errno == ENOTDIR)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	}
}

int	ft_cd(char *line, char **envp)
{
	char	**cmd;
	char	*old_pwd;

	cmd = ft_divise(line, envp, 0);
	if (!cmd)
		return (127);
	if (cmd[1])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (free_tab(cmd), 1);
	}
	if (chdir(cmd[0]) == -1)
	{
		print_error(cmd[0]);
		return (free_tab(cmd), 1);
	}
	old_pwd = get_var("PWD", envp);
	update_env(envp, cmd[0], old_pwd, 0);
	return (free_tab(cmd), free(old_pwd), 0);
}
