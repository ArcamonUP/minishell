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

int	already_exist(char **envp, char *arg)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (arg[size] && arg[size] != '=')
		size++;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], arg, size) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	remove_env(char ***envp, char *arg, int y)
{
	int		i;
	int		x;
	char	**result;

	i = already_exist(*envp, arg);
	if (i == -1)
		return ;
	result = ft_calloc(sizeof(char *), y);
	if (!result)
		return ;
	x = -1;
	y = 0;
	while ((*envp)[++x])
	{
		if (x == i)
			continue ;
		result[y] = ft_strdup((*envp)[x]);
		if (!result[y])
			return (free_tab(result), (void)0);
		y++;
	}
	free_tab((*envp));
	(*envp) = result;
}

void	add_env(char ***envp, char *arg, int y)
{
	int		i;
	char	**result;

	if (already_exist(*envp, arg) != -1)
	{
		remove_env(envp, arg, y);
		result = ft_calloc(sizeof(char *), y + 1);
	}
	else
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

int	parse_var(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	if (var[i] == '=' && i != 0)
		return (0);
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	ft_export(char *line, char ***envp, int i)
{
	char	**temp;

	temp = ft_divise(line, *envp, 0);
	if (!temp)
		return (127);
	if (!temp[0])
	{
		free_tab(temp);
		temp = cp_tab(*envp);
		if (!temp)
			return (127);
		return (print_sorted_tab(temp), free_tab(temp), 0);
	}
	i--;
	while (temp[++i])
	{
		if (!ft_strchr(temp[i], '='))
			remove_env(envp, temp[i], ft_tablen(*envp));
		else if (!parse_var(temp[i]))
			add_env(envp, ft_strdup(temp[i]), ft_tablen(*envp));
	}
	free_tab(temp);
	if (!*envp)
		return (127);
	return (0);
}
