/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:31:16 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/05 11:17:20 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

//A test apres parsing
void	ft_cd(char **line)
{
	if (line[2])
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putstr_fd(line[1], 2);
		write(2, "\n", 1);
	}
	else if (chdir(line[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(line[1], 2);
		write(2, "\n", 1);
	}
	return ;
}
