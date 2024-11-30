/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:03:08 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/30 20:48:56 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <mlx.h>

void	free_2d_arr(void **arr, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_texture_data(t_texture_data *td)
{
	free(td->path_no);
	free(td->path_ea);
	free(td->path_so);
	free(td->path_we);
	free(td);
}

void	free_map(t_map *map)
{
	free_2d_arr((void **)map->arr, map->height);
	free(map);
}

void	destroy_textures(t_data *data)
{
	if (data->map->texture_data->textures[0].img)
		mlx_destroy_image(data->mlx, data->map->texture_data->textures[0].img);
	if (data->map->texture_data->textures[1].img)
		mlx_destroy_image(data->mlx, data->map->texture_data->textures[1].img);
	if (data->map->texture_data->textures[2].img)
		mlx_destroy_image(data->mlx, data->map->texture_data->textures[2].img);
	if (data->map->texture_data->textures[3].img)
		mlx_destroy_image(data->mlx, data->map->texture_data->textures[3].img);
}

void	free_and_exit(t_data *data, int code)
{
	if (data->players)
		free(data->players);
	get_next_line(data->fd, 1);
	if (data->mlx && data->map->texture_data)
		destroy_textures(data);
	if (data->map)
	{
		free_texture_data(data->map->texture_data);
		free_map(data->map);
	}
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(code);
}
