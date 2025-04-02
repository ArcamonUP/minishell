/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:36:32 by achu              #+#    #+#             */
/*   Updated: 2025/03/19 15:00:20 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int	ft_pwd(char **envp)
{
	char	*buf;
	char	*pwd;

	buf = NULL;
	pwd = get_var("PWD", envp);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	write(1, "\n", STDOUT_FILENO);
	free(pwd);
	free(buf);
	return (0);
}
