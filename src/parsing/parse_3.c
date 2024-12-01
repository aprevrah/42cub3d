/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:46:20 by tmeniga@stu       #+#    #+#             */
/*   Updated: 2024/11/30 21:08:54 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_valid_char(char const s) //! only accept spaces and newline, no tab
{
	if (s != '0' && s != '1' && s != 'N' && s != 'E' && s != 'S' && s != 'W'
		&& s != ' ' && s != '\t' && s != '\n' && s != '\r' && s != '\v'
		&& s != '\f')
		return (0);
	return (1);
}

int	get_dir(char c)
{
	if (c == 'N')
		return (3);
	if (c == 'E')
		return (4);
	if (c == 'S')
		return (5);
	else
		return (6);
}

int	count_players(t_map *map)
{
	int	x;
	int	y;
	int	player_count;

	x = 0;
	y = 0;
	player_count = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->length)
		{
			if (map->arr[y][x] >= 3 && map->arr[y][x] <= 6)
				player_count++;
			x++;
		}
		y++;
	}
	return (player_count);
}

int	procces_line(char const *s, t_map *map, int *i, int y)
{
	int	x;

	x = 0;
	while (s[*i] && s[*i] != '\n')
	{
		if (!is_valid_char(s[*i]))
			return (err("unvalid char in map\n"), 1);
		if (s[*i] == '0')
			map->arr[y][x] = 1;
		if (s[*i] == 'N' || s[*i] == 'E' || s[*i] == 'S' || s[*i] == 'W')
			map->arr[y][x] = get_dir(s[*i]);
		(*i)++;
		x++;
	}
	return (0);
}

int	fill_map(char const *s, t_map *map)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (y < map->height)
	{
		if (procces_line(s, map, &i, y))
			return (1);
		y++;
		if (s[i] != '\0')
			i++;
		else
			break ;
	}
	if (count_players(map) == 0)
		return (err("Error: missing player\n"), 1);
	if (count_players(map) > 1)
		return (err("Error: too many players\n"), 1);
	return (0);
}
