/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:50:34 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/13 15:29:41 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit_count(int nb)
{
	int	count;

	count = 1;
	if (nb < 0)
		count++;
	while (nb >= 10 || nb <= -10)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	nb;
	int				nb_len;
	int				i;

	nb_len = ft_digit_count(n);
	if (n < 0)
		nb = -n;
	else
		nb = n;
	s = (char *)malloc(sizeof(char) * (nb_len + 1));
	if (!s)
		return (NULL);
	i = nb_len - 1;
	if (n == 0)
		s[0] = '0';
	while (nb > 0)
	{
		s[i--] = '0' + (nb % 10);
		nb /= 10;
	}
	if (n < 0)
		s[0] = '-';
	s[nb_len] = '\0';
	return (s);
}
