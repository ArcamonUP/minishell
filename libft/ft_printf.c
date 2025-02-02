/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:48:25 by kbaridon          #+#    #+#             */
/*   Updated: 2024/11/14 15:50:06 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static int	convert(char s, va_list ap, int count)
{
	if (s == 'c')
		return (ft_putcharc(va_arg(ap, int), count));
	if (s == 's')
		return (ft_putstrc(va_arg(ap, char *), count));
	if (s == 'p')
		return (ft_putpointer(va_arg(ap, void *), count));
	if (s == 'd')
		return (ft_putdecimal(va_arg(ap, int), count));
	if (s == 'i')
		return (ft_putdecimal(va_arg(ap, int), count));
	if (s == 'u')
		return (ft_putundecimal(va_arg(ap, unsigned int), count));
	if (s == 'x')
		return (ft_puthexa(va_arg(ap, unsigned int), 0, count));
	if (s == 'X')
		return (ft_puthexa(va_arg(ap, unsigned int), 1, count));
	return (ft_putcharc('%', count));
}

int	ft_printf(const char *str, ...)
{
	va_list			ap;
	unsigned int	count;

	count = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str != '%')
			count = ft_putcharc(*str, count);
		else
		{
			str++;
			count = convert(*str, ap, count);
		}
		str++;
	}
	va_end(ap);
	return (count);
}
