/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:31:41 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/18 11:16:40 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int	ft_echo(char *line, char **envp)
{
	int		i;
	char	*temp;
	char	**cmd;

	(void)envp;
	cmd = ft_split(line, ' ');
	if (!cmd)
		return (127);
	i = 1;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 2) == 0)
		i = 2;
	while (cmd[i])
	{
		if (cmd[i][0] == '$')
		{
			temp = getenv(cmd[i] + 1);
			if (temp)
				(ft_putstr_fd(temp, STDOUT_FILENO), free(temp));
		}
		else
			ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[i + 1])
			write(1, " ", STDOUT_FILENO);
		i++;
	}
	if (!cmd[1] || ft_strncmp(cmd[1], "-n", 2) != 0)
		write(1, "\n", STDOUT_FILENO);
	return (free_tab(cmd), 0);
}
