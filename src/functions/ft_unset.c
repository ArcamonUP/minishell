/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:33:04 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/06 15:32:15 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//A faire
//unset sans rien, et unset avec des arguments
void	ft_unset(char **line, char **envp)
{
	int	i;

	if (!line[1])
	{
		ft_printf("unset: not enough arguments\n");
		return ;
	}
	i = 1;
	(void)envp;
	return ;
}
