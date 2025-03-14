/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:31:16 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/14 11:26:18 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int	ft_cd(char *line)
{
	char	**cmd;

	cmd = ft_split(line, ' ');
	if (!cmd)
		return (127);
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
	return (free_tab(cmd), 0);
}
