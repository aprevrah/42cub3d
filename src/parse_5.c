#include "../include/cub3d.h"

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

char *set_null(int *location)
{
	location = 0;

	if (location == 0)
		return (NULL);
	return (NULL);
}


char	*read_map_data(int fd, t_map *map)
{
	t_rmd data;

	data.content = set_null(&data.location);
	while (1)
	{
		data.line = get_next_line(fd, 0);
		if (!data.line)
			break ;
		if (is_only_whitespace(data.line) && (data.location == 0 || data.location == 2))
		{
			free(data.line);
			continue ;
		}
		else if (data.location == 0)
			data.location = 1;
		else if (data.location == 1 && is_only_whitespace(data.line))
			data.location = 2;
		else if (data.location == 2 && !is_only_whitespace(data.line))
			return(free(data.line), printf("Failed to read map.\n"), data.content);
		map->height++;
		if (map->length < (int)ft_strlen(data.line) - 1)
			map->length = (int)ft_strlen(data.line) - 1;
		data.content = ft_str_append(data.content, data.line);
	}
	return (data.content);
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