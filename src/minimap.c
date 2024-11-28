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
void	nice_rect(t_data *data, t_ivec2 p1, t_ivec2 p2)
{
	int x;
	int y;

	y = p1.y;
	while (y < p2.y)
	{
		x = p1.x;
		while (x < p2.x)
		{
			if (x > 50 && y > 50 && x < 500 && y < 500)
				my_mlx_pixel_put(data, x, y, 0x3000);
			x++;
		}
		y++;
	}
}

void	render_minimap(t_data *data)
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
				nice_rect(data, (t_ivec2){(x - data->players[0].position.x) * SCALE + 100, (y - data->players[0].position.y )* SCALE + 100}, (t_ivec2){(x
						+ 1 - data->players[0].position.x) * SCALE + 100, (y + 1 - data->players[0].position.y) * SCALE + 100});
			x++;
		}
		x = 0;
		y++;
	}
}
*/



#include <math.h>



typedef struct s_rect
{
    t_ivec2 start;  // Starting coordinates of the rectangle
    t_ivec2 end;    // Ending coordinates of the rectangle
    int color;      // Color of the rectangle
} t_rect;



typedef struct s_minimap
{
    int size;           // Width and height of the minimap in pixels
    int scale;          // Number of pixels per map unit
    int player_x;       // Player's x position on the minimap (always center)
    int player_y;       // Player's y position on the minimap (always center)
    double offset_x;    // Player's floating-point x position in the map
    double offset_y;    // Player's floating-point y position in the map
} t_minimap;


void draw_rectangle(t_data *data, t_rect rect)
{
    int x;
    int y;

    y = rect.start.y;
    while (y < rect.end.y)
    {
        x = rect.start.x;
        while (x < rect.end.x)
        {
            if (x >= 0 && y >= 0 && x < W_WIDTH && y < W_HEIGHT)
            {
                my_mlx_pixel_put(data, x, y, rect.color);
            }
            x++;
        }
        y++;
    }
}

void render_minimap(t_data *data)
{
    t_minimap minimap;
    t_map *map;
    int x;
    int y;
    t_rect tile_rect;
    t_rect player_rect;
    double screen_x;
    double screen_y;

    minimap.size = 200;
    minimap.scale = 10;
    minimap.player_x = minimap.size / 2;
    minimap.player_y = minimap.size / 2;
    minimap.offset_x = data->players[0].position.x;
    minimap.offset_y = data->players[0].position.y;

    map = data->map;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->length)
        {
            screen_x = (x - minimap.offset_x) * minimap.scale + minimap.player_x;
            screen_y = (y - minimap.offset_y) * minimap.scale + minimap.player_y;
            tile_rect.start = (t_ivec2){(int)screen_x, (int)screen_y};
            tile_rect.end = (t_ivec2){(int)(screen_x + minimap.scale), (int)(screen_y + minimap.scale)};
            if (map->arr[y][x] != 0)
                tile_rect.color = 0xFFFFFF;
            else
                tile_rect.color = 0x0000FF;
            draw_rectangle(data, tile_rect);

            x++;
        }
        y++;
    }
    player_rect.start = (t_ivec2){minimap.player_x - minimap.scale / 4, minimap.player_y - minimap.scale / 4};
    player_rect.end = (t_ivec2){minimap.player_x + minimap.scale / 4, minimap.player_y + minimap.scale / 4};
    player_rect.color = 0xFF0000; // Player color

    draw_rectangle(data, player_rect);
}

