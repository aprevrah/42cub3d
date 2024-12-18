/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:23:53 by aprevrha          #+#    #+#             */
/*   Updated: 2024/10/28 15:47:19 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

t_dvec2	vec_dir(t_dvec2 dir, t_dvec2 v)
{
	t_dvec2	dir_vec;

	dir_vec.y = dir.y * v.y - dir.x * v.x;
	dir_vec.x = dir.x * v.y + dir.y * v.x;
	return (dir_vec);
}

int	is_wall_tile(t_dvec2 pos, t_map *map)
{
	double	x;
	double	y;

	x = floor(pos.x);
	y = floor(pos.y);
	if (x < 0 || y < 0 || x >= map->length || y >= map->height)
		return (0);
	if (map->arr[(int)y][(int)x])
		return (0);
	return (1);
}

void	move(t_data *data, void *args)
{
	t_move_args	*a;
	t_player	*player;
	t_dvec2		direction;
	t_dvec2		move_vec;
	t_dvec2		temp;

	a = (t_move_args *)args;
	player = a->player;
	direction = a->direction;
	move_vec = vec_dir(player->orientation, direction);
	temp.x = player->position.x + move_vec.x * player->movement_speed
		* data->delta_time;
	temp.y = player->position.y + move_vec.y * player->movement_speed
		* data->delta_time;
	if (COLLISION && is_wall_tile(temp, data->map))
		return ;
	player->position.x = temp.x;
	player->position.y = temp.y;
}

t_dvec2	vec_rotate(double angle, t_dvec2 vec)
{
	t_dvec2	rotated_vec;
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	rotated_vec.x = vec.x * cos_theta - vec.y * sin_theta;
	rotated_vec.y = vec.x * sin_theta + vec.y * cos_theta;
	return (rotated_vec);
}

void	look(t_data *data, void *args)
{
	t_look_args	*a;
	t_player	*player;
	double		rotation;

	a = (t_look_args *)args;
	player = a->player;
	rotation = a->rotation;
	player->orientation = vec_rotate(rotation * player->look_speed
			* data->delta_time, player->orientation);
}
