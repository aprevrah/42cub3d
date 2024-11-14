/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:22:56 by aprevrha          #+#    #+#             */
/*   Updated: 2024/10/28 14:55:18 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>
int long loops;

void delta_time(t_data *data)
{
	struct timeval	tv_now;

	if (gettimeofday(&tv_now, NULL))
		printf("gettimeofday failed");
	data->delta_time = (tv_now.tv_sec * 1000 + tv_now.tv_usec/1000) - (data->lastframe.tv_sec * 1000 + data->lastframe.tv_usec/1000);
	printf("frametime: %dms	fps: %d loop: %ld\n", data->delta_time, 1000/data->delta_time, loops);
	data->lastframe = tv_now;
	loops++;
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
	//ft_bzero(data->addr, W_HEIGHT * data->line_length);
	
	//render toggles
	//render_half_screen(data);
	render_walls(data);
	render_map(data);
	//render_players(data);
	render_minimap_rays(data);

	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	//debug_render_textures(data, 4);
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
