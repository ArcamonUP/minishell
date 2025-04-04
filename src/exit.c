/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:42:21 by kbaridon          #+#    #+#             */
/*   Updated: 2025/04/02 13:52:25 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ft_is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	handle_str_case(char **tab)
{
	g_exit_status = 2;
	write(STDERR_FILENO, "exit\nminishell: exit: ", 22);
	write(STDERR_FILENO, tab[1], ft_strlen(tab[1]));
	write(STDERR_FILENO, ": numeric argument required\n", 29);
	return (free_tab(tab), 1);
}

int	handle_exit(char *line)
{
	char	**temp;

	temp = ft_split(line, ' ');
	free(line);
	if (!temp || !temp[0] || !temp[1])
	{
		g_exit_status = 1;
		if (temp && temp[0] && !temp[1])
			g_exit_status = 0;
		return (write(STDERR_FILENO, "exit\n", 5), free_tab(temp), 1);
	}
	if (temp[1] && ft_is_str_digit(temp[1]) && temp[2])
	{
		g_exit_status = 1;
		write(STDERR_FILENO, "exit\nminishell: exit: too many arguments\n", 41);
		return (free_tab(temp), 0);
	}
	if (temp[1] && ft_is_str_digit(temp[1]))
	{
		g_exit_status = ft_atoi(temp[1]);
		return (write(STDERR_FILENO, "exit\n", 5), free_tab(temp), 1);
	}
	return (handle_str_case(temp));
}
