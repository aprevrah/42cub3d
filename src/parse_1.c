/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:06 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/27 13:52:59 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

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


int	is_valid_char(char const s) //! only accept spaces and newline, no tab
{
	if (s != '0' && s != '1' && s != 'N' && s != 'O' && s != 'S' && s != 'W' && \
	s != ' ' && s != '\t' && s != '\n' && s != '\r' && s != '\v'&& s != '\f')
		return (0);
	return (1);
}

int	get_dir(char c)
{
	if (c == 'N')
		return (3);
	if (c == 'O')
		return (4);
	if (c == 'S')
		return (5);
	else
		return (6);
}

int	count_players(t_map *map)
{
	int x;
	int y;
	int player_count;

	x = 0;
	y = 0;
	player_count = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->length)
		{
			if (map->arr[y][x] >= 3 && map->arr[y][x] <= 6)
				player_count++;
			x++;		
		}
		y++;	
	}
	if (player_count == 0)
		printf("Error: missing player\n");
	if (player_count > 1)
		printf("Error: too many players\n");
	return (player_count);
}

static int	procces_line(char const *s, t_map *map, int *i, int y)
{
	int x;

	x = 0;
	while (s[*i] && s[*i] != '\n')
	{
		if (!is_valid_char(s[*i]))
			return (printf("unvalid char in map\n"), 1);
		if (s[*i] == '0')
			map->arr[y][x] = 1;
		if (s[*i] == 'N' || s[*i] == 'O' || s[*i] == 'S' || s[*i] == 'W')
			map->arr[y][x] = get_dir(s[*i]);
		(*i)++;
		x++;
	}
	return (0);	
}

static int	fill_map(char const *s, t_map *map)
{
	int	i;
	int	y;


	i = 0;
	y = 0;
	while (y < map->height)
	{
		if (procces_line(s, map, &i, y))
			return (1);
		y++;
		if (s[i] != '\0')
			i++;
		else
 			break ;
	}
	if (count_players(map) == 0)
		return (printf("Error: missing player\n"), 1);
	if (count_players(map) > 1)
		return (printf("Error: too many players\n"), 1);
	return (0);
}
// static int	fill_map(char const *s, t_map *map)
// {
// 	int	i;
// 	int	x;
// 	int	y;
// 	int j;

// 	i = 0;
// 	x = 0;
// 	y = 0;
// 	j = 0;

// 	while (y < map->height)
// 	{
// 		while (s[i] && s[i] != '\n')
// 		{
// 			if (!is_valid_char(s[i]) || j > 1)
// 				return (printf("unvalid char in map\n"), 1);
// 			if (s[i] == '0')
// 				map->arr[y][x] = 1;
// 			if (s[i] == 'N' || s[i] == 'O' || s[i] == 'S' || s[i] == 'W')
// 			{
// 				j++;
// 				map->arr[y][x] = get_dir(s[i]);
// 			}
// 			i++;
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 		if (s[i] != '\0')
// 			i++;
// 		else
// 			break ;
// 	}
// 	if (j == 0)
// 		return (printf("missing player position\n"), 1);
// 	return (0);
// }

int	skip_until(const char *str, unsigned int *i, const char *charset,
		bool val)
{
	int chars_skipped;
	
	chars_skipped = 0;
	while ((ft_strchr(charset, str[*i]) != 0) != val && str[*i] != '\0')
	{
		*i += 1;
		chars_skipped++;
	}
	return (chars_skipped);
}

unsigned int	ft_to_int(char *str, unsigned int *i)
{
	unsigned int	nbr;

	nbr = 0;
	while ('0' <= str[*i] && str[*i] <= '9')
	{
		nbr = nbr * 10 + (str[*i] - '0');
		*i += 1;
	}
	return (nbr);
}

int count_words(char *str)
{
	int i;
	int count;
	int in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
			str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
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
	int i;

	i = 0;
	while (str[i])
		i++;

	while (i > 0 && (str[i-1] == ' ' || str[i-1] == '\t' || \
		str[i-1] == '\r' || str[i-1] == '\v' || str[i-1] == '\f'))
		i--;

	str[i] = '\0';

	return (i);
}

int is_only_numeric_and_2_comma(char *str, int i)
{
	int count = 0;

	if (!str || str[i] == '\0')
		return (0);

	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ',' &&
			str[i] != ' ' && str[i] != '\t' && str[i] != '\r' &&
			str[i] != '\v' && str[i] != '\f' && str[i] != '\n')
		{
			return (0);
		}
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count == 2);
}

int	gc_error_check(char *s)
{
	if (count_words(s) != 2)
		return (printf("Error: color line needs 2 arguments\n"), 1);
	if (s[1] && s[1] != ' ')
		return (printf("Error: missing space after identifier\n"), 1);
	if (!is_only_numeric_and_2_comma(s, 1))
		return (printf("Error: syntax error in color line\n"), 1);
	return (0);
} 

