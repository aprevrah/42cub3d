/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:22:56 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/28 17:48:56 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>

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
			(data->keys[i].func)(data->keys[i].v, data->keys[i].matrix);
			keys_pressed++;
		}
		i++;
	}
	if (keys_pressed > 0)
	{
		ft_bzero(data->addr, W_HEIGHT * data->line_length);
		render_map(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
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
