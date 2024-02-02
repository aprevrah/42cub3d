/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:54:32 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/08 21:47:55 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*ds;
	unsigned int	len;

	len = ft_strlen(s);
	ds = malloc(sizeof(char) * (len + 1));
	if (!ds)
		return (ds);
	ft_memcpy(ds, s, len + 1);
	return (ds);
}
