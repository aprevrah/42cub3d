/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:25:37 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/30 19:19:05 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_mlx(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win = mlx_new_window(data->mlx, W_WIDTH, W_HEIGHT, "Cub3D");
	if (!data->mlx)
		return (1);
	data->img = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	if (!data->mlx)
		return (1);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->line_length), &(data->endian));
	if (!data->addr)
		return (1);
	return (0);
}

static int	win_close_button(t_data *data)
{
	free_and_exit(data, 0);
	return (0);
}

void	init_hooks(t_data *data)
{
	mlx_hook(data->win, 2, KeyPressMask, handle_keydown, data->keys);
	mlx_hook(data->win, 3, KeyReleaseMask, handle_keyup, data->keys);
	mlx_hook(data->win, 17, StructureNotifyMask, win_close_button, data);
	mlx_mouse_hook(data->win, handle_mouseclick, data);
	mlx_hook(data->win, MotionNotify, PointerMotionMask, handle_mousemove,
		data);
	mlx_loop_hook(data->mlx, loop_hook, data);
}

void	init2null(t_data *data)
{
	struct timeval	tv_now;

	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->map = NULL;
	data->players = NULL;
	data->use_mouse = false;
	if (gettimeofday(&tv_now, NULL))
	{
		printf("Error: gettimeofday failed\n");
		free_and_exit(data, 1);
	}
	data->lastframe = tv_now;
}
