/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:01:15 by aprevrha          #+#    #+#             */
/*   Updated: 2024/10/02 18:54:12 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define COLOR 0x00FFFFFF
# define MAP_SEP " "
# define W_WIDTH 1920
# define W_HEIGHT 1080
# define NUM_OF_KEYS 7 // Change to number of keys added
# define R_SPEED 0.03
# define T_SPEED 10
# define S_SPEED 0.03

typedef struct s_data	t_data;

typedef struct s_dvec2
{
	double					x;
	double					y;
}						t_dvec2;

typedef struct s_player
{
	t_dvec2 position;
	t_dvec2	orientation;
	double	movement_speed;
}						t_player;

typedef struct s_map
{
	char				*path_NO;
	char				*path_SO;
	char				*path_WE;
	char				*path_EA;
	int					col_F;
	int					col_C;
	int					length;
	int					height;
	int					**arr;
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

// Move function arguments
typedef struct s_move_args {
    t_player *player;
    t_dvec2 direction;
} t_move_args;

// Look/rotate function arguments
typedef struct s_look_args {
    t_player *player;
    double rotation;
} t_look_args;

// Union to store different types of function arguments
typedef union u_args {
    t_move_args move_args;  // Move arguments
    t_look_args look_args;  // Look/rotate arguments
    void *ptr;              // Generic pointer (for other use cases)
} u_args;

// Define the key structure
typedef struct s_key {
    int        code;
    int        state;
    void       (*func)(void *); // Function pointer to different actions
    u_args     args;            // Union to hold function-specific arguments
} t_key;

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
	t_player			*players;
	t_key				keys[NUM_OF_KEYS];
}						t_data;

typedef struct s_ivec2
{
	int					x;
	int					y;
}						t_ivec2;

// draw.c
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
void					line_put(t_data *data, t_ivec2 a, t_ivec2 b, int color);

// init.c
int						init_keys(t_key *keys, t_player *players);
int						init_mlx(t_data *data);
int						init_players(t_player **players, t_map *map);

// hooks.c
int						loop_hook(t_data *data);
int						handle_keydown(int keycode, t_key *keys);
int						handle_keyup(int keycode, t_key *keys);

// main.c
void					free_and_exit(t_data *data, int code);

// oper.c
void					move(void *args);
void					look(void *args);

// parse.c
t_map					*parse_map(int fd);

// render.c
void					render_map(t_data *data);

// utils.c
t_vec4					nv(float x, float y, float z);
t_vec4					left_multiply(t_tmatrix mat, t_vec4 vec);
t_tmatrix				multiply_tmats(t_tmatrix mat1, t_tmatrix mat2);

#endif