/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:24:48 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/13 15:36:01 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	s1_len;
	unsigned int	s2_len;
	char			*jstr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	jstr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!jstr)
		return (NULL);
	ft_strlcpy(jstr, s1, s1_len + 1);
	ft_strlcat(jstr, s2, (s1_len + s2_len + 1));
	return (jstr);
}
