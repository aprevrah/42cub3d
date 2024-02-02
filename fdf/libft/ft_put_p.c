/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:38:55 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/17 14:56:25 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_put_ulx(unsigned long nb, char *b)
{
	char	*c;
	int		printed;

	printed = 1;
	if (nb >= 16)
		printed += ft_put_ulx(nb / 16, b);
	c = b + (nb % 16);
	write(1, c, 1);
	return (printed);
}

int	ft_put_p(const void	*p)
{
	unsigned long	nb;
	int				printed;

	if (!p)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	nb = (unsigned long)p;
	printed = 2;
	write(1, "0x", 2);
	printed += ft_put_ulx(nb, "0123456789abcdef");
	return (printed);
}
