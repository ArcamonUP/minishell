/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:32:02 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/14 10:58:05 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

//Affiche l'environnement de l'utilisateur
int	ft_env(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			write(1, &envp[i][j], STDOUT_FILENO);
			j++;
		}
		write(1, "\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}
