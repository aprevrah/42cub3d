/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:34:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/28 18:31:56 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	free_and_exit(t_data *data, int code)
{
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

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (argc > 2)
		return (ft_printf("No map arg!"), 1);
	fd = open(argv[1], O_RDONLY);
	data.map = parse_map(fd);
	close(fd);
	if (!init_mlx(&data))
		free_and_exit(&data, 1);
	init_tmatrices(data.tmatrices, data.map);
	render_map(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	init_keys(data.keys, data.tmatrices);
	mlx_hook(data.win, 2, KeyPressMask, handle_keydown, data.keys);
	mlx_hook(data.win, 3, KeyReleaseMask, handle_keyup, data.keys);
	mlx_hook(data.win, 17, StructureNotifyMask, win_close_button, &data);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
}
