/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:34:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/21 23:26:34 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <string.h>

void	free_and_exit(t_data data, int code)
{
	if (data.map)
	{
		if (data.map->arr)
			free(data.map->arr);
		free(data.map);
	}
	if (data.img)
		mlx_destroy_image(data.mlx, data.img);
	if (data.win)
		mlx_destroy_window(data.mlx, data.win);
	if (data.mlx)
		free(data.mlx);
	exit(code);
}

int	close_win(int keycode, t_data *data)
{
	free_and_exit(*data, 0);
	return (0);
}


void	clear_img(t_data *data)
{
	ft_bzero(data->addr, W_HEIGHT * data->line_length);
}

int	handle_keydown(int keycode, t_data *data)
{
	printf("Keycode Recived: 0x%x\n", keycode);
	if (keycode == XK_Escape)
		free_and_exit(*data, 0);
	if (keycode == XK_w)
	{
		clear_img(data);
		data->obj_tmat = multiply_tmats(rotation_m_x(PI/8), data->obj_tmat);
		render_map(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	if (keycode == XK_s)
	{
		clear_img(data);
		data->obj_tmat = multiply_tmats(rotation_m_x(-PI/8), data->obj_tmat);
		render_map(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	if (keycode == XK_a)
	{
		clear_img(data);
		data->obj_tmat = multiply_tmats(rotation_m_y(PI/8), data->obj_tmat);
		render_map(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	if (keycode == XK_d)
	{
		clear_img(data);
		data->obj_tmat = multiply_tmats(rotation_m_y(-PI/8), data->obj_tmat);
		render_map(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (0);
}

/*
void	print_map(t_map *map)
{
	int		col;
	int		line;

	col = 0;
	line = 0;
	while(line < map->height)
	{
		while(col < map->length)
		{
			//printf(" %i", map->arr[map->length * line + col]);
			col++;
		}
		//printf("\n");
		col = 0;
		line++;
	}
}
*/
/* 
int	get_x(t_map *map, int index)
{
    return (index % map->length);
}

int	get_y(t_map *map, int index)
{
    return (index / map->length);
}

int	get_index(t_map *map, int x, int y)
{
	if (x >= 0 && x < map->length && y >= 0 && y < map->height)
        return (y * map->length + x);
	return (-1);
}
 */
/* 
t_v2	vect_multi(t_v3 point, t_v6 view, t_v2 offset)
{
	t_v2	result;
	result.x = point.x * view.x1 + point.y * view.y1 + point.z * view.z1;
	result.y = point.x * view.x2 + point.y * view.y2 + point.z * view.z2;
	result.x *= 20;
	result.y *= 20;
	result.x += offset.x;
	result.y += offset.y;
	return (result);
}
*/
/* 
t_v2	vect_multi(u_vec4 )
{
	t_ivec2	result;
	result.x = point.x * view.x1 + point.y * view.y1 + point.z * view.z1;
	result.y = point.x * view.x2 + point.y * view.y2 + point.z * view.z2;
	result.x *= 20;
	result.y *= 20;
	result.x += offset.x;
	result.y += offset.y;
	return (result);
}
 */
/*
t_vec3 normalize(t_vec3 v) 
{
    float magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

    if (magnitude != 0)
	{
        v.x /= magnitude;
        v.y /= magnitude;
        v.z /= magnitude;
    }
    return (v);
}

u_tmatrix	get_tmatrix(t_vec3 rotaxis, float rotang, t_vec3 translation)
{
	u_tmatrix	obj_tmat;

	rotaxis = normalize(rotaxis);

	float cos_theta = cos(rotang);
	float sin_theta = sin(rotang);
	float one_minus_cos_theta = 1 - cos_theta;

	obj_tmat.f.x1 = cos_theta + rotaxis.x * rotaxis.x * one_minus_cos_theta;
	obj_tmat.f.x2 = rotaxis.x * rotaxis.y * one_minus_cos_theta - rotaxis.z * sin_theta;
	obj_tmat.f.x3 = rotaxis.x * rotaxis.z * one_minus_cos_theta + rotaxis.y * sin_theta;
	obj_tmat.f.x4 = 0;

	obj_tmat.f.y1 = rotaxis.y * rotaxis.x * one_minus_cos_theta + rotaxis.z * sin_theta;
	obj_tmat.f.y2 = cos_theta + rotaxis.y * rotaxis.y * one_minus_cos_theta;
	obj_tmat.f.y3 = rotaxis.y * rotaxis.z * one_minus_cos_theta - rotaxis.x * sin_theta;
	obj_tmat.f.y4 = 0;

	obj_tmat.f.z1 = rotaxis.z * rotaxis.x * one_minus_cos_theta - rotaxis.y * sin_theta;
	obj_tmat.f.z2 = rotaxis.z * rotaxis.y * one_minus_cos_theta + rotaxis.x * sin_theta;
	obj_tmat.f.z3 = cos_theta + rotaxis.z * rotaxis.z * one_minus_cos_theta;
	obj_tmat.f.z4 = 0;

	obj_tmat.f.w1 = translation.x;
	obj_tmat.f.w2 = translation.y;
	obj_tmat.f.w3 = translation.z;
	obj_tmat.f.w4 = 1;
	return (obj_tmat);
}
*/


int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;
	float	scale;

	if (argc > 2)
		return (ft_printf("No map arg!"), 1);
	if (argv)
		//printf("av\n");

	fd = open(argv[1], O_RDONLY);
	data.map = parse_map(fd);
	close(fd);

	data.mlx = mlx_init();
	if (!data.mlx)
		return (0);
	data.win = mlx_new_window(data.mlx, W_WIDTH, W_HEIGHT, "FdF");
	if (!data.mlx)
		return (free(data.mlx), 0);
	data.img = mlx_new_image(data.mlx, W_WIDTH, W_HEIGHT);
	if (!data.mlx)
		return (mlx_destroy_window(data.mlx, data.win), free(data.mlx), 0);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	if (!data.addr)
		return (mlx_destroy_image(data.mlx, data.img), mlx_destroy_window(data.mlx, data.win), free(data.mlx), 0);
	
	scale = 40;
	data.obj_tmat = translate_m(-((data.map->length - 1)/ 2.f), -((data.map->height - 1)/ 2.f), 0.f);
	data.obj_tmat = multiply_tmats(scale_m(scale), data.obj_tmat);

	data.view_tmat = translate_m(W_WIDTH/2, W_HEIGHT/2, 0);
	


	render_map(&data);

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 2, 1L<<0, handle_keydown, &data);
	mlx_hook(data.win, 17, 0, close_win, &data);
	mlx_loop(data.mlx);
}
