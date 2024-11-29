/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:06 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/27 19:04:51 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	procces_line2(char const *s, int **arr, int *i, int y)
{
	int x;

	x = 0;
	while (s[*i] && s[*i] != '\n')
	{
		if (s[*i] == '0' || s[*i] == 'N' || s[*i] == 'E' || s[*i] == 'S' || s[*i] == 'W')
				arr[y][x] = 1;
			if (s[*i] == ' ')
				arr[y][x] = 8;
		(*i)++;
		x++;
	}
	return (x);	
}

int	fill_map2(char const *s, t_map *map, int **arr)
{
	int	i;
	int x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (y < map->height)
	{
		x = procces_line2(s, arr, &i, y);
		while (x < map->length)
		{
			arr[y][x] = 8;
			x++;
		}
		y++;
		if (s[i] != '\0')
			i++;
		else
			break ;
	}
	return (0);
}

//! check minimum a least 3 row and collums;

int	check_sides(int **arr, int height, int length)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < length)
	{
		if (arr[0][x] == 1 || arr[height-1][x] == 1)
			return (0);
		x++;
	}
	while (y < height)
	{
		if (arr[y][0] == 1 || arr[y][length-1] == 1)
			return (0);
		y++;
	}
	return (1);
}

int check_middle(int **arr, int height, int length)
{
	int x;
	int y;

	x = 1;
	y = 1;
	while (y < height-1)
	{
		x = 1;
		while (x < length-1)
		{
			if (arr[y][x] == 1)
			{
				if ((arr[y-1][x] != 0 && arr[y-1][x] != 1) || \
					(arr[y][x+1] != 0 && arr[y][x+1] != 1) || \
					(arr[y+1][x] != 0 && arr[y+1][x] != 1) || \
					(arr[y][x-1] != 0 && arr[y][x-1] != 1))
				{
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	is_wall_enclosed(char *content , t_map *map)
{
	int **array;

	array = new_2d_int_arr(map->height, map->length);
	if (!array)
		return (0);
	fill_map2(content, map,array);
	if (!check_sides(array, map->height, map->length))
		return (printf("Error: map is not enclosed\n"), free_2d_arr((void **)array, map->height), 0);
	if (!check_middle(array, map->height, map->length))
		return (printf("Error: map is not enclosed\n"), free_2d_arr((void **)array, map->height), 0);
	free_2d_arr((void **)array, map->height);
	return (1);
}