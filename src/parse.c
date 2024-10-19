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

char *get_key(unsigned int *i, char *s)
{
	unsigned int start;

	skip_until(s, i, WHITESPACE, true);
	if (!skip_until(s, i, WHITESPACE, false))
		return (NULL);
	start = *i;
	skip_until(s, i, "\n", true);
	return (ft_substr(s, start, *i - start));
}

int key_val(char *line, t_texture_data *texture_data)
{
	unsigned int i;

	i = 0;
	skip_until(line, &i, WHITESPACE, false);
	if (line[i] == '\0')
		return (0);
	else if (!ft_strncmp(&line[i], "NO", 2))
		texture_data->path_NO = get_key(&i, line);
	else if (!ft_strncmp(&line[i], "EA", 2))
		texture_data->path_EA = get_key(&i, line);
	else if (!ft_strncmp(&line[i], "SO", 2))
		texture_data->path_SO = get_key(&i, line);
	else if (!ft_strncmp(&line[i], "WE", 2))
		texture_data->path_WE = get_key(&i, line);
	else if (!ft_strncmp(&line[i], "C", 1) && !get_color(&line[i], &texture_data->col_C))
		return (printf("Failed to parse ceiling color."), 1);
	else if (!ft_strncmp(&line[i], "F", 1) && !get_color(&line[i], &texture_data->col_F))
		return (printf("Failed to parse floor color."), 1);
	else if (line[i] == '\n')
		return (100);
	return (1);
}

static char	*read_file(int fd, t_map *map)
{
	char	*line;
	char	*content;
	int		status;

	status = 0;
	while (status < 6)
	{
		line = get_next_line(fd);
		status += key_val(line, &map->texture_data);
		if (!line)
			break;
		free(line);
	}
	content = NULL;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map->height++;
		if (map->length < (int)ft_strlen(line) - 1)
			map->length = (int)ft_strlen(line) - 1;
		content = ft_str_append(content, line);
	}
	printf("%s\n", content);
	printf("NO: %s\n", map->texture_data.path_NO);
	printf("EA: %s\n", map->texture_data.path_EA);
	printf("SO: %s\n", map->texture_data.path_SO);
	printf("WE: %s\n", map->texture_data.path_WE);
	printf("C: %X\n", map->texture_data.col_C);
	printf("F: %X\n", map->texture_data.col_F);
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
