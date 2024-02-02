/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:21:43 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/13 15:34:14 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_handle_cases(int nb, int fd)
{
	if (nb == 0)
	{
		write(fd, "0", 1);
		return (0);
	}
	else if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (0);
	}
	else if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	return (nb);
}

void	ft_putnbr_fd(int nb, int fd)
{
	int		count;
	int		temp;
	int		index;
	int		digit;
	char	digits[10];

	nb = ft_handle_cases(nb, fd);
	if (nb == 0)
		return ;
	temp = nb;
	count = 0;
	while (temp > 0)
	{
		temp /= 10;
		count++;
	}
	index = count - 1;
	while (nb > 0)
	{
		digit = nb % 10;
		digits[index--] = digit + '0';
		nb /= 10;
	}
	write(fd, digits, count);
}
