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
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	get_color_normalized(t_texture texture, double x, double y)
{
	int	x_pixel;
	int	y_pixel;

	x = x - floor(x);
	y = y - floor(y);
	x_pixel = x * texture.img_width;
	y_pixel = y * texture.img_height;
	return (get_pixel_color(texture, x_pixel, y_pixel));
}

// maybe improve error handling
int	get_pixel_color(t_texture texture, int x, int y)
{
	int	offset;
	int	color;

	if (x < 0 || y < 0 || x >= texture.img_width || y >= texture.img_height)
	{
		printf("Pixel coordinates out of bounds\n");
		return (-1);
	}
	offset = (y * texture.line_length) + (x * (texture.bits_per_pixel / 8));
	color = *(int *)(texture.addr + offset);
	return (color);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= W_WIDTH || y >= W_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
