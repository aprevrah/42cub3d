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

void	delta_time(t_data *data)
{
	struct timeval	tv_now;

	if (gettimeofday(&tv_now, NULL))
		printf("gettimeofday failed");
	data->delta_time = (tv_now.tv_sec * 1000 + tv_now.tv_usec / 1000)
		- (data->lastframe.tv_sec * 1000 + data->lastframe.tv_usec / 1000);
	data->lastframe = tv_now;
	if (PRINT_FPS)
		printf("%dms	%dfps\n", data->delta_time, 1000
				/ data->delta_time);
}

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

int	loop_hook(t_data *data)
{
	int	i;
	int	keys_pressed;

	keys_pressed = 0;
	i = 0;
	if (data->keys[0].state == 1)
		free_and_exit(data, 0);
	while (i < NUM_OF_KEYS)
	{
		if (data->keys[i].state == 1)
		{
			(data->keys[i].func)(data, &data->keys[i].args);
			keys_pressed++;
		}
		i++;
	}
	// render toggles
	render_walls(data);
	// render_map(data);
	// render_players(data);
	// render_minimap_rays(data);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	delta_time(data);
	return (0);
}

int	handle_keydown(int keycode, t_key *keys)
{
	int	i;

	i = 0;
	while (i < NUM_OF_KEYS)
	{
		if (keys[i].code == keycode)
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
	int	i;

	i = 0;
	while (i < NUM_OF_KEYS)
	{
		if (keys[i].code == keycode)
		{
			keys[i].state = 0;
			break ;
		}
		i++;
	}
	return (0);
}
