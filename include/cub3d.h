/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:01:15 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/27 19:13:45 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define COLOR 0x00FFFFFF
# define MAP_SEP " "
# define W_WIDTH 1280
# define W_HEIGHT 720
# define NUM_OF_KEYS 7 // Change to number of keys added
# define R_SPEED 0.03
# define T_SPEED 10
# define S_SPEED 0.03
# define PI 3.14159265358979323
# define EPSILON 0.000001
# define SCALE 70
# define MAX_RAY 3000

# define WHITESPACE " \t\n\r\v\f"
# define NUNERIC "0123456789"

# define COLLISION true
# define PRINT_FPS false

typedef struct s_data	t_data;
typedef struct s_map	t_map;

typedef struct s_dvec2
{
	double				x;
	double				y;
}						t_dvec2;

typedef struct s_color_value
{
	unsigned int		r;
	unsigned int		g;
	unsigned int		b;
}						t_color_value;

typedef struct s_rmd
{
	char				*line;
	char				*content;
	int					location;
}						t_rmd;

typedef struct s_player
{
	t_dvec2				position;
	t_dvec2				orientation;
	double				movement_speed;
	double				look_speed;
	t_map				*map;
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
	char				*path_no;
	char				*path_so;
	char				*path_we;
	char				*path_ea;
	unsigned int		col_f;
	unsigned int		col_c;
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
typedef struct s_move_args
{
	t_player			*player;
	t_dvec2				direction;
}						t_move_args;

// Look/rotate function arguments
typedef struct s_look_args
{
	t_player			*player;
	double				rotation;
}						t_look_args;

// Union to store different types of function arguments
// Last entry is  a generic pointer (for other use cases)
typedef union u_args
{
	t_move_args			move_args;
	t_look_args			look_args;
	void				*ptr;
}						t_args;

// Define the key structure
typedef struct s_key
{
	int					code;
	int					state;
	void				(*func)(t_data *data, void *);
	t_args				args;
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
	struct timeval		lastframe;
	unsigned int		delta_time;
	bool				use_mouse;
	t_map				*map;
	t_player			*players;
	t_key				keys[NUM_OF_KEYS];
	int					fd;
}						t_data;

typedef struct s_ivec2
{
	int					x;
	int					y;
}						t_ivec2;

// check if this is norm
typedef enum e_direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}						t_direction;

typedef struct s_ray
{
	t_dvec2				start_pos;
	t_dvec2				hit_pos;
	double				angle;
	t_ivec2				sign;
	t_dvec2				delta;
	t_dvec2				vertical_intersection;
	t_dvec2				horizontal_intersection;
	bool				vert_hit;
	bool				hori_hit;
	t_direction			texture;
}						t_ray;

// minimap
typedef struct s_rect
{
	t_ivec2				start;
	t_ivec2				end;
	int					color;
}						t_rect;

typedef struct s_minimap
{
	int					size;
	int					scale;
	int					player_x;
	int					player_y;
	double				offset_x;
	double				offset_y;
}						t_minimap;

// debug.c
void					debug_render_textures(t_data *data, unsigned int count);
void					printmap(t_map *map);
void					printtexture_data(t_texture_data texture_data);
void					printray(t_ray ray);

// line.c
void					line_put(t_data *data, t_ivec2 a, t_ivec2 b, int color);

// draw.c
void					slice_put(t_data *data, int x, double size, double d_x,
							t_texture texture);

// pixel.c
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
int						get_pixel_color(t_texture texture, int x, int y);

// pixel.c
int						get_color_normalized(t_texture texture, double x,
							double y);
int						get_pixel_color(t_texture texture, int x, int y);
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);

// init.c
int						init_keys(t_key *keys, t_player *players);
int						init_mlx(t_data *data);
int						init_players(t_player **players, t_map *map);

// hooks.c
int						loop_hook(t_data *data);
int						handle_keydown(int keycode, t_key *keys);
int						handle_keyup(int keycode, t_key *keys);
void					delta_time(t_data *data);

// mouse.c
int						handle_mousemove(int x, int y, t_data *data);
int						handle_mouseclick(int button, int x, int y,
							t_data *data);

// main.c
void					free_and_exit(t_data *data, int code);

// oper.c
void					move(t_data *data, void *args);
void					look(t_data *data, void *args);

// # parse_1.c
t_texture_data			*get_texture_data(int fd);
t_map					*get_map(int fd, t_texture_data *texture_data);
t_map					*parse_map(int fd);

// # parse_2.c
int						procces_line2(char const *s, int **arr, int *i, int y);
int						fill_map2(char const *s, t_map *map, int **arr);
int						check_sides(int **arr, int height, int length);
int						check_middle(int **arr, int height, int length);
int						is_wall_enclosed(char *content, t_map *map);

// # parse_3.c
int						is_valid_char(char const s);
int						get_dir(char c);
int						count_players(t_map *map);
int						procces_line(char const *s, t_map *map, int *i, int y);
int						fill_map(char const *s, t_map *map);

// # parse_4.c
int						is_only_numeric_and_2_comma(char *str, int i);
int						gc_error_check(char *s);
int						get_color(char *s, unsigned int *color);
int						get_key(unsigned int *i, char *s, char **path);
int						key_val(char *line, t_texture_data *texture_data);

// # parse_5.c
int						read_texture_data(int fd, t_texture_data *texture_data);
char					*set_null(int *location);
char					*read_map_data(int fd, t_map *map);
int						**new_2d_int_arr(int rows, int cols);

// # parse_6.c
char					*ft_str_append(char *a, char *b);
int						count_words(char *str);
int						trim_spaces_at_end(char *str);
bool					is_only_whitespace(char *s);
int						skip_until(const char *str, unsigned int *i,
							const char *charset, bool val);
unsigned int			ft_to_int(char *str, unsigned int *i);

// render.c

// minimap.c
void					render_minimap(t_data *data);

// debug_minimap.c
void					render_map(t_data *data);
void					render_players(t_data *data);

// # utils.c

// free.c
void					free_2d_arr(void **arr, int rows);
void					free_map(t_map *map);
void					free_texture_data(t_texture_data *td);
void					gnl_clear_buffer(int fd);

// dda functions
double					get_fract_part(double x);
t_dvec2					get_horizontal_intersection(t_ray ray);
t_dvec2					get_vertical_intersection(t_ray ray);
t_ray					raycast(t_player player, t_map *map, double angle);
int						is_wall(t_dvec2 intersection, t_map *map);
double					deg2rad(double degrees);
double					rad2deg(double rad);
double					vec2angle(t_dvec2 vec);

void					gnl_clear_buffer(int fd);
void					render_wall(t_data *data);
void					render_walls(t_data *data);
void					render_minimap_rays(t_data *data);
double					vec2angle(t_dvec2 vec);

#endif