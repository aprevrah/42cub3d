/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:01:15 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/21 21:57:59 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define VERBOSE_ERR 0
# define MAP_SEP " "
# define PI 3.141592678

typedef struct s_map
{
	int length;
	int height;
    int *arr;
}				t_map;

typedef struct	s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	*map;
}				t_data;

typedef struct s_ivec2
{
    int x;
    int y;
}		t_ivec2;

typedef struct s_vec3
{
    float x;
    float y;
	float z;
}		t_vec3;


typedef union
{
    struct
	{
        float x, y, z, w;
    }	f;
    float arr[4];
}	t_vec4;

typedef union
{
    struct
	{
        float x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3, x4, y4, z4, w4;
    }	f;
    float arr[16];
}	t_tmatrix;

/* 
typedef struct s_tmatrix
{
    int x1;
    int y1;
	int z1;
	int x2;
    int y2;
	int z2;
}		t_vec6;
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	line_put(t_data *data, t_ivec2 a, t_ivec2 b, int color);
t_map	*parse_map(int fd);

#endif