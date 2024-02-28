/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:25:37 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/28 18:36:58 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static t_key	init_key(int keycode, t_key_func function, t_tmatrix *tmatrix,
		t_vec4 vec)
{
	t_key	key;

	key.state = 0;
	key.code = keycode;
	key.func = function;
	key.matrix = tmatrix;
	key.v = vec;
	return (key);
}

// Needs to match NUM_OF_KEYS
int	init_keys(t_key *keys, t_tmatrix *tmatrices)
{
	keys[0] = init_key(XK_Escape, scale, &tmatrices[1], nv(0, 0, 0));
	keys[1] = init_key(XK_w, rotate, &tmatrices[1], nv(-R_SPEED, 0, 0));
	keys[2] = init_key(XK_s, rotate, &tmatrices[1], nv(R_SPEED, 0, 0));
	keys[3] = init_key(XK_a, rotate, &tmatrices[1], nv(0, R_SPEED, 0));
	keys[4] = init_key(XK_d, rotate, &tmatrices[1], nv(0, -R_SPEED, 0));
	keys[5] = init_key(XK_q, rotate, &tmatrices[1], nv(0, 0, R_SPEED));
	keys[6] = init_key(XK_e, rotate, &tmatrices[1], nv(0, 0, -R_SPEED));
	keys[7] = init_key(XK_r, scale, &tmatrices[1], nv(1.0 + S_SPEED, 1.0
				+ S_SPEED, 1.0 + S_SPEED));
	keys[8] = init_key(XK_f, scale, &tmatrices[1], nv(1.0 - S_SPEED, 1.0
				- S_SPEED, 1.0 - S_SPEED));
	keys[9] = init_key(XK_Up, translate, &tmatrices[0], nv(0, -T_SPEED, 0));
	keys[10] = init_key(XK_Down, translate, &tmatrices[0], nv(0, T_SPEED, 0));
	keys[11] = init_key(XK_Left, translate, &tmatrices[0], nv(-T_SPEED, 0, 0));
	keys[12] = init_key(XK_Right, translate, &tmatrices[0], nv(T_SPEED, 0, 0));
	return (0);
}

int	init_mlx(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->win = mlx_new_window(data->mlx, W_WIDTH, W_HEIGHT, "FdF");
	if (!data->mlx)
		return (0);
	data->img = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	if (!data->mlx)
		return (0);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->line_length), &(data->endian));
	if (!data->addr)
		return (0);
	return (1);
}

void	init_tmatrices(t_tmatrix *tmatrices, t_map *map)
{
	float	scale;

	scale = 50;
	tmatrices[1] = translate_m(nv(-((map->length - 1) / 2.f * scale),
				-((map->height - 1) / 2.f * scale), 0.f));
	tmatrices[1] = multiply_tmats(tmatrices[1], scale_m(nv(scale, scale,
					scale)));
	tmatrices[0] = translate_m(nv(W_WIDTH / 2, W_HEIGHT / 2, 0.f));
}

/* Old Binds
	init_key(&keys[4], XK_w, translate, &tmatrices[0], nv(0, 0, 50));
	init_key(&keys[5], XK_s, translate, &tmatrices[0], nv(0, 0, -50));
	init_key(&keys[6], XK_a, translate, &tmatrices[0], nv(50, 0, 0));
	init_key(&keys[7], XK_d, translate, &tmatrices[0], nv(-50, 0, 0));
	init_key(&keys[8], XK_space, translate, &tmatrices[0], nv(0, 50, 0));
	init_key(&keys[9], XK_Shift_L, translate, &tmatrices[0], nv(0, -50, 0)); */