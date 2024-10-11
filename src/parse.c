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

int is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

# define WHITESPACE " \t\n\r\v\f"

void	skip_until(const char *str, unsigned int *i, const char *charset,
		bool val)
{
	while ((ft_strchr(charset, str[*i]) != 0) != val && str[*i] != '\0')
		*i += 1;
}



key_val(char *line, t_texture_data *texture_data)
{
	int i;

	i = 0;
	skip_until(line, &i, WHITESPACE, false);
	if (!ft_strncmp(&line[i], "NO", 2)) 
	{
		i += 2;
		if (ft_strchr(line[i], WHITESPACE))
			return (1);
		texture_data->path_NO = 
	}
		
	if (!ft_strncmp(&line[i], "EA", 2));
		texture_data->path_EA
	if (!ft_strncmp(&line[i], "SO", 2));
		texture_data->path_SO
	if (!ft_strncmp(&line[i], "WE", 2));
		texture_data->path_WE
	if (!ft_strncmp(&line[i], "C", 1));
		texture_data->col_C
	if (!ft_strncmp(&line[i], "F", 1));
		texture_data->col_F
	
}

static char	*read_file(int fd, t_map *map)
{
	char	*line;
	char	*content;

	content = NULL;
	while (1)
	{
		line = get_next_line(fd);
		key_val(line, &map->texture_data);
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
