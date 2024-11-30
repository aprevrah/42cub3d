/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:17 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/30 21:30:29 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	line_length(t_dvec2 a, t_dvec2 b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

void	render_vertical_line(t_data *data, double angle, int x, double angle2)
{
	t_ray	ray;
	t_slice	slice;
	double	distance;

	ray = raycast(data->players[0], data->map, fmod(angle, 2 * PI));
	distance = line_length(ray.start_pos, ray.hit_pos);
	distance = cos(angle2) * distance;
	slice.size = (double)1 / distance;
	if (ray.texture == NORTH)
		slice.d_x = 1 - ray.hit_pos.x;
	if (ray.texture == EAST)
		slice.d_x = 1 - ray.hit_pos.y;
	if (ray.texture == SOUTH)
		slice.d_x = ray.hit_pos.x;
	if (ray.texture == WEST)
		slice.d_x = ray.hit_pos.y;
	slice.texture = data->map->texture_data->textures[ray.texture];
	slice.x = x;
	slice_put(data, slice);
}

void	render_walls(t_data *data)
{
	int		w_offset;
	double	a_offset;

	w_offset = 0;
	while (w_offset < W_WIDTH)
	{
		a_offset = atan(tan(PI / 4) * ((W_WIDTH / 2) - (double)w_offset)
				/ (W_WIDTH / 2));
		render_vertical_line(data, vec2angle(data->players[0].orientation)
			+ a_offset, w_offset, a_offset);
		w_offset++;
	}
}

/*
void	render_walls(t_data *data)
{
	int		w_offset;
	double	a_offset;

	w_offset = 0;
	a_offset = 0;
	//double half_fov = 1.0472 / 2;
	render_vertical_line(data, vec2angle(data->players[0].orientation)
		+ a_offset, W_WIDTH/2 + w_offset, a_offset);
	while (w_offset <= W_WIDTH/2)
	{
		// a_offset = atan((double)w_offset / (W_WIDTH / 2)) * half_fov;
		a_offset = atan(tan(PI/4) * w_offset / (W_WIDTH / 2));
		render_vertical_line(data, vec2angle(data->players[0].orientation)
			- a_offset, W_WIDTH/2 + w_offset, a_offset);
		render_vertical_line(data, vec2angle(data->players[0].orientation)
			+ a_offset, W_WIDTH/2 - w_offset, a_offset);
		//a_offset += 1.0472/960;
		w_offset++;
	}
	// int col;
	// col = 0;
	// while (col <= W_WIDTH)
	// {
	// 	a_offset = atan(tan(PI/4) * w_offset / (W_WIDTH / 2));
	// 	render_vertical_line(data, col);
	// 	w_offset++;
	// 	col++;
	// }
}
*/
