/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:19:23 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/30 17:27:48 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_dvec2	get_horizontal_intersection(t_ray ray)
{
	t_dvec2	intersection;
	double	d_y;
	double	d_x;
	t_dvec2	position;

	position = ray.start_pos;
	// Use fabs to check if the difference is within a small range (epsilon)
	// ! change
	if (fabs(ray.angle - 0) < EPSILON || fabs(ray.angle - PI) < EPSILON)
	{
		intersection.x = position.x;
		intersection.y = floor(position.y) + (ray.sign.y - 1) / 2;
		return (intersection);
	}
	if (ray.sign.y == -1)
	{
		d_x = get_fract_part(position.y) / fabs(tan(ray.angle));
		d_y = get_fract_part(position.y);
	}
	else
	{
		d_x = ((1 - get_fract_part(position.y)) / fabs(tan(ray.angle)));
		d_y = 1 - get_fract_part(position.y);
	}
	if (ray.angle == PI / 2 || ray.angle == 3 * PI / 2)
		intersection.x = ray.start_pos.x;
	else
		intersection.x = ray.start_pos.x + ray.sign.x * d_x;
	intersection.y = ray.start_pos.y + ray.sign.y * d_y;
	return (intersection);
}

t_dvec2	get_vertical_intersection(t_ray ray)
{
	t_dvec2	intersection;
	double	d_x;
	double	d_y;
	t_dvec2	position;

	position = ray.start_pos;
	// Use fabs to check if the difference is within a small range (epsilon)
	// ! change
	if (fabs(ray.angle - PI / 2) < EPSILON || fabs(ray.angle - 3 * PI
			/ 2) < EPSILON)
	{
		intersection.x = floor(position.x) + (ray.sign.x - 1) / 2;
		intersection.y = position.y;
		return (intersection);
	}
	if (ray.sign.x == -1)
	{
		d_y = get_fract_part(position.x) * fabs(tan(ray.angle));
		d_x = get_fract_part(position.x);
	}
	else
	{
		d_y = ((1 - get_fract_part(position.x)) * fabs(tan(ray.angle)));
		d_x = 1 - get_fract_part(position.x);
	}
	if (ray.angle == 0 || ray.angle == PI)
		intersection.y = position.y;
	else
		intersection.y = position.y + ray.sign.y * d_y;
	intersection.x = position.x + ray.sign.x * d_x;
	return (intersection);
}

void	set_sign(t_ray *ray)
{
	if (ray->angle > PI / 2 && ray->angle < 3 * PI / 2)
		ray->sign.x = -1;
	else
		ray->sign.x = 1;
	if (ray->angle > 0 && ray->angle < PI)
		ray->sign.y = -1;
	else
		ray->sign.y = 1;
}

// flipped 1 and 0 in both functions this was 50% of the line bug,
//	~5h to find this
double	get_dx(double angle)
{
	if (angle == PI / 2 || angle == 3 * PI / 2)
		return (0);
	if (angle == 0 || angle == PI)
		return (1);
	return (1 / tan(angle));
}

double	get_dy(double angle)
{
	if (angle == PI / 2 || angle == 3 * PI / 2)
		return (1);
	if (angle == 0 || angle == PI)
		return (0);
	return (tan(angle));
}