int get_color(char *s, unsigned int *color)
{
	unsigned int i;
	t_color_value color_value;

	i = 0;
	if (gc_error_check(s))
		return (1);
	skip_until(s, &i, WHITESPACE, true);
	if (!skip_until(s, &i, WHITESPACE, false))
		return (1);
	color_value.r = ft_to_int(s, &i);
	if (s[i] != ',')
		return (1);
	i++;
	skip_until(s, &i, WHITESPACE, false);
	color_value.g = ft_to_int(s, &i);
	if (s[i] != ',')
		return (1);
	i++;
	skip_until(s, &i, WHITESPACE, false);
	color_value.b = ft_to_int(s, &i);
	if (color_value.r > 255 || color_value.g > 255 || color_value.b > 255)
		return (printf("Error: color values too high\n"), 1);
	*color = (color_value.r << 16) | (color_value.g << 8) | color_value.b;
	return (0);
}

int get_key(unsigned int *i, char *s, char **path)
{
	unsigned int start;

	if (count_words(s) != 2)
		return (printf("Error: texture line needs 2 arguments\n"), 1);
	if (s[*i+2] && s[*i+2] != ' ')
		return (printf("Error: missing space after identifier\n"), 1);
	skip_until(s, i, WHITESPACE, true);
	if (!skip_until(s, i, WHITESPACE, false))
		return (printf("Error: Unable to parse: %s", s), 1);
	start = *i;
	skip_until(s, i, "\n", true);
	if (*path)
		return (printf("Error: Duplicate config: %s", s), 1);
	*path = ft_substr(s, start, *i - start);
	if (!path)
		return (printf("Error: Malloc failed."), 1);
	trim_spaces_at_end(*path);
	return (0);
}

bool is_only_whitespace(char *s)
{
	unsigned int i;
	i = 0;
	skip_until(s, &i, WHITESPACE, false);
	return (s[i] == '\0');
}

int key_val(char *line, t_texture_data *texture_data)
{
	unsigned int i;

	i = 0;
	skip_until(line, &i, WHITESPACE, false);
	if (line[i] == '\0')
		return (2);
	else if (!ft_strncmp(&line[i], "NO", 2))
		return (get_key(&i, line, &texture_data->path_NO));
	else if (!ft_strncmp(&line[i], "EA", 2))
		return (get_key(&i, line, &texture_data->path_EA));
	else if (!ft_strncmp(&line[i], "SO", 2))
		return (get_key(&i, line, &texture_data->path_SO));
	else if (!ft_strncmp(&line[i], "WE", 2))
		return (get_key(&i, line, &texture_data->path_WE));
	else if (!ft_strncmp(&line[i], "C", 1))
		return (get_color(&line[i], &texture_data->col_C));
	else if (!ft_strncmp(&line[i], "F", 1))
		return (get_color(&line[i], &texture_data->col_F));
	printf("Error: Unable to parse: %s", line);
	return (1);
}

int read_texture_data(int fd, t_texture_data *texture_data)
{
	char	*line;
	int		status;
	int		configs;

	texture_data->path_NO = NULL;
	texture_data->path_EA = NULL;
	texture_data->path_SO = NULL;
	texture_data->path_WE = NULL;
	configs = 0;
	while (configs < 6)
	{
		line = get_next_line(fd, 0);
		if (!line)
			return (1);
		status = key_val(line, texture_data);
		free(line);
		if (status == 0)
			configs++;
		else if (status == 1)
			return (1);
	}
	return (0);
}

static char	*read_map_data(int fd, t_map *map)
{
	char	*line;
	char	*content;
	int		location;

	content = NULL;
	location = 0;
	while (1)
	{
		line = get_next_line(fd, 0);
		if (!line)
			break ;
		if (is_only_whitespace(line) && (location == 0 || location == 2))
		{
			free(line);
			continue ;
		}
		else if (location == 0)
			location = 1;
		else if (location == 1 && is_only_whitespace(line))
			location = 2;
		else if (location == 2 && !is_only_whitespace(line))
			return(free(line), printf("Failed to read map.\n"), content);
		map->height++;
		if (map->length < (int)ft_strlen(line) - 1)
			map->length = (int)ft_strlen(line) - 1;
		content = ft_str_append(content, line);
	}
	return (content);
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


int	procces_line2(char const *s, int **arr, int *i, int y)
{
	int x;

	x = 0;
	while (s[*i] && s[*i] != '\n')
	{
		if (s[*i] == '0' || s[*i] == 'N' || s[*i] == 'O' || s[*i] == 'S' || s[*i] == 'W')
				arr[y][x] = 1;
			if (s[*i] == ' ')
				arr[y][x] = 8;
		(*i)++;
		x++;
	}
	return (x);	
}

static int	fill_map2(char const *s, t_map *map, int **arr)
{
	int	i;
	int x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (y < map->height)
	{
		x = procces_line2(s, arr, &i, y);
		while (x < map->length)
		{
			arr[y][x] = 8;
			x++;
		}
		y++;
		if (s[i] != '\0')
			i++;
		else
			break ;
	}
	return (0);
}

//! check minimum a least 3 row and collums;

int	check_sides(int **arr, int height, int length)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < length)
	{
		if (arr[0][x] == 1 || arr[height-1][x] == 1)
			return (0);
		x++;
	}
	while (y < height)
	{
		if (arr[y][0] == 1 || arr[y][length-1] == 1)
			return (0);
		y++;
	}
	return (1);
}

