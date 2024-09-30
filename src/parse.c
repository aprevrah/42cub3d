/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:06 by aprevrha          #+#    #+#             */
/*   Updated: 2024/09/30 15:30:52 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*ft_str_append(char *a, char *b)
{
	char	*str;

	str = ft_strjoin(a, b);
	free(a);
	free(b);
	if (!str)
		return (NULL);
	return (a = NULL, b = NULL, str);
}

static unsigned int	count_tokens(char *str, char c)
{
	unsigned int	i;
	unsigned int	count;
	int				in_token;

	i = 0;
	in_token = 0;
	count = 0;
	while (str[i])
	{
		if (!in_token && str[i] != c && str[i] != '\n')
		{
			in_token = 1;
			count++;
		}
		else if (in_token && (str[i] == c || str[i] == '\n'))
		{
			in_token = 0;
		}
		i++;
	}
	return (count);
}

static unsigned int	count_chars(char *str, char *chars)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strchr(chars, str[i]))
		{
			count++;
		}
	}
	return (count);
}

// Update this to handle edge cases
static int	fill_map(char const *s, char c, t_map *map)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (index < (map->height * map->length))
	{
		while (s[i] == c || s[i] == '\n')
			i++;
		map->arr[index] = ft_atoi(s + i);
		index++;
		while (s[i] != c && s[i] != '\n' && s[i] != '\0')
			i++;
	}
	return (1);
}

// Update this to handle edge cases
static int	identifier(char const *s, char c, t_map *map)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (index < (map->height * map->length))
	{
		while (s[i] == c || s[i] == '\n')
			i++;
		map->arr[index] = ft_atoi(s + i);
		index++;
		while (s[i] != c && s[i] != '\n' && s[i] != '\0')
			i++;
	}
	return (1);
}

// static char	*read_file(int fd, t_map *map)
// {
// 	char	*line;
// 	char	*content;

// 	content = NULL;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		if (ft_strncmp(line, , 3))
// 		while ()
// 	}
// 	return (content);
// }

t_map	*parse_map(int fd)
{
	t_map	*map;
	char	*content;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = 0;
	map->length = 0;
	content = read_file(fd, map);
	map->arr = (int *)malloc((map->length * map->height) * sizeof(int));
	if (!map->arr)
		return (free(map), NULL);
	ft_bzero(map->arr, map->length * map->height);
	fill_map(content, ' ', map);
	free(content);
	return (map);
}
