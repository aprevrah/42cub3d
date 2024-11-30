/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:19:23 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/30 21:08:30 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_dvec2	get_horizontal_intersection(t_ray ray)
{
	t_dvec2	intersection;
	t_dvec2	d;
	t_dvec2	position;

	position = ray.start_pos;
	if (ray.angle == 0 || ray.angle == PI)
	{
		intersection.x = position.x;
		intersection.y = floor(position.y) + (ray.sign.y - 1) / 2;
		return (intersection);
	}
	if (ray.sign.y == -1)
		d = (t_dvec2){get_fract_part(position.y) / fabs(tan(ray.angle)),
			get_fract_part(position.y)};
	else
		d = (t_dvec2){((1 - get_fract_part(position.y)) / fabs(tan(ray.angle))),
			1 - get_fract_part(position.y)};
	if (ray.angle == PI / 2 || ray.angle == 3 * PI / 2)
		intersection.x = ray.start_pos.x;
	else
		intersection.x = ray.start_pos.x + ray.sign.x * d.x;
	intersection.y = ray.start_pos.y + ray.sign.y * d.y;
	return (intersection);
}

t_dvec2	get_vertical_intersection(t_ray ray)
{
	t_dvec2	intersection;
	t_dvec2	d;
	t_dvec2	position;

	position = ray.start_pos;
	if (ray.angle == PI / 2 || ray.angle == (3 * PI / 2))
	{
		intersection.x = floor(position.x) + (ray.sign.x - 1) / 2;
		intersection.y = position.y;
		return (intersection);
	}
	if (ray.sign.x == -1)
		d = (t_dvec2){get_fract_part(position.x), \
		get_fract_part(position.x) * fabs(tan(ray.angle))};
	else
		d = (t_dvec2){1 - get_fract_part(position.x), \
		((1 - get_fract_part(position.x)) * fabs(tan(ray.angle)))};
	if (ray.angle == 0 || ray.angle == PI)
		intersection.y = position.y;
	else
		intersection.y = position.y + ray.sign.y * d.y;
	intersection.x = position.x + ray.sign.x * d.x;
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
