/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:43:27 by kbaridon          #+#    #+#             */
/*   Updated: 2024/11/06 20:17:35 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_int(int n)
{
	int	nb;

	nb = 1;
	while (n / 10)
	{
		nb++;
		n /= 10;
	}
	return (nb);
}

static int	power_ten(int n)
{
	int	result;

	result = 1;
	while (n > 1)
	{
		result *= 10;
		n--;
	}
	return (result);
}

static int	is_negative(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

char	*ft_itoa(int n)
{
	int		count;
	int		i;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	count = size_int(n);
	if (n < 0)
		i = 1;
	n = is_negative(n);
	str = malloc(sizeof(char) * (count + 1 + i));
	if (str == NULL)
		return (NULL);
	if (i == 1)
		str[0] = '-';
	while (count > 0)
	{
		str[i] = (n / power_ten(count)) + '0';
		n %= power_ten(count);
		i++;
		count--;
	}
	str[i] = '\0';
	return (str);
}
