/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:32:20 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/28 14:48:28 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static int	get_len(char *line)
{
	int	i;
	int	size;
	int	c;

	c = 0;
	size = 0;
	while (line[size] && line[size] != '=')
		size++;
	i = size;
	while (line[i] && (line[i] != ' ' || c != 0))
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (c == line[i])
				c = 0;
			else if (c == 0)
				c = line[i];
		}
		if ((c == 0 && line[i] != '\"' && line[i] != '\'') || \
		(c != 0 && c != line[i]))
			size++;
		i++;
	}
	return (size);
}

static char	*get_value(char *line, int i, int c)
{
	int		y;
	char	*arg;

	y = 0;
	arg = ft_calloc(sizeof(char), get_len(line) + 1);
	if (!arg)
		return (NULL);
	while (line[i] && line[i] != '=')
		arg[y++] = line[i++];
	while (line[i] && (line[i] != ' ' || c != 0))
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (c == line[i])
				c = 0;
			else if (c == 0)
				c = line[i];
		}
		if ((c == 0 && line[i] != '\"' && line[i] != '\'') || \
		(c != 0 && c != line[i]))
			arg[y++] = line[i];
		i++;
	}
	return (arg);
}

static char	*get_arg(char *line)
{
	int		i;
	int		y;
	char	*arg;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (line[i - 1] == ' ')
	{
		y = i;
		while (line[y] && line[y] != ' ')
			y++;
		arg = ft_strndup(line + i, y - i);
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (free(arg), NULL);
	}
	while (line[i] && line[i] != ' ')
		i--;
	i++;
	arg = get_value(line + i, 0, 0);
	return (arg);
}

void	add_env(char ***envp, char *arg, int y)
{
	int		i;
	char	**result;

	result = ft_calloc(sizeof(char *), y + 2);
	if (!result)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		result[i] = ft_strdup((*envp)[i]);
		if (!result[i])
			return (free_tab(result), (void)0);
		i++;
	}
	result[i] = arg;
	free_tab((*envp));
	(*envp) = result;
}

int	ft_export(char *line, char ***envp, int i, int y)
{
	char	*arg;
	char	**temp;

	if (!ft_strchr(line, ' '))
	{
		temp = cp_tab(*envp);
		if (!temp)
			return (127);
		return (print_sorted_tab(temp), free_tab(temp), 0);
	}
	arg = get_arg(line);
	if (!arg)
		return (1);
	while (arg[i] && arg[i] != '=')
		i++;
	while ((*envp)[y] && ft_strncmp(arg, (*envp)[y], i) != 0)
		y++;
	if ((*envp)[y])
	{
		free((*envp)[y]);
		(*envp)[y] = arg;
		return (0);
	}
	add_env(envp, arg, y);
	return (0);
}
