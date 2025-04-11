/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:36:32 by achu              #+#    #+#             */
/*   Updated: 2025/03/19 15:00:20 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_pwd(void)
{
	char	*buf;
	char	*pwd;

	buf = NULL;
	pwd = getcwd(buf, 0);
	if (!pwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory:", STDERR_FILENO);
		ft_putstr_fd(" getcwd: cannot access parent ", STDERR_FILENO);
		ft_putstr_fd("directories: No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	write(1, "\n", STDOUT_FILENO);
	free(pwd);
	return (0);
}
