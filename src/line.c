/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:45 by aprevrha          #+#    #+#             */
/*   Updated: 2024/10/28 13:00:22 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	isignum(int x)
{
	if (x > 0)
		return (1);
	else if (x < 0)
		return (-1);
	else
		return (0);
}

int	iabs(int x)
{
	return (x * isignum(x));
}

void	draw_straight(t_data *data, t_ivec2 a, t_ivec2 b, int color)
{
	int		i;
	int		dx;
	int		dy;
	float	m;

	dx = b.x - a.x;
	dy = b.y - a.y;
	m = fabs((float)dy / (float)dx);
	i = -1;
	if (m <= 1.0)
		while (++i <= iabs(dx))
			my_mlx_pixel_put(data, a.x + i * isignum(dx), a.y + m * i
				* isignum(dy), color);
	else
		while (++i <= iabs(dy))
			my_mlx_pixel_put(data, a.x + 1.0 / m * i * isignum(dx), a.y + i
				* isignum(dy), color);
}

void	line_put(t_data *data, t_ivec2 a, t_ivec2 b, int color)
{
	int	i;
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	dx = b.x - a.x;
	dy = b.y - a.y;
	if (a.x == b.x && a.y == b.y)
	{
		my_mlx_pixel_put(data, a.x, a.y, color);
		return ;
	}
	i = 0;
	if (dx == 0)
	{
		while (i <= iabs(dy))
		{
			my_mlx_pixel_put(data, a.x, a.y + i * isignum(dy), color);
			i++;
		}
		return ;
	}
	draw_straight(data, a, b, color);
}
