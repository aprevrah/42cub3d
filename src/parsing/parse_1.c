/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:06 by aprevrha          #+#    #+#             */
/*   Updated: 2024/12/01 16:23:34 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_texture_data	*get_texture_data(char *str)
{
	t_texture_data	*texture_data;

	texture_data = (t_texture_data *)malloc(sizeof(t_texture_data));
	if (!texture_data)
		return (NULL);
	if (read_texture_data(str, texture_data))
		return (free_texture_data(texture_data), NULL);
	return (texture_data);
}

t_map	*get_map(char *str, t_texture_data *texture_data)
{
	t_map	*map;
	char	*content;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (free_texture_data(texture_data), NULL);
	map->texture_data = texture_data;
	map->height = 0;
	map->length = 0;
	content = read_map_data(str, map);
	if (!content)
		return (free_texture_data(texture_data),
			free(map), NULL);
	map->arr = new_2d_int_arr(map->height, map->length);
	if (!map->arr)
		return (free_texture_data(texture_data),
			free(map), free(content), NULL);
	if (fill_map(content, map))
		return (free_texture_data(texture_data),
			free(content), free_map(map), NULL);
	if (!is_wall_enclosed(content, map))
		return (free_texture_data(texture_data),
			free(content), free_map(map), NULL);
	free(content);
	return (map);
}

t_map	*parse_map(int fd)
{
	t_map			*map;
	t_texture_data	*texture_data;
	char			*str;
	
	str = read_file(fd);
	if (!str)
		return (NULL);
	texture_data = get_texture_data(str);
	if (!texture_data)
		return (free(str), NULL);
	map = get_map(str, texture_data);
	free(str);
	if (!map)
		return (NULL);
	close(fd);
	return (map);
}
