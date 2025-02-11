/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:31:16 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/11 14:34:31 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

//A test apres parsing
void	ft_cd(char **cmd)
{
	if (cmd[2])
	{
		ft_putstr_fd("cd: string not in pwd: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], 2);
		write(2, "\n", 1);
		exit(0);
	}
	else if (chdir(cmd[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], 2);
		write(2, "\n", 1);
		exit(1);
	}
}
