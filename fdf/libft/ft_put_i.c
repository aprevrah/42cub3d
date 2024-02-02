/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:53:08 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/16 17:15:57 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static void	ft_write_c(char *s, unsigned int size, int *printed)
{
	*printed += write(1, s, size);
}

static int	ft_handle_cases(int nb, int *printed)
{
	if (nb == 0)
	{
		ft_write_c("0", 1, printed);
	}
	else if (nb == -2147483648)
	{
		ft_write_c("-2147483648", 11, printed);
		return (0);
	}
	else if (nb < 0)
	{
		ft_write_c("-", 1, printed);
		nb = -nb;
	}
	return (nb);
}

int	ft_put_i(int nb)
{
	int		printed;
	int		count;
	int		temp;
	int		index;
	char	digits[10];

	printed = 0;
	count = 0;
	nb = ft_handle_cases(nb, &printed);
	if (nb == 0)
		return (printed);
	temp = nb;
	while (temp > 0)
	{
		temp /= 10;
		count++;
	}
	index = count - 1;
	while (nb > 0)
	{
		digits[index--] = (nb % 10) + '0';
		nb /= 10;
	}
	ft_write_c(digits, count, &printed);
	return (printed);
}
