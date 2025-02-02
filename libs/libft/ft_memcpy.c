/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:00:13 by kbaridon          #+#    #+#             */
/*   Updated: 2024/11/13 13:40:33 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr;
	const unsigned char	*ptr_src;

	if (!src && !dest)
		return (NULL);
	ptr = (unsigned char *)dest;
	ptr_src = (const unsigned char *)src;
	while (n > 0)
	{
		*ptr = *ptr_src;
		ptr++;
		ptr_src++;
		n--;
	}
	return (dest);
}
