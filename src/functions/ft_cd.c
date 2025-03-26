/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:31:16 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/19 15:08:45 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			ft_putstr_fd(envp[i], STDOUT_FILENO);
			write(1, "\n", 1);
		}
		else if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			ft_putstr_fd(envp[i], STDOUT_FILENO);
			write(1, "\n", 1);
		}
		i++;
	}
	write(1, "---------\n", 10);
}

void	update_env(char ***envp, char *old_pwd)
{
	char	*pwd;
	int		i;

	i = 0;
	while ((*envp)[i] && ft_strncmp("PWD=", (*envp)[i], 4) != 0)
		i++;
	if (!(*envp)[i])
		return ;
	free((*envp)[i]);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	(*envp)[i] = ft_strjoin("PWD=", pwd);
	free(pwd);
	i = 0;
	while ((*envp)[i] && ft_strncmp("OLDPWD=", (*envp)[i], 7) != 0)
		i++;
	if (!(*envp)[i])
		return ;
	free((*envp)[i]);
	(*envp)[i] = ft_strjoin("OLDPWD=", old_pwd);
}

int	ft_cd(char *line, char ***envp)
{
	char	**cmd;
	char	*old_pwd;

	cmd = ft_split(line, ' ');
	if (!cmd)
		return (127);
	print_env(*envp);
	old_pwd = get_var("PWD", *envp);
	if (cmd[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (free_tab(cmd), 1);
	}
	else if (chdir(cmd[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (free_tab(cmd), 1);
	}
	update_env(envp, old_pwd);
	print_env(*envp);
	return (free_tab(cmd), 0);
}
