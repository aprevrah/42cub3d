/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:25:37 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/30 18:20:52 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_dvec2	get_player_pos(t_map *map)
{
	int		i;
	int		j;
	t_dvec2	pos;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->length)
		{
			if (map->arr[i][j] >= 3 && map->arr[i][j] <= 6)
			{
				pos.y = i + 0.5;
				pos.x = j + 0.5;
				return (pos);
			}
			j++;
		}
		i++;
	}
	pos.x = 1.5;
	pos.y = 1.5;
	return (pos);
}

//! this is kinda wack, maybe set the rot while parsing?
t_dvec2	get_player_orientation(t_map *map)
{
	int		i;
	int		j;
	t_dvec2	orientation;

	i = 0;
	orientation = (t_dvec2){1, 1};
	while (i < map->height)
	{
		j = 0;
		while (j < map->length)
		{
			if (map->arr[i][j] == 3)
				orientation = (t_dvec2){0, -1};
			if (map->arr[i][j] == 4)
				orientation = (t_dvec2){1, 0};
			if (map->arr[i][j] == 5)
				orientation = (t_dvec2){0, 1};
			if (map->arr[i][j] == 6)
				orientation = (t_dvec2){-1, 0};
			j++;
		}
		i++;
	}
	return (orientation);
}

int	init_players(t_player **players, t_map *map)
{
	*players = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!*players)
		return (1);
	(*players)[0].position = get_player_pos(map);
	(*players)[0].orientation = get_player_orientation(map);
	(*players)[0].movement_speed = (double){0.003};
	(*players)[0].look_speed = (double){0.003};
	return (0);
}
