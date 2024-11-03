/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:06 by aprevrha          #+#    #+#             */
/*   Updated: 2024/09/30 18:46:51 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void printmap(t_map *map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < map->height)
	{
		while (x < map->length)
		{
			printf("%i", map->arr[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
	printf ("height: %i length: %i\n", map->height, map->length);
}

void printtexture_data(t_texture_data texture_data)
{
	printf("NO: %s\n", texture_data.path_NO);
	printf("EA: %s\n", texture_data.path_EA);
	printf("SO: %s\n", texture_data.path_SO);
	printf("WE: %s\n", texture_data.path_WE);
	printf("C: #%06X\n", texture_data.col_C);
	printf("F: #%06X\n", texture_data.col_F);
}