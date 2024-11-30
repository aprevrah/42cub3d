/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:49:22 by tmeniga@stu       #+#    #+#             */
/*   Updated: 2024/11/30 16:19:04 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	count_words(char *str)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f')
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

int	trim_spaces_at_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0 && (str[i - 1] == ' ' || str[i - 1] == '\t' || \
		str[i - 1] == '\r' || str[i - 1] == '\v' || str[i - 1] == '\f'))
		i--;
	str[i] = '\0';
	return (i);
}

char	*ft_str_append(char *a, char *b)
{
	char	*str;

	if (!a && !b)
		return (NULL);
	else if (!a)
		str = ft_strdup(b);
	else if (!b)
		str = ft_strdup(a);
	else
		str = ft_strjoin(a, b);
	free(a);
	free(b);
	if (!str)
		return (NULL);
	return (a = NULL, b = NULL, str);
}

bool	is_only_whitespace(char *s)
{
	unsigned int	i;

	i = 0;
	skip_until(s, &i, WHITESPACE, false);
	return (s[i] == '\0');
}

int	skip_until(const char *str, unsigned int *i, const char *charset, bool val)
{
	int	chars_skipped;

	chars_skipped = 0;
	while ((ft_strchr(charset, str[*i]) != 0) != val && str[*i] != '\0')
	{
		*i += 1;
		chars_skipped++;
	}
	return (chars_skipped);
}
