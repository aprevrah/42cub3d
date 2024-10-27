/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:45 by aprevrha          #+#    #+#             */
/*   Updated: 2024/09/30 15:29:07 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int get_color_normalized(t_texture texture, double x, double y) 
{
	int x_pixel;
	int y_pixel;

	x = x - floor(x);
	y = y - floor(y);

	x_pixel = x * texture.img_width;
	y_pixel = y * texture.img_height;

	return(get_pixel_color(texture, x_pixel, y_pixel));
}

int get_pixel_color(t_texture texture, int x, int y) 
{
	if (x < 0 || y < 0 || x >= texture.img_width || y >= texture.img_height)
	{
    	printf("Pixel coordinates out of bounds\n");
    	return -1; // Or some other error handling
	}
	// Calculate the pixel's memory offset
	int offset = (y * texture.line_length) + (x * (texture.bits_per_pixel / 8));

	// Read the color directly from the data buffer
	int color = *(int *)(texture.addr + offset);

	return color;
}

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
