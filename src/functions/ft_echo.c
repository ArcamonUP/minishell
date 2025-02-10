/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:31:41 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/05 11:46:21 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_echo(char **line)
{
	int	i;

	if (ft_strncmp(line[1], "-n", 2) == 0)
	{
		i = 2;
		while (line[i])
		{
			ft_putstr_fd(line[i], 1);
			if (line[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
		return ;
	}
	i = 1;
	while (line[i])
	{
		//ft_printf("%s", line[i]);
		if (line[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	return ;
}
