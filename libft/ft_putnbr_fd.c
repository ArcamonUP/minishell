/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:26:33 by kbaridon          #+#    #+#             */
/*   Updated: 2024/11/06 20:17:49 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_nb(int nb)
{
	int	size;

	if (nb == 0)
		return (1);
	size = 1;
	while (nb / 10 != 0)
	{
		nb = nb / 10;
		size = size * 10;
	}
	return (size);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		size;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	size = ft_size_nb(n);
	while (size != 0)
	{
		c = (n / size) + '0';
		write(fd, &c, 1);
		n = n % size;
		size = size / 10;
	}
}
