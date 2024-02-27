/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:34:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/25 03:38:56 by aprevrha         ###   ########.fr       */
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

void	init_key(t_key *key, int keycode, t_key_func function, u_tmatrix *tmatrix, u_vec4 vec)
{
	key->state = 0;
	key->code = keycode;
	key->func = function;
	key->matrix = tmatrix;
	key->v = vec;
}

/* Old Binds
	init_key(&keys[4], XK_w, translate, &tmatrices[0], nv(0, 0, 50));
	init_key(&keys[5], XK_s, translate, &tmatrices[0], nv(0, 0, -50));
	init_key(&keys[6], XK_a, translate, &tmatrices[0], nv(50, 0, 0));
	init_key(&keys[7], XK_d, translate, &tmatrices[0], nv(-50, 0, 0));
	init_key(&keys[8], XK_space, translate, &tmatrices[0], nv(0, 50, 0));
	init_key(&keys[9], XK_Shift_L, translate, &tmatrices[0], nv(0, -50, 0));
 */
//Needs to match NUM_OF_KEYS
int	init_keys(t_key *keys, u_tmatrix *tmatrices)
{
	init_key(&keys[0], XK_w, rotate, &tmatrices[1], nv(-R_SPEED, 0, 0));
	init_key(&keys[1], XK_s, rotate, &tmatrices[1], nv(R_SPEED, 0, 0));
	init_key(&keys[2], XK_a, rotate, &tmatrices[1], nv(0, R_SPEED, 0));
	init_key(&keys[3], XK_d, rotate, &tmatrices[1], nv(0, -R_SPEED, 0));
	init_key(&keys[4], XK_q, rotate, &tmatrices[1], nv(0, 0, R_SPEED));
	init_key(&keys[5], XK_e, rotate, &tmatrices[1], nv(0, 0, -R_SPEED));
	init_key(&keys[6], XK_r, scale, &tmatrices[1], nv(1.0 + S_SPEED, 1.0 + S_SPEED, 1.0 + S_SPEED));
	init_key(&keys[7], XK_f, scale, &tmatrices[1], nv(1.0 - S_SPEED, 1.0 - S_SPEED, 1.0 - S_SPEED));

	init_key(&keys[8], XK_Up, translate, &tmatrices[0], nv(0, -T_SPEED, 0));
	init_key(&keys[9], XK_Down, translate, &tmatrices[0], nv(0, T_SPEED, 0));
	init_key(&keys[10], XK_Left, translate, &tmatrices[0], nv(-T_SPEED, 0, 0));
	init_key(&keys[11], XK_Right, translate, &tmatrices[0], nv(T_SPEED, 0, 0));
	
	return (0);
}

int	handle_keydown(int keycode, t_key *keys)
{
	int i;

	i = 0;
	while(i < NUM_OF_KEYS)
	{
		if(keys[i].code == keycode)
		{
			keys[i].state = 1;
			break ;
		}
		i++;
	}
	return (0);
}

int	handle_keyup(int keycode, t_key *keys)
{
	int i;
	
	i = 0;
	while(i < NUM_OF_KEYS)
	{
		if(keys[i].code == keycode)
		{
			keys[i].state = 0;
			break ;
		}
		i++;
	}
	return (0);
}


int	loop_hook(t_data *data)
{
	int i;
	int keys_pressed;
	
	keys_pressed = 0;
	i = 0;
	while (i < NUM_OF_KEYS)
	{
		if (data->keys[i].state == 1)
		{
			(data->keys[i].func)(data->keys[i].v, data->keys[i].matrix);
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
	return (0);
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
	
	scale = 50;
	data.tmatrices[1] = translate_m(nv(-((data.map->length - 1)/ 2.f), -((data.map->height - 1)/ 2.f), 0.f));
	data.tmatrices[1] = multiply_tmats(data.tmatrices[1], scale_m(nv(scale, scale, scale)));
	//data.tmatrices[0] = scale_m(nv(1, 1, 1));
	data.tmatrices[0] = translate_m(nv(W_WIDTH/2, W_HEIGHT/2, 0.f));
	render_map(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	init_keys(data.keys, data.tmatrices);
	mlx_hook(data.win, 2, KeyPressMask, handle_keydown, data.keys);
	mlx_hook(data.win, 3, KeyReleaseMask, handle_keyup, data.keys);
	mlx_hook(data.win, 17, ButtonPressMask, win_close_button, &data);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
}
