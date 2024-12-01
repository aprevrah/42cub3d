/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:10:45 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/30 18:20:47 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	return (key);
}

// Needs to match NUM_OF_KEYS
void	init_keys(t_key *keys, t_player *players)
{
	keys[0] = init_key_move(XK_Escape, &players[0], (t_dvec2){0.0, 0.0});
	keys[1] = init_key_move(XK_w, &players[0], (t_dvec2){0.0, 1.0});
	keys[2] = init_key_move(XK_a, &players[0], (t_dvec2){1.0, 0.0});
	keys[3] = init_key_move(XK_s, &players[0], (t_dvec2){0.0, -1.0});
	keys[4] = init_key_move(XK_d, &players[0], (t_dvec2){-1.0, 0.0});
	keys[5] = init_key_look(XK_Right, &players[0], (double)1.0);
	keys[6] = init_key_look(XK_Left, &players[0], (double)-1.0);
}
