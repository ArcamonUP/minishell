/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:36:32 by achu              #+#    #+#             */
/*   Updated: 2025/02/03 17:55:46 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void    ft_pwd(void)
{
    char    *buf;
    char    *pwd;

    buf = NULL;
    pwd = getcwd(buf, 42);
    ft_printf("%s\n", pwd);
    free(pwd);
    free(buf);
}
