/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdecimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:55:53 by kbaridon          #+#    #+#             */
/*   Updated: 2024/11/14 15:39:00 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putcharc(char c, int count)
{
	write(1, &c, 1);
	return (count + 1);
}

int	ft_putstrc(const char *str, int count)
{
	if (!str)
		return (ft_putstrc("(null)", count));
	while (*str)
	{
		count = ft_putcharc(*str, count);
		str++;
	}
	return (count);
}

static int	ft_size_nb(unsigned int nb)
{
	int	size;

	if (nb == 0)
		return (1);
	size = 1;
	while (nb / 10 != 0)
	{
		nb /= 10;
		size *= 10;
	}
	return (size);
}

int	ft_putdecimal(int nb, int count)
{
	char				c;
	unsigned int		size;

	if (nb == -2147483648)
	{
		count = ft_putstrc("-2147483648", count);
		return (count);
	}
	if (nb < 0)
	{
		count = ft_putcharc('-', count);
		nb = -nb;
	}
	size = ft_size_nb(nb);
	while (size != 0)
	{
		c = (nb / size) + '0';
		count = ft_putcharc(c, count);
		nb %= size;
		size /= 10;
	}
	return (count);
}

int	ft_putundecimal(unsigned int nb, int count)
{
	char			c;
	unsigned int	size;

	size = ft_size_nb(nb);
	while (size != 0)
	{
		c = (nb / size) + '0';
		count = ft_putcharc(c, count);
		nb %= size;
		size /= 10;
	}
	return (count);
}
