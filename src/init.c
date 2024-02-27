/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:25:37 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/27 23:49:38 by aprevrha         ###   ########.fr       */
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

static void	init_key(t_key *key, int keycode, t_key_func function,
		u_tmatrix *tmatrix, u_vec4 vec)
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
// Needs to match NUM_OF_KEYS
int	init_keys(t_key *keys, u_tmatrix *tmatrices)
{
	init_key(&keys[0], XK_w, rotate, &tmatrices[1], nv(-R_SPEED, 0, 0));
	init_key(&keys[1], XK_s, rotate, &tmatrices[1], nv(R_SPEED, 0, 0));
	init_key(&keys[2], XK_a, rotate, &tmatrices[1], nv(0, R_SPEED, 0));
	init_key(&keys[3], XK_d, rotate, &tmatrices[1], nv(0, -R_SPEED, 0));
	init_key(&keys[4], XK_q, rotate, &tmatrices[1], nv(0, 0, R_SPEED));
	init_key(&keys[5], XK_e, rotate, &tmatrices[1], nv(0, 0, -R_SPEED));
	init_key(&keys[6], XK_r, scale, &tmatrices[1], nv(1.0 + S_SPEED, 1.0
			+ S_SPEED, 1.0 + S_SPEED));
	init_key(&keys[7], XK_f, scale, &tmatrices[1], nv(1.0 - S_SPEED, 1.0
			- S_SPEED, 1.0 - S_SPEED));
	init_key(&keys[8], XK_Up, translate, &tmatrices[0], nv(0, -T_SPEED, 0));
	init_key(&keys[9], XK_Down, translate, &tmatrices[0], nv(0, T_SPEED, 0));
	init_key(&keys[10], XK_Left, translate, &tmatrices[0], nv(-T_SPEED, 0, 0));
	init_key(&keys[11], XK_Right, translate, &tmatrices[0], nv(T_SPEED, 0, 0));
	return (0);
}
int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->win = mlx_new_window(data->mlx, W_WIDTH, W_HEIGHT, "FdF");
	if (!data->mlx)
		return (free(data->mlx), 0);
	data->img = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	if (!data->mlx)
		return (mlx_destroy_window(data->mlx, data->win), free(data->mlx), 0);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->line_length), &(data->endian));
	if (!data->addr)
		return (mlx_destroy_image(data->mlx, data->img),
			mlx_destroy_window(data->mlx, data->win), free(data->mlx), 0);
	return (1);
}

void	init_tmatrices(u_tmatrix *tmatrices, t_map *map)
{
	float scale;

	scale = 50;
	tmatrices[1] = translate_m(nv(-((map->length - 1) / 2.f * scale),
				-((map->height - 1) / 2.f * scale), 0.f));
	tmatrices[1] = multiply_tmats(tmatrices[1], scale_m(nv(scale, scale,
					scale)));
	// data.tmatrices[0] = scale_m(nv(1, 1, 1));
	tmatrices[0] = translate_m(nv(W_WIDTH / 2, W_HEIGHT / 2, 0.f));
}