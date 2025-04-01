/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:46:05 by achu              #+#    #+#             */
/*   Updated: 2025/04/01 18:44:23 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// ""
// ''
// $
// *

static int	do_quote(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] && cmd[i] == '"')
	{
		i++;
		while (cmd[i] && cmd[i] != '"')
			i++;
		if (cmd[i] && cmd[i] == '"')
			i++;
	}
	else if (cmd[i] && cmd[i] == '\'')
	{
		i++;
		while (cmd[i] && cmd[i] != '\'')
			i++;
		if (cmd[i] && cmd[i] == '\'')
			i++;
	}
	return (i);
}

static int	cal_customlen(char *cmd)
{
	int	sum;

	sum = 0;
	while (*cmd)
	{
		sum++;
		while (*cmd && ft_isalnum(*cmd))
			cmd++;
		cmd += do_quote(cmd);
		while (*cmd && ft_isspace(*cmd))
			cmd++;
	}
	return (sum);
}

void	ft_custom_split(char *cmd)
{
	ft_printf("len: %i\n", cal_customlen(cmd));
}