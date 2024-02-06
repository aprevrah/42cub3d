/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:59:36 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/13 15:37:14 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_count_token(char *str, char c)
{
	unsigned int	i;
	unsigned int	count;
	int				in_token;

	i = 0;
	in_token = 0;
	count = 0;
	while (str[i])
	{
		if (!in_token && str[i] != c)
		{
			in_token = 1;
			count++;
		}
		else if (in_token && str[i] == c)
		{
			in_token = 0;
		}
		i++;
	}
	return (count);
}

static void	ft_free_tab(char **strs, int j)
{
	while (j >= 0)
	{
		free(strs[j]);
		j--;
	}
	free(strs);
}

static int	ft_fill_tab(char const *s, char c, char **strs, int token_c)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	while (j < token_c)
	{
		while (s[i] == c)
			i++;
		size = 0;
		while (s[i + size] != c && s[i + size] != '\0')
			size++;
		strs[j] = ft_substr(s, i, size);
		if (!strs[j])
		{
			ft_free_tab(strs, --j);
			return (0);
		}
		i += size;
		j++;
	}
	strs[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		token_c;
	char	**strs;

	token_c = ft_count_token((char *)s, c);
	strs = (char **)malloc((token_c + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	if (!ft_fill_tab(s, c, strs, token_c))
		return (NULL);
	return (strs);
}
