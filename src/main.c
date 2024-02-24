/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:34:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/24 18:10:24 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <string.h>

# include <mlx.h>
# include <X11/X.h>



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

int	win_close_button(int keycode, t_data *data)
{
	free_and_exit(*data, 0);
	return (0);
}


void	clear_img(t_data *data)
{
	ft_bzero(data->addr, W_HEIGHT * data->line_length);
}

int	init_keys(t_keys *keys)
{
	int i;
	
	keys->codes[0] = XK_w;
	keys->oper[0].func = rot_x; keys->oper[0].value = 1; keys->oper[0].matrix = 'o';
	keys->codes[1] = XK_s;
	keys->oper[1].func = rot_x; keys->oper[1].value = -1; keys->oper[1].matrix = 'o';
	keys->codes[0] = XK_a;
	keys->oper[2].func = rot_y; keys->oper[2].value = 1; keys->oper[2].matrix = 'o';
	keys->codes[3] = XK_d;
	keys->oper[3].func = rot_y; keys->oper[3].value = -1; keys->oper[3].matrix = 'o';
	
	i = 0;
	while(i < NUM_OF_KEYS)
	{
		keys->state[i] = 0;
		i++;
	}
}

int	handle_keydown(int keycode, t_data *data)
{
	int i;
	
	i = 0;
	while(i < NUM_OF_KEYS)
	{
		if(data->keys.codes[i] == keycode)
		{
			data->keys.state[i] = 1;
			break ;
		}
		i++;
	}
	return (0);
}

int	handle_keyup(int keycode, t_data *data)
{
	int i;
	
	i = 0;
	while(i < NUM_OF_KEYS)
	{
		if(data->keys.codes[i] == keycode)
		{
			data->keys.state[i] = 0;
			break ;
		}
		i++;
	}
	return (0);
}

/* int	handle_keydown(int keycode, t_data *data)
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
} */

loop_hook(t_data *data)
{
	int i;
	int keys_pressed;
	
	keys_pressed = 0;
	i = 0;
	while (i < NUM_OF_KEYS)
	{
		if (data->keys.state[i] == 1)
		{
			(data->keys.oper[i].func)(data->keys.oper[i].value, data->keys.oper[i].matrix, data);
			keys_pressed++;
		}
		i++;
	}
	if (keys_pressed > 0)
	{
		clear_img(data);
		render_map(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
}

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
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_hook(data.win, 2, KeyPressMask, handle_keydown, &data);
	mlx_hook(data.win, 3, KeyReleaseMask, handle_keyup, &data);
	mlx_hook(data.win, 17, ButtonPressMask, win_close_button, &data);
	mlx_loop(data.mlx);
}
