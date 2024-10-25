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

// void	print_vec(t_tmatrix mat)
// {
// 	int	i;
// 	int	j;
// void	print_vec(t_tmatrix mat)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			printf("%.1f	", mat.arr[i + j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }
// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			printf("%.1f	", mat.arr[i + j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

// t_vec4	get_mapcoords(t_map *map, int index)
// {
// 	t_vec4	p;
// t_vec4	get_mapcoords(t_map *map, int index)
// {
// 	t_vec4	p;

// 	p.f.x = index % map->length;
// 	p.f.y = index / map->length;
// 	//p.f.z = (float)(map->arr[index]);
// 	p.f.w = 1;
// 	return (p);
// }
// 	p.f.x = index % map->length;
// 	p.f.y = index / map->length;
// 	//p.f.z = (float)(map->arr[index]);
// 	p.f.w = 1;
// 	return (p);
// }

// t_ivec2	get_sspace(t_vec4 v)
// {
// 	t_ivec2	p;
// t_ivec2	get_sspace(t_vec4 v)
// {
// 	t_ivec2	p;

// 	p.x = (int)((v.f.x));
// 	p.y = (int)((v.f.y));
// 	return (p);
// }
// 	p.x = (int)((v.f.x));
// 	p.y = (int)((v.f.y));
// 	return (p);
// }

// static void	connect_spoints(t_ivec2 *spoints, t_data *data)
// {
// 	t_map	*map;
// 	int		i;
// static void	connect_spoints(t_ivec2 *spoints, t_data *data)
// {
// 	t_map	*map;
// 	int		i;

// 	map = data->map;
// 	i = 0;
// 	while (i < map->height * map->length)
// 	{
// 		if ((i + 1) % (map->length) != 0)
// 			line_put(data, spoints[i], spoints[i + 1], COLOR);
// 		if (i < (map->height - 1) * map->length)
// 			line_put(data, spoints[i], spoints[i + map->length], COLOR);
// 		i++;
// 	}
// }
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
	//draw first ray 

	
	
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





// void	render_map(t_data *data)
// {
// 	t_ivec2		*spoints;
// 	t_tmatrix	tmat;
// 	int			i;

// 	spoints = (t_ivec2 *)malloc(sizeof(t_ivec2) * data->map->length
// 			* data->map->height);
// 	if (!spoints)
// 		free_and_exit(data, 1);
// 	tmat = multiply_tmats(data->tmatrices[0], data->tmatrices[1]);
// 	i = 0;
// 	while (i < data->map->height * data->map->length)
// 	{
// 		spoints[i] = get_sspace(left_multiply(tmat, get_mapcoords(data->map,
// 						i)));
// 		i++;
// 	}
// 	connect_spoints(spoints, data);
// 	free(spoints);
// }
// 	spoints = (t_ivec2 *)malloc(sizeof(t_ivec2) * data->map->length
// 			* data->map->height);
// 	if (!spoints)
// 		free_and_exit(data, 1);
// 	tmat = multiply_tmats(data->tmatrices[0], data->tmatrices[1]);
// 	i = 0;
// 	while (i < data->map->height * data->map->length)
// 	{
// 		spoints[i] = get_sspace(left_multiply(tmat, get_mapcoords(data->map,
// 						i)));
// 		i++;
// 	}
// 	connect_spoints(spoints, data);
// 	free(spoints);
// }
