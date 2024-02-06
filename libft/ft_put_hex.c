/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:21:34 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/16 20:13:15 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_put_hex(unsigned int nb, char *b)
{
	char	*c;
	int		printed;

	printed = 1;
	if (nb >= 16)
		printed += ft_put_hex(nb / 16, b);
	c = b + (nb % 16);
	write(1, c, 1);
	return (printed);
}
