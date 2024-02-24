/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:45 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/24 17:24:49 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <X11/keysym.h>
#include <stdlib.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > 1920 || y > 1080)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int isignum(int x)
{
	if (x > 0) 
		return (1);
	else if(x < 0)
		return (-1);
	else
		return (0);
}

int iabs(int x)
{
	return (x * isignum(x));
}

void	line_put(t_data *data, t_ivec2 a, t_ivec2 b, int color)
{
	int		i;
	int		dx;
	int		dy;
	float	m;

	dx = 0;
	dy = 0;
	dx = b.x - a.x;
	dy = b.y - a.y;
	i = 0;
	if (dx == 0)
	{
		while(i <= iabs(dy))
		{
			my_mlx_pixel_put(data, a.x, a.y + i * isignum(dy), color);
			i++;
		}
		return ;
	}
	m = fabs((float)dy / (float)dx);
	if (m <= 1.0)
	{
		while(i <= iabs(dx))
		{
			my_mlx_pixel_put(data, a.x + i * isignum(dx), a.y + m * i * isignum(dy), color);
			i++;
		}
	}
	else
	{
		while(i <= iabs(dy))
		{
			my_mlx_pixel_put(data, a.x + 1.0 / m * i * isignum(dx), a.y + i * isignum(dy), color);
			i++;
		}
	}
}