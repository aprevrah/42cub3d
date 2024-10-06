/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:17 by aprevrha          #+#    #+#             */
/*   Updated: 2024/10/02 16:31:07 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	print_vec(t_tmatrix mat)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			printf("%.1f	", mat.arr[i + j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

// t_vec4	get_mapcoords(t_map *map, int index)
// {
// 	t_vec4	p;

// 	p.f.x = index % map->length;
// 	p.f.y = index / map->length;
// 	//p.f.z = (float)(map->arr[index]);
// 	p.f.w = 1;
// 	return (p);
// }

// t_ivec2	get_sspace(t_vec4 v)
// {
// 	t_ivec2	p;

// 	p.x = (int)((v.f.x));
// 	p.y = (int)((v.f.y));
// 	return (p);
// }

// static void	connect_spoints(t_ivec2 *spoints, t_data *data)
// {
// 	t_map	*map;
// 	int		i;

// 	map = data->map;
// 	i = 0;
// 	while (i < map->height * map->length)
// 	{
// 		if ((i + 1) % (map->length) != 0)
// 			line_put(data, spoints[i], spoints[i + 1], COLOR);
// 		if (i < (map->height - 1) * map->length)
// 			line_put(data, spoints[i], spoints[i + map->length], COLOR);
// 		i++;
// 	}
// }
void	render_rect(t_data *data, t_ivec2 p1, t_ivec2 p2)
{
	t_ivec2 p1_;
	t_ivec2 p2_;

	p1_.x = p1.x;
	p1_.y = p2.y;
	p2_.x = p2.x;
	p2_.y = p1.y;

	line_put(data, p1, p2, COLOR);
	line_put(data, p1, p1_, COLOR);
	line_put(data, p1, p2_, COLOR);
	line_put(data, p2, p1_, COLOR);
	line_put(data, p2, p2_, COLOR);
}
void	render_players(t_data *data)
{
	t_player player = data->players[0];
	render_rect(data, (t_ivec2){player.position.x -2, player.position.y -2}, (t_ivec2){player.position.x + 2, player.position.y + 2});
	line_put(data, (t_ivec2){round(player.position.x), round(player.position.y)}, (t_ivec2){round(player.position.x + player.orientation.x * 20), round(player.position.y + player.orientation.y * 20)}, 0xf7f70a);
}

void	render_map(t_data *data)
{
	t_map map = *data->map;
	int x ,y = 0;
	int unit = 50;

	while (y < map.height)
	{
		while (x < map.length)
		{
			if (!map.arr[y][x])
				render_rect(data, (t_ivec2){x * unit, y * unit}, (t_ivec2){(x + 1) * unit, (y + 1) * unit});
			x++;
		}
		x = 0;
		y++;
	}
}





// void	render_map(t_data *data)
// {
// 	t_ivec2		*spoints;
// 	t_tmatrix	tmat;
// 	int			i;

// 	spoints = (t_ivec2 *)malloc(sizeof(t_ivec2) * data->map->length
// 			* data->map->height);
// 	if (!spoints)
// 		free_and_exit(data, 1);
// 	tmat = multiply_tmats(data->tmatrices[0], data->tmatrices[1]);
// 	i = 0;
// 	while (i < data->map->height * data->map->length)
// 	{
// 		spoints[i] = get_sspace(left_multiply(tmat, get_mapcoords(data->map,
// 						i)));
// 		i++;
// 	}
// 	connect_spoints(spoints, data);
// 	free(spoints);
// }
