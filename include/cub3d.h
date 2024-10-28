/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:01:15 by aprevrha          #+#    #+#             */
/*   Updated: 2024/10/28 15:34:47 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
#include <sys/time.h> // gettimeofday()

# define COLOR 0x00FFFFFF
# define MAP_SEP " "
# define W_WIDTH 1920
# define W_HEIGHT 1080
# define NUM_OF_KEYS 7 // Change to number of keys added
# define R_SPEED 0.03
# define T_SPEED 10
# define S_SPEED 0.03
#define PI 3.14159265358979323
# define EPSILON 0.000001
# define SCALE 70



typedef struct s_data	t_data;
typedef struct s_map	t_map;


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
	t_map	*map;
}						t_player;

typedef struct s_texture
{
	char				*path;
	void				*img;
	void				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					img_width;
	int					img_height;
}						t_texture;

typedef struct s_texture_data
{
	char				*path_NO;
	char				*path_SO;
	char				*path_WE;
	char				*path_EA;
	unsigned int		col_F;
	unsigned int		col_C;
	t_texture			textures[4];
}						t_texture_data;

typedef struct s_map
{
	t_texture_data		*texture_data;
	int					length;
	int					height;
	int					**arr;
}						t_map;

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
	struct timeval		lastframe;
	t_map				*map;
	t_player			*players;
	t_key				keys[NUM_OF_KEYS];
}						t_data;

typedef struct s_ivec2
{
	int					x;
	int					y;
}						t_ivec2;

//debug.c
void 					printmap(t_map *map);
void					printtexture_data(t_texture_data texture_data);

// draw.c
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
void					line_put(t_data *data, t_ivec2 a, t_ivec2 b, int color);
int						get_pixel_color(t_texture texture, int x, int y);
void	slice_put(t_data *data, int x, double size, double d_x, t_texture texture);

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
void					render_players(t_data *data);

// utils.c

//free.c
void					free_2d_arr(void **arr, int rows);
void					free_map(t_map *map);
void					free_texture_data(t_texture_data *td);

// dda functions

double get_fract_part(double x);
double  get_hi_lenght(t_dvec2 position, double angle);
double  get_vi_lenght(t_dvec2 position, double angle);
t_dvec2 get_horizontal_intersection(t_dvec2 position, double angle);
t_dvec2 get_vertical_intersection(t_dvec2 position, double angle);
t_dvec2 get_intersection(t_player player, t_map *map, double angle);
int is_wall(t_dvec2 intersection, t_map *map);
double  deg2rad(double degrees);
double rad2deg(double rad);
double vec2angle(t_dvec2 vec);

void	render_half_screen(t_data *data);
void	render_wall(t_data *data);
void	render_walls(t_data *data);
void	render_minimap_rays(t_data *data);




#endif