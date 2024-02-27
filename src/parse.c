/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:06 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/27 22:00:45 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

char	*ft_str_append(char *a, char *b)
{
	char	*str;

	str = ft_strjoin(a, b);
	free(a);
	free(b);
	if (!str)
		return (NULL);
	return (a = NULL, b = NULL, str);
}

unsigned int	count_token(char *str, char c)
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

/*
int	fill_map(char const *s, char c, t_map *map)
{
	int	i;
	int	col;
	int	line;
	int	size;

	i = 0;
	line = 0;
	col = 0;
	while (line < map->height)
	{
		while (col < map->length)
		{
			while (s[i] == c)
				i++;
			map->arr[map->length * line + col] = ft_atoi(&s[i]);
			ft_printf("%i\n", map->arr[map->length * line + col]);
			while (s[i] != c && s[i] != '\n')
				i++;
			if (s[i] == '\n')
			{
				i++;
				break ;
			}
			col++;
		}
		col = 0;
		line++;
	}
	return (1);
}
*/

// Updata this to handle edge cases

int	fill_map(char const *s, char c, t_map *map)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (index < (map->height * map->length))
	{
		while (s[i] == c || s[i] == '\n') // Skip spaces
			i++;
		// if (s[i] == '\0') // Check for premature end of string
		//     return (0);
		// ft_printf("\n%s \n", &s[i]);
		map->arr[index] = ft_atoi(s + i); // Convert substring to integer
		index++;
		while (s[i] != c && s[i] != '\n' && s[i] != '\0')
			// Skip to next token or line
			i++;
		if (s[i] == '\n') // Skip newline character
			i++;
	}
	return (1);
}

t_map	*parse_map(int fd)
{
	char	*line;
	char	*content;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	content = NULL;
	map->height = 0;
	map->length = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!content)
		{
			map->length = count_token(line, ' ');
			map->height = 1;
			content = ft_strdup(line);
			free(line);
		}
		else
		{
			content = ft_str_append(content, line);
			map->height++;
		}
	}
	// ft_printf("\n%s\n", content);
	map->arr = (int *)malloc((map->length * map->height) * sizeof(int));
	if (!map->arr)
		return (free(map), NULL);
	ft_bzero(map->arr, map->length * map->height);
	ft_printf("Content: %s \n Length: %i Height: %i\n", content, map->length,
		map->height);
	fill_map(content, ' ', map);
	free(content);
	ft_printf("Done Pasing!\n");
	return (map);
}
