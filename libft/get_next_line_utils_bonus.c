/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:16:47 by aprevrha          #+#    #+#             */
/*   Updated: 2023/12/15 15:57:15 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

unsigned long	gnl_ft_strlen(const char *s)
{
	unsigned long	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	char			*jstr;
	int				i;
	int				j;

	jstr = (char *)malloc(sizeof(char) * (gnl_ft_strlen(s1)
				+ gnl_ft_strlen(s2) + 1));
	if (!jstr)
		return (free(s1), s1 = NULL, NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		jstr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		jstr[i + j] = s2[j];
		j++;
	}
	jstr[i + j] = '\0';
	return (free(s1), s1 = NULL, jstr);
}

char	*gnl_ft_strdup(char const *s1)
{
	char			*dstr;
	int				i;

	dstr = (char *)malloc(sizeof(char) * (gnl_ft_strlen(s1) + 1));
	if (!dstr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dstr[i] = s1[i];
		i++;
	}
	dstr[i] = '\0';
	return (dstr);
}

char	*gnl_ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && (unsigned char)c == '\0')
		return ((char *)s);
	return (0);
}
