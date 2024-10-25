/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:17 by aprevrha          #+#    #+#             */
/*   Updated: 2024/10/25 19:01:41 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"
#include <math.h>
#include <stdio.h>


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
	t_ivec2 ray_hit_pos_screen1;
	t_ivec2 ray_hit_pos_screen2;
	t_ivec2 ray_hit_pos_screen3;
	t_ivec2 player_pos_screen;
	t_dvec2 ray_hit_pos1;
	t_dvec2 ray_hit_pos2;
	t_dvec2 ray_hit_pos3;


	t_player player = data->players[0];

	player_pos_screen = (t_ivec2){round(player.position.x * SCALE), round(player.position.y * SCALE)};
	
	//render_rect(data, (t_ivec2){player.position.x -2, player.position.y -2}, (t_ivec2){player.position.x + 2, player.position.y + 2});
	line_put(data, player_pos_screen, (t_ivec2){round(player_pos_screen.x + player.orientation.x * 20), round(player_pos_screen.y + player.orientation.y * 20)}, 0xf7f70a);
	//draw rays 
	ray_hit_pos1 = get_intersection(player, data->map, fmod(vec2angle(player.orientation), 2*PI));
	ray_hit_pos2 = get_intersection(player, data->map, fmod(vec2angle(player.orientation) + PI/8, 2*PI));
	ray_hit_pos3 = get_intersection(player, data->map, fmod(vec2angle(player.orientation) - PI/8, 2*PI));
	
	printf("p_x = %lf, p_y = %lf\n", player.position.x, player.position.y);
	printf("orientation.x = %lf, orientation.y = %lf\n", player.orientation.x, player.orientation.y);
	

	ray_hit_pos_screen1 = (t_ivec2){ray_hit_pos1.x * SCALE, ray_hit_pos1.y * SCALE};
	line_put(data, player_pos_screen, ray_hit_pos_screen1, 0xFF0000);

	ray_hit_pos_screen2 = (t_ivec2){ray_hit_pos2.x * SCALE, ray_hit_pos2.y * SCALE};
	line_put(data, player_pos_screen, ray_hit_pos_screen2, 0x00FF00);

	ray_hit_pos_screen3 = (t_ivec2){ray_hit_pos3.x * SCALE, ray_hit_pos3.y * SCALE};
	line_put(data, player_pos_screen, ray_hit_pos_screen3, COLOR);
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
