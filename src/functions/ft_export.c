/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:32:20 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/06 11:59:18 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

//A faire
//export sans rien, et export avec des arguments
void	ft_export(char **line, char **envp)
{
	char	*result;
	int		i;

	i = 1;
	while (line[i])
	{
		//add les valeurs dans le truc export
		i++;
	}
	if (i == 1)
	{
		//on affiche ici toutes les variables deja exportees
		return ;
	}	
	return ;
}
