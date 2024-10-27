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
	printf("Unable to parse: %s", line);
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
		line = get_next_line(fd);
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
		line = get_next_line(fd);
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
	printf ("height: %i length: %i\n", map->height, map->length);
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

//This is some BS
void gnl_clear_buffer(fd)
{
	char *line;

	line = NULL;
	while (1)
	{
		get_next_line(fd);
		free(line);
		if (!line)
			return ;
	}
}

void printtexture_data(t_texture_data texture_data)
{
	printf("NO: %s\n", texture_data.path_NO);
	printf("EA: %s\n", texture_data.path_EA);
	printf("SO: %s\n", texture_data.path_SO);
	printf("WE: %s\n", texture_data.path_WE);
	printf("C: #%06X\n", texture_data.col_C);
	printf("F: #%06X\n", texture_data.col_F);
}

t_map	*parse_map(int fd)
{
	t_map			*map;
	t_texture_data	*texture_data;
	char			*content;

	texture_data = (t_texture_data *)malloc(sizeof(t_texture_data));
	if (!texture_data)
		return (NULL);
	if (read_texture_data(fd, texture_data))
		return (gnl_clear_buffer(fd), free_texture_data(texture_data), NULL);
	printtexture_data(*texture_data);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (free_texture_data(texture_data), NULL);
	map->texture_data = texture_data;
	map->height = 0;
	map->length = 0;
	content = read_map_data(fd, map);
	map->arr = new_2d_int_arr(map->height, map->length);
	if (!map->arr)
		return (free(content), free(texture_data), free_map(map), NULL);
	fill_map(content, map);
	printf("%s\n", content);
	free(content);
	printf("\nConverted map\n\n");
	// maunaly check if the map was correcty filled
	printmap(map);
	return (map);
}
