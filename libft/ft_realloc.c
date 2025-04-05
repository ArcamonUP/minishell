/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:21:08 by achu              #+#    #+#             */
/*   Updated: 2025/04/05 16:49:51 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	size_t	size;
	void	*new;

	if (new_size == 0)
		return (free(ptr), NULL);
	if (!ptr)
		return (malloc(new_size));
	new = (void *)malloc(new_size);
	if (!new)
		return (NULL);
	size = new_size;
	if (old_size < new_size)
		size = old_size;
	ft_memcpy(new, ptr, size);
	free(ptr);
	return (new);
}
