/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:03:58 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/10 18:22:02 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	l_len;
	size_t	b_len;

	l_len = ft_strlen(little);
	b_len = ft_strlen(big);
	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	while (b_len - i >= l_len)
	{
		j = 0;
		while (j + i < len && big[i + j] == little[j] && little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
