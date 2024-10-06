/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:06 by aprevrha          #+#    #+#             */
/*   Updated: 2024/09/30 18:46:51 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*ft_str_append(char *a, char *b)
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

// static unsigned int	count_tokens(char *str, char c)
// {
// 	unsigned int	i;
// 	unsigned int	count;
// 	int				in_token;

// 	i = 0;
// 	in_token = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (!in_token && str[i] != c && str[i] != '\n')
// 		{
// 			in_token = 1;
// 			count++;
// 		}
// 		else if (in_token && (str[i] == c || str[i] == '\n'))
// 		{
// 			in_token = 0;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

// static unsigned int	count_chars(char *str, char *chars)
// {
// 	unsigned int	i;
// 	unsigned int	count;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (ft_strchr(chars, str[i]))
// 		{
// 			count++;
// 		}
// 	}
// 	return (count);
// }


static int	fill_map(char const *s, t_map *map)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (y < map->height)
	{
		while (s[i] && s[i] != '\n')
		{
			if (s[i] == '0')
				map->arr[y][x] = 1;
			i++;
			x++;
		}
		x = 0;
		y++;
		if (s[i] != '\0')
			i++;
		else
			break ;
	}
	return (1);
}

// Update this to handle edge cases
// static int	identifier(char const *s, char c, t_map *map)
// {
// 	int	i;
// 	int	index;

// 	i = 0;
// 	index = 0;
// 	while (index < (map->height * map->length))
// 	{
// 		while (s[i] == c || s[i] == '\n')
// 			i++;
// 		map->arr[index] = ft_atoi(s + i);
// 		index++;
// 		while (s[i] != c && s[i] != '\n' && s[i] != '\0')
// 			i++;
// 	}
// 	return (1);
// }

static char	*read_file(int fd, t_map *map)
{
	char	*line;
	char	*content;

	content = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		//if (ft_strncmp(line, , 3))
		map->height++;
		if (map->length < (int)ft_strlen(line) - 1)
			map->length = (int)ft_strlen(line) - 1;
		content = ft_str_append(content, line);
	}
	printf("%s\n", content);
	return (content);
}

void printmap(t_map *map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < map->height)
	{
		while (x < map->length)
		{
			printf("%i", map->arr[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}

int **new_2d_int_arr(int rows, int cols)
{
	int **arr;
	int i;

	arr = (int **)ft_calloc(rows, sizeof(int *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		arr[i] = (int *)ft_calloc(cols, sizeof(int));
		if (!arr[i])
		{
			while (i > 0)
				free(arr[--i]);
			free(arr);
			return (NULL);
		}
		i++;
	}
	return (arr);
}

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
	map->arr = new_2d_int_arr(map->height, map->length);
	if (!map->arr)
		return (free(map), NULL);
	fill_map(content, map);
	free(content);
	printf("\nConverted map\n\n");
	// to test if the map was correcty filled
	printmap(map);
	return (map);
}
