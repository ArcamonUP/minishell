/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:33:04 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/06 12:06:32 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//A faire
//unset sans rien, et unset avec des arguments
void	ft_unset(char **line, char **envp)
{
	int	i;

	if (!line[1])
		return (ft_printf("unset: not enough arguments\n"));
	i = 1;
	while (line[i])
	{
		//unset les valeurs line[i]
		i++;
	}
	return ;
}
