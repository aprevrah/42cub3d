/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:27:19 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/13 15:44:01 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if ((c == ' ') || (c == '\f') || (c == '\n')
		|| (c == '\r') || (c == '\t') || (c == '\v'))
		return (1);
	else
		return (0);
}

static int	ft_to_int(char *str)
{
	int				i;
	unsigned int	nbr;

	nbr = 0;
	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr);
}

int	ft_atoi(const char *nptr)
{
	char	*str;
	int		s;
	int		nbr;

	s = 1;
	str = (char *)nptr;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		s = -1;
		str++;
	}
	nbr = ft_to_int(str);
	nbr *= s;
	return (nbr);
}
