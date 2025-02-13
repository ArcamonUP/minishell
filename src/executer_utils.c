/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:16:37 by achu              #+#    #+#             */
/*   Updated: 2025/02/13 04:36:56 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// int	ft_args_count(char *cmd)
// {
// 	int	count;

// 	count = 0;
// 	while (*cmd)
// 	{
// 		if (*cmd && *cmd == '"')
// 		{
// 			cmd++;
// 			count++;
// 			while (*cmd && *cmd != '"')
// 				cmd++;
// 			cmd++;
// 		}
// 		else if (*cmd && *cmd == '\'')
// 		{
// 			cmd++;
// 			count++;
// 			while (*cmd && *cmd != '\'')
// 				cmd++;
// 			cmd++;
// 		}
// 		else if (*cmd && *cmd != ' ')
// 		{
// 			count++;
// 			while (*cmd && *cmd != ' ')
// 				cmd++;
// 		}
// 		while (*cmd && *cmd == ' ')
// 			cmd++;
// 	}
// 	return (count);
// }