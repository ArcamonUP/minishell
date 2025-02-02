/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:25:38 by kbaridon          #+#    #+#             */
/*   Updated: 2024/11/14 15:24:06 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_int(unsigned long long num)
{
	int		size;

	size = 0;
	while (num != 0)
	{
		num /= 16;
		size++;
	}
	if (size == 0)
		return (1);
	return (size);
}

static char	*int_to_hex(unsigned long long num, int upper)
{
	char	*hex_str;
	char	*hex_digits;
	int		temp;
	int		s;

	s = size_int(num);
	if (upper)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	hex_str = (char *)malloc(s + 1);
	if (!hex_str)
		return (NULL);
	hex_str[s] = '\0';
	s--;
	while (s >= 0)
	{
		temp = num % 16;
		hex_str[s] = hex_digits[temp];
		num /= 16;
		s--;
	}
	return (hex_str);
}

int	ft_puthexa(unsigned long long nb, int upper, int count)
{
	char	*str;
	int		i;

	str = int_to_hex(nb, upper);
	if (!str)
	{
		free(str);
		return (count);
	}
	i = 0;
	while (str[i])
	{
		count = ft_putcharc(str[i], count);
		i++;
	}
	free(str);
	return (count);
}

int	ft_putpointer(void *p, int count)
{
	unsigned long long	nb;

	if (p == NULL)
		return (ft_putstrc("(nil)", count));
	nb = (unsigned long long)p;
	count = ft_putstrc("0x", count);
	return (ft_puthexa(nb, 0, count));
}
