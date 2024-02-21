/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:34:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/15 00:01:18 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <X11/keysym.h>
#include <stdlib.h>

/* 
int	has_extension(char * fname, char *fextension)
{
	ft_strrchr(fname)
	ft_strc
}*/

int	close_win(int keycode, t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	return (0);
}

int	handle_keydown(int keycode, t_data *data)
{
	printf("Keycode: %i\n", keycode);
	if (keycode == XK_Escape)
		mlx_destroy_window(data->mlx, data->win);
	return (0);
}

void	print_map(t_map *map)
{
	int		col;
	int		line;

	col = 0;
	line = 0;
	while(line < map->height)
	{
		while(col < map->length)
		{
			ft_printf(" %i", map->arr[map->length * line + col]);
			col++;
		}
		ft_printf("\n");
		col = 0;
		line++;
	}
}

t_vec4 get_mapcoords(t_map *map, int index)
{
	t_vec4	p;
	p.f.x = index % map->length;
    p.f.y = index / map->length;
	p.f.z = (float)(map->arr[index]);
	p.f.w = 1;
	printf("MapIdx: %i Coords: %.1fx %.1fy %.1fz\n", index, p.f.x, p.f.y, p.f.z);
	return (p);
}

/* 
int	get_x(t_map *map, int index)
{
    return (index % map->length);
}

int	get_y(t_map *map, int index)
{
    return (index / map->length);
}

int	get_index(t_map *map, int x, int y)
{
	if (x >= 0 && x < map->length && y >= 0 && y < map->height)
        return (y * map->length + x);
	return (-1);
}
 */
/* 
t_v2	vect_multi(t_v3 point, t_v6 view, t_v2 offset)
{
	t_v2	result;
	result.x = point.x * view.x1 + point.y * view.y1 + point.z * view.z1;
	result.y = point.x * view.x2 + point.y * view.y2 + point.z * view.z2;
	result.x *= 20;
	result.y *= 20;
	result.x += offset.x;
	result.y += offset.y;
	return (result);
}
*/
/* 
t_v2	vect_multi(t_vec4 )
{
	t_ivec2	result;
	result.x = point.x * view.x1 + point.y * view.y1 + point.z * view.z1;
	result.y = point.x * view.x2 + point.y * view.y2 + point.z * view.z2;
	result.x *= 20;
	result.y *= 20;
	result.x += offset.x;
	result.y += offset.y;
	return (result);
}
 */
t_vec4 multiply(t_vec4 vec, t_tmatrix mat) {
    t_vec4	result;

    result.f.x = vec.f.x * mat.f.x1 + vec.f.y * mat.f.x2 + vec.f.z * mat.f.x3 + vec.f.w * mat.f.x4;
    result.f.y = vec.f.x * mat.f.y1 + vec.f.y * mat.f.y2 + vec.f.z * mat.f.y3 + vec.f.w * mat.f.y4;
    result.f.z = vec.f.x * mat.f.z1 + vec.f.y * mat.f.z2 + vec.f.z * mat.f.z3 + vec.f.w * mat.f.z4;
    result.f.w = vec.f.x * mat.f.w1 + vec.f.y * mat.f.w2 + vec.f.z * mat.f.w3 + vec.f.w * mat.f.w4;
    return (result);
}

t_ivec2 get_sspace(t_vec4 v, t_tmatrix tmat)
{
	t_ivec2	p;
	t_vec4	tv;

	tv = multiply(v, tmat);
	p.x = (int)(tv.f.x * 30);
	p.y = (int)(tv.f.y * 30);
	
	return (p);
}

