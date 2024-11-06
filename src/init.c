/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:25:37 by aprevrha          #+#    #+#             */
/*   Updated: 2024/10/28 15:09:46 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// static t_key	init_key(int keycode, void	(*func)(void))
// {
// 	t_key	key;

// 	key.state = 0;
// 	key.code = keycode;
// 	key.func = func;
// 	key.args = 0;
// 	return (key);
// }

//static t_key	init_key_look(int keycode, t_player *player, double rotation)
// static t_key	init_key(int keycode, void	(*func)(void))
// {
// 	t_key	key;

// 	key.state = 0;
// 	key.code = keycode;
// 	key.func = func;
// 	key.args = 0;
// 	return (key);
// }

static t_key	init_key_move(int keycode, t_player *player, t_dvec2 direction)
{
	t_key	key;
	
	
	key.state = 0;
	key.code = keycode;
	key.func = move;
	key.args.move_args.player = player;
    key.args.move_args.direction = direction;
	return (key);
}

static t_key	init_key_look(int keycode, t_player *player, double rotation)
{
	t_key	key;

	key.state = 0;
	key.code = keycode;
	key.func = look;
	key.args.look_args.player = player;
    key.args.look_args.rotation = rotation;
	key.func = look;
	key.args.look_args.player = player;
    key.args.look_args.rotation = rotation;
	return (key);
}

// Needs to match NUM_OF_KEYS
int	init_keys(t_key *keys, t_player *players)
{
	keys[0] = init_key_move(XK_Escape, &players[0], (t_dvec2){0.0, 0.0});
	keys[1] = init_key_move(XK_w, &players[0], (t_dvec2){0.0, 1.0});
	keys[2] = init_key_move(XK_a, &players[0], (t_dvec2){1.0, 0.0});
	keys[3] = init_key_move(XK_s, &players[0], (t_dvec2){0.0, -1.0});
	keys[4] = init_key_move(XK_d, &players[0], (t_dvec2){-1.0, 0.0});
	keys[5] = init_key_look(XK_Right, &players[0], (double)0.05);
	keys[6] = init_key_look(XK_Left, &players[0], (double)-0.05);
	
	// keys[9] = init_key(XK_Up, translate, &players[0], nv(0, -T_SPEED, 0));
	// keys[10] = init_key(XK_Down, translate, &players[0], nv(0, T_SPEED, 0));
	// keys[11] = init_key(XK_Left, translate, &players[0], nv(-T_SPEED, 0, 0));
	// keys[12] = init_key(XK_Right, translate, &players[0], nv(T_SPEED, 0, 0));
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

int	init_players(t_player **players, t_map *map)
{
	(void)map;
	*players = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!*players)
		return (1);
	// hard coded for now, use map later
	(*players)[0].position = (t_dvec2){1.5, 1.5}; 
	(*players)[0].orientation = (t_dvec2){0, -1};
	(*players)[0].movement_speed = (double){0.1};
	return (0);
}
