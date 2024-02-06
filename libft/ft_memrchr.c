/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:33:35 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/13 15:29:09 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrchr(const void *s, int c, size_t n)
{
	unsigned char	*b;
	unsigned long	i;

	i = 0;
	b = (unsigned char *)s;
	while (i < n)
	{
		if (b[-i] == c)
			return ((void *)&b[-i]);
		i++;
	}
	return (0);
}
