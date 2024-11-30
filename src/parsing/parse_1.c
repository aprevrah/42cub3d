/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:06 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/30 20:40:19 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


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
		return (get_next_line(fd, 1), free_texture_data(texture_data),
			free(map), NULL);
	map->arr = new_2d_int_arr(map->height, map->length);
	if (!map->arr)
		return (get_next_line(fd, 1), free_texture_data(texture_data),
			free(map), free(content), NULL);
	if (fill_map(content, map))
		return (get_next_line(fd, 1), free_texture_data(texture_data),
			free(content), free_map(map), NULL);
	if (!is_wall_enclosed(content, map))
		return (get_next_line(fd, 1), free_texture_data(texture_data),
			free(content), free_map(map), NULL);
	free(content);
	return (map);
}

t_map	*parse_map(int fd)
{
	t_map			*map;
	t_texture_data	*texture_data;

	texture_data = get_texture_data(fd);
	if (!texture_data)
		return (NULL);
	map = get_map(fd, texture_data);
	if (!map)
		return (NULL);
	close(fd);
	return (map);
}
