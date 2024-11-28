/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:22:56 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/20 12:13:55 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>

/* LEAKS: this leaks cus mlx sucks and its docs suck even more
int	handle_mouseclick(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button != 1)
		return (0);
	if (data->use_mouse)
	{
		data->use_mouse = false;
		//mlx_mouse_show(data->mlx, data->win);
	}
	else
	{
		data->use_mouse = true;
		//mlx_mouse_hide(data->mlx, data->win);
		//mlx_mouse_move(data->mlx, data->win, W_WIDTH / 2, W_HEIGHT / 2);
	}
	return (0);
}*/

int	handle_mouseclick(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button != 1)
		return (0);
	if (data->use_mouse)
		data->use_mouse = false;
	else
		data->use_mouse = true;
	return (0);
}

int	handle_mousemove(int x, int y, t_data *data)
{
	static int	dx;
	t_look_args	look_args;

	(void)y;
	if (!data->use_mouse)
		return (0);
	dx = (x - W_WIDTH / 2);
	if (dx)
	{
		mlx_mouse_move(data->mlx, data->win, W_WIDTH / 2, W_HEIGHT / 2);
		look_args.player = &data->players[0];
		look_args.rotation = dx * data->players[0].look_speed * 10;
		look(data, &look_args);
	}
	return (0);
}
