/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:17 by aprevrha          #+#    #+#             */
/*   Updated: 2024/10/28 16:46:35 by tmeniga@stu      ###   ########.fr       */
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



// void	render_floor_ceiling(t_data *data)
// {
		
// }



void render_half_screen(t_data *data)
{
    int x;
	int y;

	x = 0;
	y = 0;
	while(y < W_HEIGHT / 2)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			my_mlx_pixel_put(data, x, y, 0x011f4b);
			x++;
		}
		y++;
	}
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			my_mlx_pixel_put(data, x, y, 0x355e3b);
			x++;
		}
		y++;
	}
}

double line_length(t_dvec2 a, t_dvec2 b)
{
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

// void	render_vertical_line(t_data *data , double angle, int width, double angle2)
// {
// 	t_dvec2		ray_hit_pos;
// 	double		distance;
// 	double		d_x;
// 	double		offset;
	


// 	ray_hit_pos = get_intersection(data->players[0], data->map, fmod(angle,2*PI));
// 	distance = line_length(data->players[0].position, ray_hit_pos);
// 	distance = cos(angle2) * distance;
// 	// if (distance < 1)
// 		// distance = 1;
// 	offset = (double) 1/distance;
// 	//offset = (double)W_HEIGHT / (distance * 2);
// 	// if (offset > (double)W_HEIGHT/2)
// 	// 	offset = (double)W_HEIGHT/2;
	
// 	if (floor(ray_hit_pos.y) == ray_hit_pos.y)
// 	{
// 		d_x = ray_hit_pos.x;
// 		slice_put(data, width, offset, d_x, data->map->texture_data->textures[0]);
// 	}
// 	else {
// 		d_x = ray_hit_pos.y;
// 		slice_put(data, width, offset, d_x, data->map->texture_data->textures[1]);
// 	}
// }

void	render_vertical_line(t_data *data , double angle, int width, double angle2)
{
	t_dvec2		ray_hit_pos;
	double		distance;
	t_dvec2		a;
	t_dvec2		b;
	t_ivec2		a_screen;
	t_ivec2		b_screen;
	double		offset;
	


	ray_hit_pos = get_intersection(data->players[0], data->map, fmod(angle,2*PI));
	distance = line_length(data->players[0].position, ray_hit_pos);
	distance = cos(angle2) * distance;
	// if (distance < 1)
		// distance = 1;
	offset = (double)W_HEIGHT / (distance * 2);
	if (offset > (double)W_HEIGHT/2)
		offset = (double)W_HEIGHT/2;
	
	a.x = (double)width;
	a.y = (double)W_HEIGHT/2 - offset;
	a_screen = (t_ivec2){a.x, a.y};

	b.x = (double)width;
	b.y = (double)W_HEIGHT/2 + offset;
	b_screen = (t_ivec2){b.x, b.y};
	
	if (a.y < 0 || a.y > W_HEIGHT || b.y < 0 || b.y > W_HEIGHT)
	{
		printf("aaaaaaaaaaaaaaaaaaaa\n");	
		return ;
	}
	line_put(data, a_screen, b_screen, 0xd7c6cf);
}


void	render_walls(t_data *data)
{
	int w_offset;
	double a_offset;

	
	w_offset = 0;
	a_offset = 0; 

	//double half_fov = 1.0472 / 2;

	render_vertical_line(data, vec2angle(data->players[0].orientation) + a_offset, W_WIDTH/2 + w_offset, a_offset);
	
	
	while (w_offset <= W_WIDTH/2)
	{
		// a_offset = atan((double)w_offset / (W_WIDTH / 2)) * half_fov;
		a_offset = atan(tan(PI/4) * w_offset / (W_WIDTH / 2));

		render_vertical_line(data, vec2angle(data->players[0].orientation) - a_offset, W_WIDTH/2 + w_offset, a_offset);
		render_vertical_line(data, vec2angle(data->players[0].orientation) + a_offset, W_WIDTH/2 - w_offset, a_offset);
		//a_offset += 1.0472/960;
		w_offset++;
	}	
}

void	render_wall(t_data *data)
{
	t_dvec2		ray_hit_pos;
	t_player	player = data->players[0];
	double		distance;
	t_dvec2		a;
	t_dvec2		b;
	t_ivec2		a_screen;
	t_ivec2		b_screen;
	double		offset;
	int i;

	i = 0;
	double angle_offset = 0.0007;
	while (i < W_WIDTH) 
	{
	ray_hit_pos = get_intersection(player, data->map,  fmod(vec2angle(player.orientation) - PI/6.5  + i * angle_offset  , 2*PI));
	distance = line_length(player.position, ray_hit_pos);

	offset = (double)W_HEIGHT / (distance * 2);
	
	//offset = (double)W_HEIGHT/4;
	
	a.x = (double)i;
	a.y = (double)W_HEIGHT/2 - offset;
	//printf("a.x = %lf a.y = %lf\n", a.x, a.y);
	a_screen = (t_ivec2){a.x, a.y};

	b.x = (double)i;
	b.y = (double)W_HEIGHT/2 + offset;
	//printf("b.x = %lf b.y = %lf\n", b.x, b.y);
	b_screen = (t_ivec2){b.x, b.y};
	
	//printf("a = %i %i b = %i %i\n", a_screen.x, a_screen.y, b_screen.x, b_screen.y);
	line_put(data, a_screen, b_screen, 0xd7c6cf);
	i++;
	}
}

void	render_minimap_ray(t_data *data, double angle)
{
	t_dvec2 ray_hit_pos;
	t_ivec2 ray_hit_pos_screen;
	t_ivec2 player_pos_screen;
	
	t_player player = data->players[0];
	ray_hit_pos = get_intersection(player, data->map, fmod(angle, 2*PI));
	ray_hit_pos_screen = (t_ivec2){ray_hit_pos.x * SCALE, ray_hit_pos.y * SCALE};
	player_pos_screen = (t_ivec2){round(player.position.x * SCALE), round(player.position.y * SCALE)};

	line_put(data, player_pos_screen, ray_hit_pos_screen, 0xff6289);
}


void	render_minimap_rays(t_data *data)
{
	int w_offset;
	double a_offset;
	
	w_offset = 0;
	a_offset = 0; 
		
	while (w_offset <= W_WIDTH/2)
	{
		a_offset = atan(tan(PI/4) * w_offset / ((double)W_WIDTH / 2));
		render_minimap_ray(data, vec2angle(data->players[0].orientation) + a_offset);
		render_minimap_ray(data, vec2angle(data->players[0].orientation) - a_offset);
		w_offset++;
	}	
}


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
	
	// printf("p_x = %lf, p_y = %lf\n", player.position.x, player.position.y);
	// printf("orientation.x = %lf, orientation.y = %lf\n", player.orientation.x, player.orientation.y);
	

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
