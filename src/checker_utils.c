/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:16:14 by kbaridon          #+#    #+#             */
/*   Updated: 2025/04/08 13:28:39 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	check_error_2(char *line, int ret)
{
	if (ret == RET_NOFILE)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(line, 2);
		return (ft_putstr_fd(": No such file or directory\n", 2), (void)ret);
	}
	else if (ret == RET_NOPERMISSIONS)
	{
		ft_putstr_fd("minishell: cannot open ", 2);
		ft_putstr_fd(line, 2);
		return (ft_putstr_fd(": Permission denied\n", 2), (void)ret);
	}
}

void	check_error(char *line, int ret)
{
	if (ret == RET_OPERATOR)
	{
		ft_putstr_fd("minishell: Syntax error: \"", 2);
		ft_putstr_fd(line, 2);
		return (ft_putstr_fd("\" unexpected\n", 2), (void)ret);
	}
	else if (ret == RET_PARENTHESIS)
	{
		ft_putstr_fd("minishell: Syntax error: \")\" unexpected\n", 2);
		return ;
	}
	else if (ret == RET_NOTIMPLEMENTED)
	{
		ft_putstr_fd("minishell: Feature \"", 2);
		ft_putstr_fd(line, 2);
		return (ft_putstr_fd("\" is not implemented\n", 2), (void)ret);
	}
	else if (ret == RET_NEWLINE)
	{
		ft_putstr_fd("minishell: Syntax error: newline unexpected\n", 2);
		return ;
	}
	else
		check_error_2(line, ret);
}

char	*handle_missings(char *to_parse)
{
	char	*line;
	char	*temp;

	line = readline("> ");
	if (!line)
		return (NULL);
	temp = ft_strjoin_char(to_parse, '\n');
	to_parse = temp;
	if (!to_parse)
		return (free(line), NULL);
	temp = ft_strjoin(to_parse, line);
	(free(to_parse), free(line));
	if (!temp)
		return (NULL);
	return (temp);
}

char	*missing_elements(char **line)
{
	char	*to_parse;
	char	*temp;
	int		i;

	to_parse = ft_strdup(line[0]);
	if (!to_parse)
		return (NULL);
	i = 1;
	while (line[i])
	{
		temp = ft_strjoin_char(to_parse, ' ');
		if (!temp)
			return (NULL);
		to_parse = ft_strjoin(temp, line[i]);
		free(temp);
		if (!to_parse)
			return (NULL);
		i++;
	}
	temp = handle_missings(to_parse);
	if (!temp)
		return (NULL);
	return (temp);
}

int	wait_next(char **line, int *i, int *y, char c)
{
	(*y)++;
	while (line[*i])
	{
		while (line[*i][*y] && line[*i][*y] != c)
			(*y)++;
		if (!line[*i][*y])
		{
			(*i)++;
			*y = 0;
		}
		else
			return (0);
	}
	return (1);
}
