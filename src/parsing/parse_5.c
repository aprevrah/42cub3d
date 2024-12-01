/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:48:24 by tmeniga@stu       #+#    #+#             */
/*   Updated: 2024/12/01 17:17:51 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	read_texture_data(char *str, t_texture_data *texture_data)
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
		line = get_line(str);
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

char	*set_null(int *location)
{
	location = 0;
	if (location == 0)
		return (NULL);
	return (NULL);
}

char	*read_map_data_small(char *str, t_map *map, t_rmd data)
{
	while (1)
	{
		data.line = get_line(str);
		if (!data.line || *data.line == '\0')
		{
			if (*data.line == '\0')
				return (free(data.line), data.line = NULL, data.content);
			break ;
		}
		if (is_only_whitespace(data.line) && (!data.in_map))
		{
			free(data.line);
			continue ;
		}
		else if (!data.in_map)
			data.in_map = 1;
		map->height++;
		if (map->length < (int)ft_strlen(data.line) - 1)
			map->length = (int)ft_strlen(data.line) - 1;
		data.content = ft_str_append(data.content, data.line);
		if (!data.content)
			return (NULL);
	}
	return (data.content);
}

char	*read_map_data(char *str, t_map *map)
{
	t_rmd	data;

	data.content = NULL;
	data.in_map = 0;
	data.content = read_map_data_small(str, map, data);
	return (data.content);
}

int	**new_2d_int_arr(int rows, int cols)
{
	int	**arr;
	int	i;

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
