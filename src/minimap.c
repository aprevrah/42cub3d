/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:17 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/20 12:03:29 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>
#include <stdio.h>

void	draw_rectangle(t_data *data, t_rect rect, t_rect bounds)
{
	int	x;
	int	y;

	y = rect.start.y;
	while (y < rect.end.y)
	{
		x = rect.start.x;
		while (x < rect.end.x)
		{
			if (x >= 0 && y >= 0 && x < W_WIDTH && y < W_HEIGHT)
			{
				if (bounds.start.x <= x && bounds.start.y <= y
					&& bounds.end.x > x && bounds.end.y > y)
					my_mlx_pixel_put(data, x, y, rect.color);
			}
			x++;
		}
		y++;
	}
}

void	render_tiles(t_data *data, t_minimap minimap, t_rect map_rect)
{
	t_ivec2	i;
	t_rect	tile_rect;
	double	sx;
	double	sy;

	i.y = 0;
	while (i.y < data->map->height)
	{
		i.x = 0;
		while (i.x < data->map->length)
		{
			sx = (i.x - minimap.offset_x) * minimap.scale + minimap.player_x;
			sy = (i.y - minimap.offset_y) * minimap.scale + minimap.player_y;
			tile_rect.start = (t_ivec2){(int)sx, (int)sy};
			tile_rect.end = (t_ivec2){(int)(sx + minimap.scale), (int)(sy
					+ minimap.scale)};
			if (data->map->arr[i.y][i.x] != 0)
				tile_rect.color = 0xFFFFFF;
			else
				tile_rect.color = 0x0000FF;
			draw_rectangle(data, tile_rect, map_rect);
			i.x++;
		}
		i.y++;
	}
}

void	render_minimap(t_data *data)
{
	t_minimap	minimap;
	t_rect		player_rect;
	t_rect		map_rect;

	minimap.size = 200;
	minimap.scale = 10;
	minimap.player_x = minimap.size / 2;
	minimap.player_y = minimap.size / 2;
	minimap.offset_x = data->players[0].position.x;
	minimap.offset_y = data->players[0].position.y;
	map_rect.start = (t_ivec2){0, 0};
	map_rect.end = (t_ivec2){minimap.size, minimap.size};
	map_rect.color = 0x0000FF;
	draw_rectangle(data, map_rect, map_rect);
	render_tiles(data, minimap, map_rect);
	player_rect.start = (t_ivec2){minimap.player_x - minimap.scale / 4,
		minimap.player_y - minimap.scale / 4};
	player_rect.end = (t_ivec2){minimap.player_x + minimap.scale / 4,
		minimap.player_y + minimap.scale / 4};
	player_rect.color = 0xFF0000;
	draw_rectangle(data, player_rect, map_rect);
}
