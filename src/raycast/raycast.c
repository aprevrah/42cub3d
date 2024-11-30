/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:49:42 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/30 17:41:41 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	smart_is_wall(t_map *map, t_dvec2 intersection, bool horizontal)
{
	int	x;
	int	y;

	x = (int)intersection.x;
	y = (int)intersection.y;
	if (x < 0 || y < 0 || x >= map->length || y >= map->height)
		return (1);
	if (!horizontal)
	{
		if (!map->arr[y][x] || (x - 1 >= 0 && !map->arr[y][x - 1]))
			return (1);
	}
	else
	{
		if (!map->arr[y][x] || (y - 1 >= 0 && !map->arr[y - 1][x]))
			return (1);
	}
	return (0);
}

void	ray_cal_hit_and_dir(t_ray *ray)
{
	if (ray->delta.y == 0 || (ray->delta.x != 0
			&& squared_distance(ray->start_pos, ray->horizontal_intersection)
			>= squared_distance(ray->start_pos, ray->vertical_intersection)))
	{
		ray->hit_pos = ray->vertical_intersection;
		if (ray->sign.x == 1)
			ray->texture = WEST;
		else
			ray->texture = EAST;
	}
	else
	{
		ray->hit_pos = ray->horizontal_intersection;
		if (ray->sign.y == 1)
			ray->texture = NORTH;
		else
			ray->texture = SOUTH;
	}
}

void	rayloop(t_ray *ray, t_map *map)
{
	int	i;

	i = 0;
	while (i < MAX_RAY && (!ray->hori_hit || !ray->vert_hit))
	{
		if (!ray->vert_hit && ray->delta.x && smart_is_wall(map,
				ray->vertical_intersection, false))
			ray->vert_hit = true;
		if (!ray->vert_hit && ray->delta.x)
		{
			ray->vertical_intersection.x += ray->sign.x;
			ray->vertical_intersection.y += fabs(ray->delta.y) * ray->sign.y;
		}
		if (!ray->hori_hit && ray->delta.y && smart_is_wall(map,
				ray->horizontal_intersection, true))
			ray->hori_hit = true;
		if (!ray->hori_hit && ray->delta.y)
		{
			ray->horizontal_intersection.x += fabs(ray->delta.x) * ray->sign.x;
			ray->horizontal_intersection.y += ray->sign.y;
		}
		i++;
	}
}

t_ray	raycast(t_player player, t_map *map, double angle)
{
	t_ray	ray;

	ray.start_pos = player.position;
	ray.angle = angle;
	set_sign(&ray);
	ray.delta.x = get_dx(angle);
	ray.delta.y = get_dy(angle);
	ray.vertical_intersection = get_vertical_intersection(ray);
	ray.horizontal_intersection = get_horizontal_intersection(ray);
	ray.vert_hit = false;
	ray.hori_hit = false;
	rayloop(&ray, map);
	ray_cal_hit_and_dir(&ray);
	return (ray);
}
