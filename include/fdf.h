/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:01:15 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/27 23:53:11 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define VERBOSE_ERR 0
# define MAP_SEP " "
# define PI 3.141592678
# define W_WIDTH 1920
# define W_HEIGHT 1080
# define NUM_OF_KEYS 20 // Change to number of keys added
# define R_SPEED 0.03
# define T_SPEED 10
# define S_SPEED 0.03

typedef struct s_data	t_data;

typedef struct s_map
{
	int					length;
	int					height;
	int					*arr;
}						t_map;

typedef union
{
	struct
	{
		float x, y, z, w;
	} f;
	float				arr[4];
}						u_vec4;

typedef union
{
	struct
	{
		float x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3, x4, y4, z4, w4;
	} f;
	float				arr[16];
}						u_tmatrix;

typedef void			(*t_key_func)(u_vec4 vec, u_tmatrix *tmat);

typedef struct s_key
{
	int					code;
	int					state;
	t_key_func			func;
	u_vec4				v;
	u_tmatrix			*matrix;
}						t_key;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	t_map				*map;
	u_tmatrix			tmatrices[2];
	t_key				keys[NUM_OF_KEYS];
}						t_data;

typedef struct s_ivec2
{
	int					x;
	int					y;
}						t_ivec2;

// typedef struct s_vec3
// {
//     float x;
//     float y;
// 	float z;
// }		t_vec3;

// draw.c
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
void					line_put(t_data *data, t_ivec2 a, t_ivec2 b, int color);

// init.c
int						init_keys(t_key *keys, u_tmatrix *tmatrices);
int						init_mlx(t_data *data);
void					init_tmatrices(u_tmatrix *tmatrices, t_map *map);

// hooks.c
int						loop_hook(t_data *data);
int						handle_keydown(int keycode, t_key *keys);
int						handle_keyup(int keycode, t_key *keys);

// matrix_utils.c
u_vec4					nv(float x, float y, float z);
u_tmatrix				rotation_m_x(float angle);
u_tmatrix				rotation_m_y(float angle);
u_tmatrix				rotation_m_z(float angle);
u_tmatrix				scale_m(u_vec4 vec);
u_tmatrix				translate_m(u_vec4 vec);
u_tmatrix				perspec_project_m(float n, float f);
u_vec4					perspec_div(u_vec4 vec);
u_tmatrix				multiply_tmats(u_tmatrix mat1, u_tmatrix mat2);

// oper.c
void					rotate(u_vec4 v, u_tmatrix *matrix);
void					translate(u_vec4 v, u_tmatrix *matrix);
void					scale(u_vec4 v, u_tmatrix *matrix);

// parse.c
t_map					*parse_map(int fd);

// render.c
void					render_map(t_data *data);

#endif