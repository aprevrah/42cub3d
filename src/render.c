/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:17 by aprevrha          #+#    #+#             */
/*   Updated: 2024/09/30 15:29:07 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_vec(t_tmatrix mat)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%.1f	", mat.arr[i + j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

t_vec4	get_mapcoords(t_map *map, int index)
{
	t_vec4	p;

	p.f.x = index % map->length;
	p.f.y = index / map->length;
	p.f.z = (float)(map->arr[index]);
	p.f.w = 1;
	return (p);
}

t_ivec2	get_sspace(t_vec4 v)
{
	t_ivec2	p;

	p.x = (int)((v.f.x));
	p.y = (int)((v.f.y));
	return (p);
}

static void	connect_spoints(t_ivec2 *spoints, t_data *data)
{
	t_map	*map;
	int		i;

	map = data->map;
	i = 0;
	while (i < map->height * map->length)
	{
		if ((i + 1) % (map->length) != 0)
			line_put(data, spoints[i], spoints[i + 1], COLOR);
		if (i < (map->height - 1) * map->length)
			line_put(data, spoints[i], spoints[i + map->length], COLOR);
		i++;
	}
}

void	render_map(t_data *data)
{
	t_ivec2		*spoints;
	t_tmatrix	tmat;
	int			i;

	spoints = (t_ivec2 *)malloc(sizeof(t_ivec2) * data->map->length
			* data->map->height);
	if (!spoints)
		free_and_exit(data, 1);
	tmat = multiply_tmats(data->tmatrices[0], data->tmatrices[1]);
	i = 0;
	while (i < data->map->height * data->map->length)
	{
		spoints[i] = get_sspace(left_multiply(tmat, get_mapcoords(data->map,
						i)));
		i++;
	}
	connect_spoints(spoints, data);
	free(spoints);
}