int check_middle(int **arr, int height, int length)
{
	int x;
	int y;

	x = 1;
	y = 1;
	while (y < height-1)
	{
		x = 1;
		while (x < length-1)
		{
			if (arr[y][x] == 1)
			{
				if ((arr[y-1][x] != 0 && arr[y-1][x] != 1) || \
					(arr[y][x+1] != 0 && arr[y][x+1] != 1) || \
					(arr[y+1][x] != 0 && arr[y+1][x] != 1) || \
					(arr[y][x-1] != 0 && arr[y][x-1] != 1))
				{
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	is_wall_enclosed(char *content , t_map *map)
{
	int **array;

	array = new_2d_int_arr(map->height, map->length);
	if (!array)
		return (0);
	fill_map2(content, map,array);
	if (!check_sides(array, map->height, map->length))
		return (printf("Error: map is not enclosed\n"), free_2d_arr((void **)array, map->height), 0);
	if (!check_middle(array, map->height, map->length))
		return (printf("Error: map is not enclosed\n"), free_2d_arr((void **)array, map->height), 0);
	free_2d_arr((void **)array, map->height);
	return (1);
}


t_texture_data	*get_texture_data(int fd)
{
	t_texture_data	*texture_data;
	
	texture_data = (t_texture_data *)malloc(sizeof(t_texture_data));
	if (!texture_data)
		return (NULL);
	if (read_texture_data(fd, texture_data))
		return (get_next_line(fd, 1), free_texture_data(texture_data), NULL);
	return (texture_data);
}

t_map	*get_map(int fd, t_texture_data *texture_data)
{
	t_map	*map;
	char	*content;

	
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (get_next_line(fd, 1), free_texture_data(texture_data), NULL);
	map->texture_data = texture_data;
	map->height = 0;
	map->length = 0;
	content = read_map_data(fd, map);
	if (!content)
		return (get_next_line(fd, 1), free_texture_data(texture_data), free(map),NULL);
	map->arr = new_2d_int_arr(map->height, map->length);
	if (!map->arr)
		return (get_next_line(fd, 1), free_texture_data(texture_data), free(map), free(content), NULL);
	if (fill_map(content, map))
		return (get_next_line(fd, 1), free_texture_data(texture_data), free(content), free_map(map), NULL);
	if (!is_wall_enclosed(content, map))
		return (get_next_line(fd, 1), free_texture_data(texture_data), free(content), free_map(map), NULL);
	free(content);
	
	return (map);
}


// # function protected and tested with valgrind
t_map	*parse_map(int fd)
{
	t_map			*map;
	t_texture_data	*texture_data;


	if ((texture_data = get_texture_data(fd)) == NULL)
		return (NULL);
	printtexture_data(*texture_data); //! delete
	
	if ((map = get_map(fd, texture_data)) == NULL)
		return (NULL); 

	return (map);
}




// t_map	*parse_map(int fd)
// {
// 	t_map			*map;
// 	t_texture_data	*texture_data;
// 	char			*content;

// 	texture_data = (t_texture_data *)malloc(sizeof(t_texture_data));
// 	if (!texture_data)
// 		return (NULL);
// 	if (read_texture_data(fd, texture_data))
// 		return (get_next_line(fd, 1), free_texture_data(texture_data), NULL);
// 	printtexture_data(*texture_data);
// 	map = (t_map *)malloc(sizeof(t_map));
// 	if (!map)
// 		return (get_next_line(fd, 1), free_texture_data(texture_data), NULL);
// 	map->texture_data = texture_data;
// 	map->height = 0;
// 	map->length = 0;
// 	content = read_map_data(fd, map);
// 	if (!content)
// 		return (get_next_line(fd, 1), free_texture_data(texture_data), free(map),NULL);
// 	map->arr = new_2d_int_arr(map->height, map->length);
// 	if (!map->arr)
// 		return (get_next_line(fd, 1), free_texture_data(texture_data), free(map), free(content), NULL);

// 	if (fill_map(content, map))
// 		return (get_next_line(fd, 1), free_texture_data(texture_data), free(content), free_map(map), NULL);

// 	if (!is_wall_enclosed(content, map))
// 		return (get_next_line(fd, 1), free_texture_data(texture_data), free(content), free_map(map), NULL);


// 	printf("\nINPUT\n%s\n", content);
// 	printf("\nConverted map\n\n");
// 	printmap(map);

// 	// maunaly check if the map was correcty filled
// 	free(content);
// 	return (map);
// }
