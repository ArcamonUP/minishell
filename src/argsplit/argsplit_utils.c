/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argsplit_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:48:06 by achu              #+#    #+#             */
/*   Updated: 2025/04/08 14:04:55 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Shorten realloc function for char *
int	req_realloc(char **buffer, size_t *size, size_t need)
{
	char	*new_buffer;
	size_t	new_size;

	if (*size > need)
		return (1);
	new_size = need * 2;
	new_buffer = ft_realloc(*buffer, *size * sizeof(char), \
		new_size * sizeof(char));
	if (!new_buffer)
		return (0);
	*buffer = new_buffer;
	*size = new_size;
	return (1);
}

// Shorten realloc function for char **
int	expand_realloc(char	***buffer, size_t size)
{
	char	**new_buffer;
	size_t	new_size;

	new_size = size + 1;
	new_buffer = ft_realloc(*buffer, (size + 1) * sizeof(char *), \
		(new_size + 1) * sizeof(char *));
	if (!new_buffer)
		return (0);
	new_buffer[new_size - 1] = NULL;
	new_buffer[new_size] = NULL;
	*buffer = new_buffer;
	return (1);
}

int	add_join(char **buffer, char *join, size_t *size, size_t *i)
{
	size_t	len;	

	len = ft_strlen(join);
	if (!req_realloc(buffer, size, *i + len + 1))
		return (0);
	ft_strcpy(*buffer + *i, join);
	*i += len;
	free(join);
	return (1);
}

int	add_schar(char **buffer, char **str, size_t *size, size_t *i)
{
	if (!req_realloc(buffer, size, *i + 1))
		return (0);
	(*buffer)[*i] = **str;
	(*buffer)[*i + 1] = '\0';
	(*i)++;
	(*str)++;
	return (1);
}

int	add_var(char **buffer, char *var, size_t *size, size_t *i)
{
	size_t	len;

	len = ft_strlen(var);
	if (!req_realloc(buffer, size, *i + len + 1))
		return (0);
	ft_strcpy(&(*buffer[*i]), var);
	*i += len;
	free(var);
	return (1);
}
