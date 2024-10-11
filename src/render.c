/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:17 by aprevrha          #+#    #+#             */
/*   Updated: 2024/10/02 16:31:07 by aprevrha         ###   ########.fr       */
/*   Updated: 2024/10/02 16:31:07 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	render_rect(t_data *data, t_ivec2 p1, t_ivec2 p2)
{
	t_ivec2 p1_;
	t_ivec2 p2_;

	p1_.x = p1.x;
	p1_.y = p2.y;
	p2_.x = p2.x;
	p2_.y = p1.y;

	line_put(data, p1, p2, COLOR);
	line_put(data, p1, p1_, COLOR);
	line_put(data, p1, p2_, COLOR);
	line_put(data, p2, p1_, COLOR);
	line_put(data, p2, p2_, COLOR);
}
// t_dvec2 get_ray_hit(t_dvec2 start_pos, t_data *data, t_dvec2 orientation);
// {
// 	t_player player = data->players[0];
// 	tanh(orientation)
// 	ray_hit_pos = get_intersection(player.position, data->map->arr, 0);

// 	return (ray_hit_pos);
// }

void	render_players(t_data *data)
{
	// t_ivec2 ray_hit_pos_screen;
	t_ivec2 player_pos_screen;
	// t_dvec2 ray_hit_pos;
	t_player player = data->players[0];

	player_pos_screen = (t_ivec2){round(player.position.x * SCALE), round(player.position.y * SCALE)};
	
	//render_rect(data, (t_ivec2){player.position.x -2, player.position.y -2}, (t_ivec2){player.position.x + 2, player.position.y + 2});
	line_put(data, player_pos_screen, (t_ivec2){round(player_pos_screen.x + player.orientation.x * 20), round(player_pos_screen.y + player.orientation.y * 20)}, 0xf7f70a);
	//draw first ray 
	// ray_hit_pos = get_intersection(player.position, data->map->arr, atan(player.orientation.x / player.orientation.y));
	// ray_hit_pos_screen = (t_ivec2){ray_hit_pos.x * SCALE, ray_hit_pos.y * SCALE};
	// line_put(data, player_pos_screen, ray_hit_pos_screen, COLOR);
}

void	render_map(t_data *data)
{
	t_map map = *data->map;
	int x;
	int y;

	x = 0;
	y = 0;

	while (y < map.height)
	{
		while (x < map.length )
		{
			if (!map.arr[y][x])
				render_rect(data, (t_ivec2){x * SCALE, y * SCALE}, (t_ivec2){(x + 1) * SCALE, (y + 1) * SCALE});
			x++;
		}
		x = 0;
		y++;
	}
}
