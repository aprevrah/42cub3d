/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:01:15 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/28 18:13:58 by aprevrha         ###   ########.fr       */
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
# define NUM_OF_KEYS 13 // Change to number of keys added
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

typedef union u_vec4
{
	struct				s_vec4_f
	{
		float			x;
		float			y;
		float			z;
		float			w;
	} f;
	float				arr[4];
}						t_vec4;

typedef union u_tmatrix
{
	struct				s_tmatrix_f
	{
		float			x1;
		float			y1;
		float			z1;
		float			w1;
		float			x2;
		float			y2;
		float			z2;
		float			w2;
		float			x3;
		float			y3;
		float			z3;
		float			w3;
		float			x4;
		float			y4;
		float			z4;
		float			w4;
	} f;
	float				arr[16];
}						t_tmatrix;

typedef void			(*t_key_func)(t_vec4 vec, t_tmatrix *tmat);

typedef struct s_key
{
	int					code;
	int					state;
	t_key_func			func;
	t_vec4				v;
	t_tmatrix			*matrix;
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
	t_tmatrix			tmatrices[2];
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
int						init_keys(t_key *keys, t_tmatrix *tmatrices);
int						init_mlx(t_data *data);
void					init_tmatrices(t_tmatrix *tmatrices, t_map *map);

// hooks.c
int						loop_hook(t_data *data);
int						handle_keydown(int keycode, t_key *keys);
int						handle_keyup(int keycode, t_key *keys);

// main.c
void					free_and_exit(t_data *data, int code);

// matrix_affine.c
t_tmatrix				rotation_m_x(float angle);
t_tmatrix				rotation_m_y(float angle);
t_tmatrix				rotation_m_z(float angle);
t_tmatrix				scale_m(t_vec4 vec);
t_tmatrix				translate_m(t_vec4 vec);

// matrix_utils.c
t_vec4					nv(float x, float y, float z);
t_vec4					left_multiply(t_tmatrix mat, t_vec4 vec);
t_tmatrix				perspec_project_m(float n, float f);
t_vec4					perspec_div(t_vec4 vec);
t_tmatrix				multiply_tmats(t_tmatrix mat1, t_tmatrix mat2);

// oper.c
void					rotate(t_vec4 v, t_tmatrix *matrix);
void					translate(t_vec4 v, t_tmatrix *matrix);
void					scale(t_vec4 v, t_tmatrix *matrix);

// parse.c
t_map					*parse_map(int fd);

// render.c
void					render_map(t_data *data);

#endif