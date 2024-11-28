/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:34:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/11/20 12:15:46 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	free_and_exit(t_data *data, int code)
{
	if (data->players)
		free(data->players);
	get_next_line(data->fd, 1);
	if (data->map && data->map->texture_data)
	{
		if (data->map->texture_data->textures[0].img)
			mlx_destroy_image(data->mlx,
				data->map->texture_data->textures[0].img);
		if (data->map->texture_data->textures[1].img)
			mlx_destroy_image(data->mlx,
				data->map->texture_data->textures[1].img);
		if (data->map->texture_data->textures[2].img)
			mlx_destroy_image(data->mlx,
				data->map->texture_data->textures[2].img);
		if (data->map->texture_data->textures[3].img)
			mlx_destroy_image(data->mlx,
				data->map->texture_data->textures[3].img);
		free_texture_data(data->map->texture_data);
	}
	if (data->map)
		free_map(data->map);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(code);
}

int	win_close_button(t_data *data)
{
	free_and_exit(data, 0);
	return (0);
}

int	is_file_extension(char *filename, char *extension)
{
	int	len;
	int	extension_len;

	len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (len < extension_len)
		return (0);
	if (ft_strncmp(filename + len - extension_len, extension, extension_len))
		return (0);
	return (1);
}

int	load_texture(char *path, t_data *data, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path, &texture->img_width,
			&texture->img_height);
	if (!texture->img)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
		return (1);
	return (0);
}

void	init2null(t_data *data)
{
	struct timeval	tv_now;
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->map = NULL;
	data->players = NULL;
	data->use_mouse = false;
	if (gettimeofday(&tv_now, NULL))
		printf("gettimeofday failed");
	data->lastframe = tv_now;
	// data->map->texture_data = NULL;
	// data->map->texture_data->path_no = NULL;
	// data->map->texture_data->path_so = NULL;
	// data->map->texture_data->path_we = NULL;
	// data->map->texture_data->path_ea = NULL;
	// data->map->arr = NULL;
}
#include <locale.h>


int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;
	
	setlocale(LC_ALL, "");
	init2null(&data);
	if (argc != 2)
		return (ft_printf("(Only) one argument needed.\n"), 1);
	if (!is_file_extension(argv[1], ".cub"))
		return (ft_printf("Wrong filetype, \".cub\" needed.\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	data.fd = fd;
	data.map = parse_map(fd);
	close(fd);
	if (!data.map)
		free_and_exit(&data, 1);
	if (init_players(&data.players, data.map))
		free_and_exit(&data, 1);
	// free_and_exit(&data, 1);
	if (init_mlx(&data))
		free_and_exit(&data, 1);
	// free_and_exit(&data, 1);
	render_map(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	init_keys(data.keys, data.players);
	mlx_hook(data.win, 2, KeyPressMask, handle_keydown, data.keys);
	mlx_hook(data.win, 3, KeyReleaseMask, handle_keyup, data.keys);
	mlx_hook(data.win, 17, StructureNotifyMask, win_close_button, &data);
	mlx_hook(data.win, MotionNotify, PointerMotionMask, handle_mousemove,
		&data);
	mlx_mouse_hook(data.win, handle_mouseclick, &data);
	// test texture
	// printtexture_data(*data.map->texture_data);
	load_texture(data.map->texture_data->path_no, &data,
		&data.map->texture_data->textures[0]);
	load_texture(data.map->texture_data->path_ea, &data,
		&data.map->texture_data->textures[1]);
	load_texture(data.map->texture_data->path_so, &data,
		&data.map->texture_data->textures[2]);
	load_texture(data.map->texture_data->path_we, &data,
		&data.map->texture_data->textures[3]);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
	free_and_exit(&data, 1);
}