void	render_map(t_map *map, t_data *data, t_tmatrix tmat)
{
	int	i;
	t_ivec2 p1;
	t_ivec2 p2;

	i = 0;
	while(i < map->height * map->length)
	{
		if ((i + 1) % (map->length) != 0)
		{
			p1 = get_sspace(get_mapcoords(map, i), tmat);
			p2 = get_sspace(get_mapcoords(map, i + 1), tmat);
			line_put(data, p1, p2, 0x00FFFFFF);
			printf("Horizontal i:%i P1:%ix %iy P2:%ix %iy\n", i, p1.x, p1.y, p2.x, p2.y);
		}
			
		if (i < (map->height - 1) * map->length)
		{
			p1 = get_sspace(get_mapcoords(map, i), tmat);
			p2 = get_sspace(get_mapcoords(map, i + map->length), tmat);
			line_put(data, p1, p2, 0x00FFFFFF);
			printf("Vertical i:%i P1:%ix %iy P2:%ix %iy\n", i, p1.x, p1.y, p2.x, p2.y);
		}
			
		i++;
	}
}

t_tmatrix multiply_tmats(t_tmatrix mat1, t_tmatrix mat2)
{
    t_tmatrix result;
	int i;
	int j;
	int k;

    i = 0;
    while (i < 4) 
	{
        j = 0;
        while (j < 4) 
		{
            // Initialize the element in the result matrix to 0
            result.arr[i * 4 + j] = 0;
            k = 0;
            while (k < 4) 
			{
                // Compute the dot product of the i-th row of mat1 and the j-th column of mat2
                result.arr[i * 4 + j] += mat1.arr[i * 4 + k] * mat2.arr[k * 4 + j];
                k++;
            }
            j++;
        }
        i++;
    }
    return (result);
}

t_vec3 normalize(t_vec3 v) 
{
    float magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

    // Check for division by zero to avoid NaN (Not a Number)
    if (magnitude != 0)
	{
        v.x /= magnitude;
        v.y /= magnitude;
        v.z /= magnitude;
    }
    return (v);
}

t_tmatrix	get_tmatrix(t_vec3 rotaxis, float rotang, t_vec3 translation)
{
	t_tmatrix	tmat;
	// t_tmatrix	smat;
	// int			i;
	rotaxis = normalize(rotaxis);

	tmat.f.x1 = rotaxis.x * rotaxis.x * (1 - cos(rotang)) + cos(rotang);
	tmat.f.x2 = rotaxis.x * rotaxis.y * (1 - cos(rotang)) + rotaxis.z * sin(rotang);
	tmat.f.x3 = rotaxis.x * rotaxis.z * (1 - cos(rotang)) - rotaxis.y * sin(rotang);

	tmat.f.y1 = rotaxis.y * rotaxis.x * (1 - cos(rotang)) - rotaxis.z * sin(rotang);
	tmat.f.y2 = rotaxis.y * rotaxis.y * (1 - cos(rotang)) + cos(rotang);
	tmat.f.y3 = rotaxis.y * rotaxis.z * (1 - cos(rotang)) + rotaxis.x * sin(rotang);

	tmat.f.z1 = rotaxis.z * rotaxis.x * (1 - cos(rotang)) + rotaxis.x * sin(rotang);
	tmat.f.z2 = rotaxis.z * rotaxis.y * (1 - cos(rotang)) - rotaxis.y * sin(rotang);
	tmat.f.z3 = rotaxis.z * rotaxis.z * (1 - cos(rotang)) + cos(rotang);
	
	tmat.f.w1 = translation.x;
	tmat.f.w2 = translation.y;
	tmat.f.w3 = translation.z;
	tmat.f.w4 = 1;
	// i = -1;
	// while (i < 16)
	// 	smat.arr[++i] = 0;
	return (tmat);
}


int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;
	t_map	*map;
	t_tmatrix tmat;
	

	if (argc > 2)
		return (1);
	if (argv)
		printf("av\n");

	
	fd = open(argv[1], O_RDONLY);
	map = parse_map(fd);
	close(fd);
	
	
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	t_vec3 ra;
	ra.x = 0, ra.y = 1, ra.z = 0;
	t_vec3 t;
	t.x = 10, t.y = 10, t.z = 0;
	
	tmat = get_tmatrix(ra, PI/2., t);
	render_map(map, &data, tmat);

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 2, 1L<<0, handle_keydown, &data);
	mlx_hook(data.win, 17, 0, close_win, &data);
	mlx_loop(data.mlx);
}
