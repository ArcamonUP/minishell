/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:54:44 by kbaridon          #+#    #+#             */
/*   Updated: 2025/03/27 14:43:24 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*get_redir(const char *line, int *i, int count)
{
	char	*result;

	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (line[*i])
	{
		if (count)
			result = NULL;
		else
			result = ft_token_file(line + *i);
		if (!count && !result)
			return (NULL);
		while (line[*i] && !ft_isspace(line[*i]))
			(*i)++;
	}
	else
		return (NULL);
	return (result);
}

char	*get_operator(const char *line, int *i, int count)
{
	char	*result;

	if (count)
		result = NULL;
	else
		result = ft_token_op(line + *i);
	if (!count && !result)
		return (NULL);
	if (line[*i] == '(' || line[*i] == ')')
		(*i)++;
	else
	{
		while (line[*i] && is_operator(line[*i]))
			(*i)++;
	}
	return (result);
}

char	*get_cmd(const char *line, int *i, int count)
{
	char	*result;

	result = NULL;
	if (!count)
		result = ft_token_cmd(line + *i);
	if (!count && !result)
		return (NULL);
	while (line[*i] && !is_operator(line[*i]))
	{
		if (line[*i] && line[*i] == '"')
		{
			(*i)++;
			while (line[*i] && line[*i] != '"')
				(*i)++;
		}
		else if (line[*i] && line[*i] == '\'')
		{
			(*i)++;
			while (line[*i] && line[*i] != '\'')
				(*i)++;
		}
		if (line[*i])
			(*i)++;
	}
	return (result);
}
