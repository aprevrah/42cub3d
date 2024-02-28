/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:45 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/28 21:43:58 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= W_WIDTH || y >= W_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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

t_ivec2	niv(int x, int y)
{
	t_ivec2	v;

	v.x = x;
	v.y = y;
	return (v);
}

void	re_line(t_ivec2 *a, t_ivec2 *b, t_data *data)
{
	float	m;
	float	x_left;
	float	y_left;
	float	x_right;
	float	y_right;
	float	y_top;
	float	x_top;
	float	y_bottom;
	float	x_bottom;

	// Calculate the slope of the line segment
	m = (float)(b->y - a->y) / (b->x - a->x);
	// Calculate the intersection points with the screen boundaries
	x_left = 10;
	y_left = a->y + m * (x_left - a->x);
	x_right = (W_WIDTH - 10) - 1;
	y_right = a->y + m * (x_right - a->x);
	y_top = 10;
	x_top = a->x + (y_top - a->y) / m;
	y_bottom = (W_HEIGHT - 10) - 1;
	x_bottom = a->x + (y_bottom - a->y) / m;
	// Find the intersection point inside the screen boundaries
	float intersection_x, intersection_y;
	if (0 <= x_top && x_top < W_WIDTH)
	{
		intersection_x = x_top;
		intersection_y = y_top;
	}
	else if (0 <= x_bottom && x_bottom < W_WIDTH)
	{
		intersection_x = x_bottom;
		intersection_y = y_bottom;
	}
	else if (0 <= y_left && y_left < W_HEIGHT)
	{
		intersection_x = x_left;
		intersection_y = y_left;
	}
	else if (0 <= y_right && y_right < W_HEIGHT)
	{
		intersection_x = x_right;
		intersection_y = y_right;
	}
	else
	{
		// No intersection point inside the screen boundaries
		return ;
	}
	// Draw a line between the intersection point and one of the endpoints of the line segment
	draw_straight(data, niv(a->x, a->y), niv((int)intersection_x,
			(int)intersection_y), 0x00FFFF01);
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
	re_line(&a, &b, data);
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
/*
void	re_line(t_ivec2 *a, t_ivec2 *b)
{
	int		i;
	int		dx;
	int		dy;
	float	m;
	int		x0;
	int		y0;
	int		xw;
	int		yh;
	int		dx;
	int		dy;
	float	m;
	int		y0;
	int		x0;
	int		yh;
	int		xw;
	int		dx;
	int		dy;
	float	m;
	int		x0;
	int		y0;
	int		xw;
	int		yh;

	dx = b->x - a->x;
	dy = b->y - a->y;
	m = (float)dy / (float)dx;
	// Y = m * X + (a.y - m * a.x)
	y0 = m * 0 + (a->y - m * a->x);
	// X = (Y - (a.y - m * a.x)))/m
	x0 = (0 - (a->y - m * a->x)) / m;
	// Y = m * X + (a.y - m * a.x)
	yh = m * W_WIDTH + (a->y - m * a->x);
	// X = (Y - (a.y - m * a.x)))/m
	xw = (W_HEIGHT - (a->y - m * a->x)) / m;
	if (y0 > 0 && y0 < W_HEIGHT)
	{
		if (a->x < 0 || a->y < 0 || a->x >= W_WIDTH || a->y >= W_HEIGHT)
		{
			a->x = 0;
			a->y = y0;
		}
		printf("%iy0\n", y0);
	}
	if (x0 > 0 && x0 < W_WIDTH)
		printf("%ix0\n", x0);
	if (yh > 0 && yh < W_HEIGHT)
		printf("%iy0\n", yh);
	if (xw > 0 && xw < W_WIDTH)
		printf("%ixw\n", xw);
} */