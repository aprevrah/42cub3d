/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:17 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/24 17:24:18 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

u_vec4 left_multiply(u_tmatrix mat, u_vec4 vec) {
    u_vec4	result;

    // result.f.x = vec.f.x * mat.f.x1 + vec.f.y * mat.f.x2 + vec.f.z * mat.f.x3 + vec.f.w * mat.f.x4;
    // result.f.y = vec.f.x * mat.f.y1 + vec.f.y * mat.f.y2 + vec.f.z * mat.f.y3 + vec.f.w * mat.f.y4;
    // result.f.z = vec.f.x * mat.f.z1 + vec.f.y * mat.f.z2 + vec.f.z * mat.f.z3 + vec.f.w * mat.f.z4;
    // result.f.w = vec.f.x * mat.f.w1 + vec.f.y * mat.f.w2 + vec.f.z * mat.f.w3 + vec.f.w * mat.f.w4;

	result.f.x = vec.f.x * mat.f.x1 + vec.f.y * mat.f.y1 + vec.f.z * mat.f.z1 + vec.f.w * mat.f.w1;
	result.f.y = vec.f.x * mat.f.x2 + vec.f.y * mat.f.y2 + vec.f.z * mat.f.z2 + vec.f.w * mat.f.w2;
	result.f.z = vec.f.x * mat.f.x3 + vec.f.y * mat.f.y3 + vec.f.z * mat.f.z3 + vec.f.w * mat.f.w3;
	result.f.w = vec.f.x * mat.f.x4 + vec.f.y * mat.f.y4 + vec.f.z * mat.f.z4 + vec.f.w * mat.f.w4;
	
    return (result);
}

u_vec4 get_mapcoords(t_map *map, int index)
{
	u_vec4	p;
	p.f.x = index % map->length;
    p.f.y = index / map->length;
	p.f.z = (float)(map->arr[index]);
	p.f.w = 1;
	printf("MapIdx: %i Coords: %.1fx %.1fy %.1fz\n", index, p.f.x, p.f.y, p.f.z);
	return (p);
}


t_ivec2 get_sspace(u_vec4 v, u_tmatrix obj_tmat,  u_tmatrix view_tmat)
{
	t_ivec2	p;
	u_vec4	tv;

	tv = left_multiply(obj_tmat, v);
    tv = left_multiply(view_tmat, tv);
	p.x = (int)(tv.f.x);
	p.y = (int)(tv.f.y);

	return (p);
}

void	render_map(t_data *data)
{
    t_map *map;
    u_tmatrix obj_tmat;
    u_tmatrix view_tmat;
	int	i;
	t_ivec2 p1;
	t_ivec2 p2;

    map = data->map;
    obj_tmat = data->obj_tmat;
    view_tmat = data->view_tmat;

	i = 0;
	while(i < map->height * map->length)
	{
		if ((i + 1) % (map->length) != 0)
		{
			p1 = get_sspace(get_mapcoords(map, i), obj_tmat, view_tmat);
			p2 = get_sspace(get_mapcoords(map, i + 1), obj_tmat, view_tmat);
			line_put(data, p1, p2, 0x00FFFFFF);
			//printf("Horizontal i:%i P1:%ix %iy P2:%ix %iy\n", i, p1.x, p1.y, p2.x, p2.y);
		}
			
		if (i < (map->height - 1) * map->length)
		{
			p1 = get_sspace(get_mapcoords(map, i), obj_tmat, view_tmat);
			p2 = get_sspace(get_mapcoords(map, i + map->length), obj_tmat, view_tmat);
			line_put(data, p1, p2, 0x00FFFFFF);
			//printf("Vertical i:%i P1:%ix %iy P2:%ix %iy\n", i, p1.x, p1.y, p2.x, p2.y);
		}
			
		i++;
	}
}