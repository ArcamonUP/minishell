/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:21:13 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/24 12:51:56 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	count_all(char **line, int parenthesis, int i, int check)
{
	int	y;

	while (line[i])
	{
		y = 0;
		while (line[i][y])
		{
			if (check == 0 && line[i][y] == '\'')
				check = wait_next(line, &i, &y, '\'');
			if (check == 0 && line[i][y] == '\"')
				check = wait_next(line, &i, &y, '\"');
			if (check == 0 && line[i][y] == '(')
				parenthesis++;
			if (check == 0 && line[i][y] == ')')
				parenthesis--;
			if (parenthesis < 0)
				return (check_error(line[i], RET_PARENTHESIS), 2);
			if (check == 1)
				return (1);
			y++;
		}
		i++;
	}
	return (parenthesis != 0);
}

int	check_possible(char **line, int i)
{
	if (ft_strncmp(line[i], "&", 1) == 0 && ft_strncmp(line[i], "&&\0", 3) != 0)
		return (check_error(line[i], RET_NOTIMPLEMENTED), 0);
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
	if (ft_strncmp(line[i], ">", 1) == 0 || ft_strncmp(line[i], "<", 1) == 0)
		return (check_error(line[i], RET_OPERATOR), 1);
	return (0);
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
	int		i;

	to_parse = line[0];
	i = 1;
	while (line[i])
	{
		temp = add_char(to_parse, ' ');
		if (!temp)
			return (NULL);
		to_parse = ft_strjoin(temp, line[i]);
		free(temp);
		if (!to_parse)
			return (NULL);
		i++;
	}
	temp = handle_missings(to_parse);
	free(to_parse);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*checker(char **line)
{
	int	i;
	int	check;

	i = 0;
	check = count_all(line, 0, 0, 0);
	if (check == 2)
		return (NULL);
	if (check == 1)
		return (missing_elements(line));
	while (line[i])
	{
		if (check_possible(line, i))
			return (NULL);
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
	return ("0x20200487515969614000");
}
