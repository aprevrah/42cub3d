/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:17 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/28 00:06:07 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	print_vec(u_tmatrix mat)
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

u_vec4	left_multiply(u_tmatrix mat, u_vec4 vec)
{
	u_vec4	result;

	result.f.x = vec.f.x * mat.f.x1 + vec.f.y * mat.f.y1 + vec.f.z * mat.f.z1
		+ vec.f.w * mat.f.w1;
	result.f.y = vec.f.x * mat.f.x2 + vec.f.y * mat.f.y2 + vec.f.z * mat.f.z2
		+ vec.f.w * mat.f.w2;
	result.f.z = vec.f.x * mat.f.x3 + vec.f.y * mat.f.y3 + vec.f.z * mat.f.z3
		+ vec.f.w * mat.f.w3;
	result.f.w = vec.f.x * mat.f.x4 + vec.f.y * mat.f.y4 + vec.f.z * mat.f.z4
		+ vec.f.w * mat.f.w4;
	return (result);
}

u_vec4	get_mapcoords(t_map *map, int index)
{
	u_vec4	p;

	p.f.x = index % map->length;
	p.f.y = index / map->length;
	p.f.z = (float)(map->arr[index]);
	p.f.w = 1;
	return (p);
}

t_ivec2	get_sspace(u_vec4 v)
{
	t_ivec2	p;

	// v = perspec_div(v);
	p.x = (int)((v.f.x));
	p.y = (int)((v.f.y));
	return (p);
}

void	render_map(t_data *data)
{
	t_map *map;
	u_vec4 mverts[data->map->length * data->map->height];
	t_ivec2 spoints[data->map->length * data->map->height];

	printf("view mat:\n");
	print_vec(data->tmatrices[0]);
	printf("obj mat:\n");
	print_vec(data->tmatrices[1]);

	u_tmatrix tmat;
	int i;

	map = data->map;
	tmat = multiply_tmats(perspec_project_m(1, 100),
			multiply_tmats(data->tmatrices[0], data->tmatrices[1]));

	i = 0;
	while (i < map->height * map->length)
	{
		mverts[i] = get_mapcoords(map, i);
		i++;
	}

	i = 0;
	while (i < map->height * map->length)
	{
		spoints[i] = get_sspace(left_multiply(tmat, mverts[i]));

		i++;
	}

	printf("%ix %iy\n", spoints[0].x, spoints[0].y);

	i = 0;
	while (i < map->height * map->length)
	{
		if ((i + 1) % (map->length) != 0)
		{
			line_put(data, spoints[i], spoints[i + 1], 0x00FFFFFF);
			/* printf("Horizontal i:%i P1:%ix %iy P2:%ix %iy\n", i, p1.x, p1.y,
				p2.x, p2.y); */
		}

		if (i < (map->height - 1) * map->length)
		{
			line_put(data, spoints[i], spoints[i + map->length], 0x00FFFFFF);
			/* printf("Vertical i:%i P1:%ix %iy P2:%ix %iy\n", i, p1.x, p1.y,
				p2.x, p2.y); */
		}
		i++;
	}
}