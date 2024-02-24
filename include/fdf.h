/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:01:15 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/24 18:12:03 by aprevrha         ###   ########.fr       */
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
# define W_WIDTH 1920
# define W_HEIGHT 1080
# define NUM_OF_KEYS 10
# define OPER_FACTOR 0.05


typedef struct s_map
{
	int length;
	int height;
    int *arr;
}				t_map;

typedef union
{
    struct
	{
        float x, y, z, w;
    }	f;
    float arr[4];
}	u_vec4;

typedef union
{
    struct
	{
        float x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3, x4, y4, z4, w4;
    }	f;
    float arr[16];
}	u_tmatrix;

typedef void	(*t_key_func)(int value, char matrix_char, void *data);

typedef struct s_operation
{
	t_key_func	func;
	int			value;
	char		matrix;
}	t_operation;

typedef struct s_keys
{
	int			codes[NUM_OF_KEYS];
	int			state[NUM_OF_KEYS];
	t_operation	oper[NUM_OF_KEYS];
}	t_keys;

typedef struct  s_data
{
	void	    *mlx;
	void	    *win;
	void	    *img;
	char	    *addr;
	int         bits_per_pixel;
	int		    line_length;
	int		    endian;
	t_map	    *map;
    u_tmatrix   obj_tmat;
    u_tmatrix   view_tmat;
	t_keys		keys;
}				t_data;

typedef struct s_ivec2
{
    int x;
    int y;
}		t_ivec2;

// typedef struct s_vec3
// {
//     float x;
//     float y;
// 	float z;
// }		t_vec3;




//draw.c
void        my_mlx_pixel_put(t_data *data, int x, int y, int color);
void        line_put(t_data *data, t_ivec2 a, t_ivec2 b, int color);

//matrix_utils.c
u_tmatrix   rotation_m_x(float angle);
u_tmatrix   rotation_m_y(float angle);
u_tmatrix   rotation_m_z(float angle);
u_tmatrix   scale_m(float scale);
u_tmatrix   translate_m(float x, float y, float z);
u_tmatrix   multiply_tmats(u_tmatrix mat1, u_tmatrix mat2);

//oper.c
void		rot_x(int value, char matrix_char, void *data);
void		rot_y(int value, char matrix_char, void *data);
void		rot_z(int value, char matrix_char, void *data);

//parse.c
t_map       *parse_map(int fd);

//render.c
void        render_map(t_data *data);

#endif