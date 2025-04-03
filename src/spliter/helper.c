/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:48:06 by achu              #+#    #+#             */
/*   Updated: 2025/04/03 18:49:28 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Shorten realloc function for char *
int	req_realloc(char	**buffer, size_t *size, size_t need)
{
	char	*new_buffer;
	size_t	new_size;

	if (*size > need)
		return (1);
	new_size = need * 2;
	new_buffer = ft_realloc(*buffer, *size, new_size);
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
	size_t	i;

	i = 0;
	new_size = size + 1;
	new_buffer = ft_realloc(*buffer, (size + 1)* sizeof(char *), (new_size + 1)* sizeof(char *));
	if (!new_buffer)
		return (0);
	new_buffer[new_size - 1] = NULL;
	new_buffer[new_size] = NULL;
	*buffer = new_buffer;
	return (1);
}