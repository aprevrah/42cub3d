/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:21:34 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/16 20:55:13 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_put_u(unsigned int nb)
{
	char	c;
	int		printed;

	printed = 1;
	if (nb >= 10)
		printed += ft_put_u(nb / 10);
	c = '0' + (nb % 10);
	write(1, &c, 1);
	return (printed);
}
