/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:34:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/10/25 19:24:18 by tmeniga@stu      ###   ########.fr       */
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
	// if (data->players)
	// 	free(data->players);
	if (data->map)
	{
		if (data->map->arr)
			free(data->map->arr);
		free(data->map);
	}
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

int	file_type_matches(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (argc != 2)
		return (ft_printf("(Only) one argument needed.\n"), 1);
	if (!file_type_matches(argv[1]))
		return (ft_printf("Wrong filetype, \".cub\" needed.\n"), 1);
	fd = open(argv[1], O_RDONLY);
	data.map = parse_map(fd);
	close(fd);

	if (init_players(&data.players, data.map))
		free_and_exit(&data, 1);
	
	t_dvec2 intersection;
	// t_dvec2 v_i;
	// t_dvec2 h_i;

	//intersection = get_intersection(data.players[0], data.map, vec2angle(data.players[0].orientation));
	//printf("x = %lf, y = %lf\n", intersection.x, intersection.y);
	
	// v_i = get_vertical_intersection(data.players[0].position, vec2angle(data.players[0].orientation));
	// h_i = get_horizontal_intersection(data.players[0].position, vec2angle(data.players[0].orientation));
	
	// printf("x_v = %lf , y_v = %lf\n", v_i.x, v_i.y);
	// printf("x_h = %lf , y_h = %lf\n", h_i.x, h_i.y);
	intersection.x = 0.5;
	intersection.y = 0.5;
	
	if (is_wall(intersection, data.map) )
		printf("wall");
	else
	 	printf("no wall");

	// if (init_mlx(&data))
	// 	free_and_exit(&data, 1);
	// render_map(&data);
	// mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	// init_keys(data.keys, data.players);
	// mlx_hook(data.win, 2, KeyPressMask, handle_keydown, data.keys);
	// mlx_hook(data.win, 3, KeyReleaseMask, handle_keyup, data.keys);
	// mlx_hook(data.win, 17, StructureNotifyMask, win_close_button, &data);
	// mlx_loop_hook(data.mlx, loop_hook, &data);
	// mlx_loop(data.mlx);
}
