/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:21:13 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/10 16:21:45 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	check_redirection(char **line, int i)
{
	if (ft_strncmp(line[i], "<\0", 2) == 0 || ft_strncmp(line[i], ">\0", 2) == 0 \
	|| ft_strncmp(line[i], ">>\0", 3) == 0)
	{
		if (!line[i + 1])
			return (check_error(line[i], RET_NEWLINE), 1);
		if (access(line[i + 1], F_OK) == -1)
			return (check_error(line[i + 1], RET_NOFILE), 1);
		if (ft_strncmp(line[i], "<", 1) == 0 && access(line[i + 1], R_OK) == -1)
			return (check_error(line[i + 1], RET_NOPERMISSIONS), 1);
		if (ft_strncmp(line[i], ">", 1) == 0 && access(line[i + 1], W_OK) == -1)
			return (check_error(line[i + 1], RET_NOPERMISSIONS), 1);
	}
	if (ft_strncmp(line[i], "<<\0", 3) == 0)
	{
		if (!line[i + 1])
			return (check_error(line[i], RET_NEWLINE), 1);
	}
	return (0);
}

int	check_possible(char **line, int *parenthesis, int i)
{
	if (ft_strncmp(line[i], "(\0", 3) == 0)
	{
		(*parenthesis)++;
		return (0);
	}
	if (ft_strncmp(line[i], ")\0", 3) == 0)
	{
		(*parenthesis)--;
		return (0);
	}
	if (ft_strncmp(line[i], "&", 1) == 0 && ft_strncmp(line[i], "&&\0", 3) != 0)
		return (check_error(line[i], RET_NOTIMPLEMENTED), 1);
	return (check_redirection(line, i));
}

int	check_bords(char **line, int i)
{
	if (ft_strncmp(line[i - 1], "&&\0", 3) == 0 || \
	ft_strncmp(line[i - 1], "||\0", 3) == 0)
		return (1);
	if (ft_strncmp(line[i + 1], "&&\0", 3) == 0 || \
	ft_strncmp(line[i + 1], "||\0", 3) == 0)
		return (1);
	if (ft_strncmp(line[i + 1], "|\0", 2) == 0 || \
	ft_strncmp(line[i + 1], "|\0", 2) == 0)
		return (1);
	if (ft_strncmp(line[i + 1], ")\0", 2) == 0 || \
	ft_strncmp(line[i + 1], ")\0", 2) == 0)
		return (1);
	return (0);
}

char	*missing_elements(char **line)
{
	char	*to_parse;
	char	*temp;
	char	*temp2;
	int		i;

	to_parse = line[0];
	i = 1;
	while (line[i])
	{
		temp = add_space(to_parse);
		if (!temp)
			return (NULL);
		to_parse = ft_strjoin(temp, line[i]);
		(free(temp), free(line[i]));
		if (!to_parse)
			return (NULL);
		i++;
	}
	temp2 = handle_missings();
	to_parse = add_space(to_parse);
	if (!temp2 || !to_parse)
		return (free(line), to_parse);
	temp = ft_strjoin(to_parse, temp2);
	(free(to_parse), free(temp2), free(line));
	return (temp);
}

char	*checker(char **line)
{
	int	parenthesis;
	int	i;

	parenthesis = 0;
	i = 0;
	while (line[i])
	{
		if (check_possible(line, &parenthesis, i) || parenthesis < 0)
			return (check_error(line[i], RET_PARENTHESIS), NULL);
		if (ft_strncmp(line[i], "&&\0", 3) == 0 || \
		ft_strncmp(line[i], "||\0", 3) == 0 || \
		ft_strncmp(line[i], "|\0", 2) == 0)
		{
			if (!line[i + 1])
				return (missing_elements(line));
			if (i == 0 || check_bords(line, i))
				return (check_error(line[i], RET_OPERATOR), NULL);
		}
		i++;
	}
	if (parenthesis > 0)
		return (missing_elements(line));
	return ("ok");
}
