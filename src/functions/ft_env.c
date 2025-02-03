/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:32:02 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/03 16:20:10 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

//Affiche l'environnement de l'utilisateur
void	ft_env(t_data data)
{
	int	i;
	int	j;

	i = 0;
	while (data.envp[i])
	{
		j = 0;
		while (data.envp[i][j])
		{
			write(1, &data.envp[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	return ;
}
