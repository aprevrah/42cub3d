/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:54:32 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/13 15:25:52 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*membs;

	if (nmemb != 0 && size != 0)
		if ((nmemb * size) / size != nmemb)
			return (NULL);
	membs = malloc(size * nmemb);
	if (!membs)
		return (membs);
	ft_bzero(membs, size * nmemb);
	return (membs);
}
