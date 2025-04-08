/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:21:13 by kbaridon          #+#    #+#             */
/*   Updated: 2025/04/08 14:43:44 by kbaridon         ###   ########.fr       */
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

int	check_wildcard(char *redir, char *filename)
{
	char	**tab;

	pre_asterisk(filename);
	tab = get_file(filename);
	if (!tab || !tab[0])
		return (check_error(redir, RET_NOFILE), 1);
	if (ft_strncmp(redir, "<", 1) == 0 && access(tab[0], F_OK) == -1)
		return (check_error(tab[0], RET_NOFILE), free_tab(tab), 1);
	else if (ft_strncmp(redir, "<", 1) == 0 && access(tab[0], R_OK) == -1)
		return (check_error(tab[0], RET_NOPERMISSIONS), free_tab(tab), 1);
	else if (ft_strncmp(redir, ">", 1) == 0 && \
		(access(tab[0], F_OK) == 0 && access(tab[0], W_OK) == -1))
		return (check_error(tab[0], RET_NOPERMISSIONS), free_tab(tab), 1);
	return (free_tab(tab), 0);
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
		if (ft_strchr(line[i + 1], '*'))
			return (check_wildcard(line[i], line[i + 1]));
		if (ft_strncmp(line[i], "<", 1) == 0 && access(line[i + 1], F_OK) == -1)
			return (check_error(line[i + 1], RET_NOFILE), 1);
		else if (ft_strncmp(line[i], "<", 1) == 0 && \
		access(line[i + 1], R_OK) == -1)
			return (check_error(line[i + 1], RET_NOPERMISSIONS), 1);
		else if (ft_strncmp(line[i], ">", 1) == 0 && \
		(access(line[i + 1], F_OK) == 0 && access(line[i + 1], W_OK) == -1))
			return (check_error(line[i + 1], RET_NOPERMISSIONS), 1);
	}
	if (ft_strncmp(line[i], "<<\0", 3) == 0)
	{
		if (!line[i + 1])
			return (check_error(line[i], RET_NEWLINE), 1);
	}
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
