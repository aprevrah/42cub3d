/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:51:25 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/27 20:42:31 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdarg.h>
#define L_HEX "0123456789abcdef"
#define U_HEX "0123456789ABCDEF"

static int	cases(va_list args, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_put_c(va_arg(args, int));
	else if (c == 's')
		count = ft_put_s(va_arg(args, char *));
	else if (c == 'i' || c == 'd')
		count = ft_put_i(va_arg(args, int));
	else if (c == 'u')
		count = ft_put_u(va_arg(args, unsigned int));
	else if (c == 'x')
		count = ft_put_hex(va_arg(args, unsigned int), L_HEX);
	else if (c == 'X')
		count = ft_put_hex(va_arg(args, unsigned int), U_HEX);
	else if (c == 'p')
		count = ft_put_p(va_arg(args, void *));
	else if (c == '%')
		count = ft_put_c('%');
	else
	{
		ft_put_c('%');
		count = ft_put_c(c) + 1;
	}
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	count;

	va_start(args, s);
	i = 0;
	count = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			count += cases(args, s[i]);
		}
		else
			count += ft_put_c(s[i]);
		i++;
	}
	va_end(args);
	return (count);
}
