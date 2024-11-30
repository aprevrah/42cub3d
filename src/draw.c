/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:45 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/30 21:30:50 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	slice_put(t_data *data, t_slice slice)
{
	int	color;
	int	i;
	int	y;

	i = 0;
	if (slice.size > 1)
		i = -(W_HEIGHT * 0.5 - W_HEIGHT * 0.5 * slice.size);
	y = 0;
	while (y < W_HEIGHT)
	{
		if (y < W_HEIGHT * 0.5 - W_HEIGHT * 0.5 * slice.size)
			my_mlx_pixel_put(data, slice.x, y, data->map->texture_data->col_c);
		else if (y > W_HEIGHT * 0.5 + W_HEIGHT * 0.5 * slice.size)
			my_mlx_pixel_put(data, slice.x, y, data->map->texture_data->col_f);
		else
		{
			color = get_color_normalized(slice.texture, slice.d_x, i / (W_HEIGHT
						* slice.size));
			my_mlx_pixel_put(data, slice.x, y, color);
			i++;
		}
		y++;
	}
}
/* OPTIMIZATION maybe improve this somehow and use it,
	main problem are bigger textures
void	slice_put(t_data *data, int x, double size, double d_x,
		t_texture texture)
{
	bool	got_color;
	int		color;
	int		i;
	int		y;

	i = 0;
	if (size > 1)
		i = -(W_HEIGHT*0.5 - W_HEIGHT*0.5 *size);
	got_color = false;
	y = 0;
	while(y < W_HEIGHT)
	{
		if (y < W_HEIGHT*0.5 - W_HEIGHT*0.5 * size)
			my_mlx_pixel_put(data, x, y, data->map->texture_data->col_c);
		else if (y > W_HEIGHT*0.5 + W_HEIGHT*0.5 * size)
			my_mlx_pixel_put(data, x, y, data->map->texture_data->col_f);
		else
		{
			// we only want to get the new color
			// if there is a new pixel in the texture
			// 1 optimization off, 0 optimization on
			if (1 || fmod(i, ((W_HEIGHT * size)/texture.img_height)) < 1
				|| !got_color)
			{
				color = get_color_normalized(texture, d_x, i/(W_HEIGHT * size));
				got_color = true;
			}
			my_mlx_pixel_put(data, x, y, color);
			// if (fmod(i, ((W_HEIGHT * size)/texture.img_height)) < 1)
			// 	my_mlx_pixel_put(data, x, y, 0x00FF60);
			// if ((divisor > 0 && i % divisor == 0))
			// 	my_mlx_pixel_put(data, x, y, 0xFF8000);
			i++;
		}
		y++;
	}
}
*/
