/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:19:23 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/30 17:42:11 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	squared_distance(t_dvec2 p1, t_dvec2 p2)
{
	return ((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double	get_fract_part(double x)
{
	double	int_part;
	double	frac_part;

	frac_part = modf(x, &int_part);
	return (frac_part);
}

double	vec2angle(t_dvec2 vec)
{
	double	angle;

	angle = atan2(-1 * vec.y, vec.x);
	if (angle == 0)
		return (0);
	if (angle < 0)
		angle = 2 * PI + angle;
	return (angle);
}
