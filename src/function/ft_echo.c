/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:31:41 by kbaridon          #+#    #+#             */
/*   Updated: 2025/04/08 12:47:45 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int	get_c_value(char letter, int c)
{
	if (c == 0 && (letter == '\"' || letter == '\''))
		c = letter;
	else if (c == letter)
		c = 0;
	return (c);
}

int	ft_echo(char *line, char **envp)
{
	int		i;
	char	**cmd;

	cmd = ft_divise(line, envp, 0);
	if (!cmd || !cmd[0])
		return (127);
	i = 0;
	if (cmd[0] && ft_strncmp(cmd[0], "-n\0", 3) == 0)
		i = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!cmd[0] || ft_strncmp(cmd[0], "-n\0", 3) != 0)
		write(STDOUT_FILENO, "\n", 1);
	return (free_tab(cmd), 0);
}
