/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:06 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/16 15:26:40 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


// int	is_map_enclosed(t_map *map)
// {


	
// }

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



// # also check that there is as least one direction in the map
static int	fill_map(char const *s, t_map *map)
{
	(void) map;
	int	i;
	int	x;
	int	y;
	int j;

	i = 0;
	x = 0;
	y = 0;
	j = 0;

	while (y < map->height)
	{
		while (s[i] && s[i] != '\n')
		{
			if (!is_valid_char(s[i]) || j > 1)
				return (printf("unvalid char in map\n"), 1);
			if (s[i] == '0')
				map->arr[y][x] = 1;
			if (s[i] == 'N' || s[i] == 'O' || s[i] == 'S' || s[i] == 'W')
			{
				j++;
				map->arr[y][x] = get_dir(s[i]);
			}
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
	if (j == 0)
		return (printf("missing player position\n"), 1);
	return (0);
}

# define WHITESPACE " \t\n\r\v\f"
# define NUNERIC "0123456789"

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

int get_color(char *s, unsigned int *color)
{
	unsigned int i;
	unsigned int r, g, b;

	i = 0;
	skip_until(s, &i, WHITESPACE, true);
	if (!skip_until(s, &i, WHITESPACE, false))
		return (1);
	r = ft_to_int(s, &i);
	if (s[i] != ',')
		return (1);
	i++;
	skip_until(s, &i, WHITESPACE, false);
	g = ft_to_int(s, &i);
	if (s[i] != ',')
		return (1);
	i++;
	skip_until(s, &i, WHITESPACE, false);
	b = ft_to_int(s, &i);

	if (r > 255 || g > 255 || b > 255)
		return (1);
	*color = (r << 16) | (g << 8) | b;
	return (0);
}

int get_key(unsigned int *i, char *s, char **path)
{
	unsigned int start;

	skip_until(s, i, WHITESPACE, true);
	if (!skip_until(s, i, WHITESPACE, false))
		return (printf("Unable to parse: %s", s), 1);
	start = *i;
	skip_until(s, i, "\n", true);
	if (*path)
		return (printf("Duplicate config: %s", s), 1);
	*path = ft_substr(s, start, *i - start);
	if (!path)
		return (printf("Malloc failed."), 1);
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
		return (get_key(&i, line, &texture_data->path_no));
	else if (!ft_strncmp(&line[i], "EA", 2))
		return (get_key(&i, line, &texture_data->path_ea));
	else if (!ft_strncmp(&line[i], "SO", 2))
		return (get_key(&i, line, &texture_data->path_so));
	else if (!ft_strncmp(&line[i], "WE", 2))
		return (get_key(&i, line, &texture_data->path_we));
	else if (!ft_strncmp(&line[i], "C", 1))
		return (get_color(&line[i], &texture_data->col_c));
	else if (!ft_strncmp(&line[i], "F", 1))
		return (get_color(&line[i], &texture_data->col_f));
	printf("Unable to parse: %s", line);
	return (1);
}

int read_texture_data(int fd, t_texture_data *texture_data)
{
	char	*line;
	int		status;
	int		configs;

	texture_data->path_no = NULL;
	texture_data->path_ea = NULL;
	texture_data->path_so = NULL;
	texture_data->path_we = NULL;
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

// static char	*read_map_data(int fd, t_map *map)
// {
// 	char	*line;
// 	char	*content;
	
// 	content = NULL;
// 	line = get_next_line(fd, 0);
// 	while(is_only_whitespace(line))
// 	{
// 		free(line);
// 		line = get_next_line(fd, 0);
// 	}
// 	while (line)
// 	{
// 		map->height++;
// 		if (map->length < (int)ft_strlen(line) - 1)
// 			map->length = (int)ft_strlen(line) - 1;
// 		content = ft_str_append(content, line);
// 		line = get_next_line(fd, 0);
// 	}
// 	return (content);
// }

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


// # also check that there is as least one direction in the map
static int	fill_map2(char const *s, t_map *map, int **arr)
{
	(void) map;
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
			if (s[i] == '0' || s[i] == 'N' || s[i] == 'O' || s[i] == 'S' || s[i] == 'W')
				arr[y][x] = 1;
			if (s[i] == ' ')
				arr[y][x] = 8;
			i++;
			x++;
		}
		while (x < map->length)
		{
			arr[y][x] = 8;
			x++;
		}
		x = 0;
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
	
	int x;
	int y;


	x = 0;
	y = 0;
	printf("\nis_wall_enclosed()\n\n");
	while (y < map->height)
	{
		while (x < map->length)
		{
			printf("%i", array[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}

	if (!check_sides(array, map->height, map->length))
		return (printf("sides\n"), free_2d_arr((void **)array, map->height), 0);
	
	if (!check_middle(array, map->height, map->length))
		return (printf("middle\n"), free_2d_arr((void **)array, map->height), 0);

	free_2d_arr((void **)array, map->height);
	return (1);
}

// # function protected and tested with valgrind
t_map	*parse_map(int fd)
{
	t_map			*map;
	t_texture_data	*texture_data;
	char			*content;

	texture_data = (t_texture_data *)malloc(sizeof(t_texture_data));
	if (!texture_data)
		return (NULL);
	if (read_texture_data(fd, texture_data))
		return (get_next_line(fd, 1), free_texture_data(texture_data), NULL);
	printtexture_data(*texture_data);
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
			
	
	printf("\nINPUT\n%s\n", content);
	printf("\nConverted map\n\n");
	printmap(map);
	
	// maunaly check if the map was correcty filled
	free(content);
	return (map);
}
