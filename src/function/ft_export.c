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

int	parse_var(char *var)
{
	int	i;

	if (!ft_strchr(var, '='))
		return (1);
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

	if (!ft_strchr(line, ' '))
	{
		temp = cp_tab(*envp);
		if (!temp)
			return (127);
		return (print_sorted_tab(temp), free_tab(temp), 0);
	}
	temp = ft_divise(line, *envp, 0);
	if (!temp)
		return (127);
	i--;
	while (temp[++i])
	{
		if (parse_var(temp[i]))
			continue ;
		else
			add_env(envp, ft_strdup(temp[i]), ft_tablen(*envp));
	}
	if (!*envp)
		return (free_tab(temp), 127);
	return (free_tab(temp), 0);
}
