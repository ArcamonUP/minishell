/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:36:32 by achu              #+#    #+#             */
/*   Updated: 2025/02/11 14:35:21 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	ft_pwd(void)
{
	char	*buf;
	char	*pwd;

	buf = NULL;
	pwd = getcwd(buf, 42);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	write(1, "\n", STDOUT_FILENO);
	free(pwd);
	free(buf);
	exit(0);
}
