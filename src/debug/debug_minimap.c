/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:17 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/30 16:05:50 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_rect(t_data *data, t_ivec2 p1, t_ivec2 p2)
{
	t_ivec2	p1_;
	t_ivec2	p2_;

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

void	render_minimap_ray(t_data *data, double angle)
{
	t_dvec2		ray_hit_pos;
	t_ivec2		ray_hit_pos_screen;
	t_ivec2		player_pos_screen;
	t_player	player;

	player = data->players[0];
	ray_hit_pos = raycast(player, data->map, fmod(angle, 2 * PI)).hit_pos;
	ray_hit_pos_screen = (t_ivec2){ray_hit_pos.x * SCALE, ray_hit_pos.y
		* SCALE};
	player_pos_screen = (t_ivec2){round(player.position.x * SCALE),
		round(player.position.y * SCALE)};
	line_put(data, player_pos_screen, ray_hit_pos_screen, 0xff6289);
}

void	render_minimap_rays(t_data *data)
{
	int		w_offset;
	double	a_offset;

	w_offset = 0;
	a_offset = 0;
	while (w_offset <= W_WIDTH / 2)
	{
		a_offset = atan(tan(PI / 4) * w_offset / ((double)W_WIDTH / 2));
		render_minimap_ray(data, vec2angle(data->players[0].orientation)
			+ a_offset);
		render_minimap_ray(data, vec2angle(data->players[0].orientation)
			- a_offset);
		w_offset++;
	}
}

void	render_map(t_data *data)
{
	t_map	map;
	int		x;
	int		y;

	map = *data->map;
	x = 0;
	y = 0;
	while (y < map.height)
	{
		while (x < map.length)
		{
			if (!map.arr[y][x])
				render_rect(data, (t_ivec2){x * SCALE, y * SCALE}, (t_ivec2){(x
						+ 1) * SCALE, (y + 1) * SCALE});
			x++;
		}
		x = 0;
		y++;
	}
}

/*
void	render_players(t_data *data)
{
	t_ivec2		ray_hit_pos_screen1;
	t_ivec2		ray_hit_pos_screen2;
	t_ivec2		ray_hit_pos_screen3;
	t_ivec2		player_pos_screen;
	t_dvec2		ray_hit_pos1;
	t_dvec2		ray_hit_pos2;
	t_dvec2		ray_hit_pos3;
	t_player	player;

	player = data->players[0];
	player_pos_screen = (t_ivec2){round(player.position.x * SCALE),
		round(player.position.y * SCALE)};
	line_put(data, player_pos_screen, (t_ivec2){round(player_pos_screen.x
			+ player.orientation.x * 20), round(player_pos_screen.y
			+ player.orientation.y * 20)}, 0xf7f70a);
	ray_hit_pos1 = raycast(player, data->map,
			fmod(vec2angle(player.orientation), 2 * PI)).hit_pos;
	ray_hit_pos2 = raycast(player, data->map, fmod(vec2angle(player.orientation)
				+ PI / 8, 2 * PI)).hit_pos;
	ray_hit_pos3 = raycast(player, data->map, fmod(vec2angle(player.orientation)
				- PI / 8, 2 * PI)).hit_pos;
	ray_hit_pos_screen1 = (t_ivec2){ray_hit_pos1.x * SCALE, ray_hit_pos1.y
		* SCALE};
	line_put(data, player_pos_screen, ray_hit_pos_screen1, 0xFF0000);
	ray_hit_pos_screen2 = (t_ivec2){ray_hit_pos2.x * SCALE, ray_hit_pos2.y
		* SCALE};
	line_put(data, player_pos_screen, ray_hit_pos_screen2, 0x00FF00);
	ray_hit_pos_screen3 = (t_ivec2){ray_hit_pos3.x * SCALE, ray_hit_pos3.y
		* SCALE};
	line_put(data, player_pos_screen, ray_hit_pos_screen3, COLOR);
}
*/
