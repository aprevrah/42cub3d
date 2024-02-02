/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:34:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/02 16:38:04 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <fcntl.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	line_put(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	int		i;
	int		dx;
	int		dy;
	float	m;

	if (x1 > x2)
	{
		i = x1;
		x1 = x2;
		x2 = i;
		i = y1;
		y1 = y2;
		y2 = i;
	}
	if (y1 > y2)
	{
		i = x1;
		x1 = x2;
		x2 = i;
		i = y1;
		y1 = y2;
		y2 = i;
	}
	dx = x2 - x1;
	dy = y2 - y1;
	m = (float)dy / dx;

	if (m < 1 && m > -1)
	{
		i = 0;
		while(i <= dx)
		{
			my_mlx_pixel_put(data, x1 + i, y1 + (m * i), color);
			i++;
		}
	}
	else
	{
		m = (float)dx / dy;
		i = 0;
		while(i <= dy)
		{
			my_mlx_pixel_put(data, x1 + (m * i), y1 + i, color);
			i++;
		}
	}
}

/* 
int	has_extension(char * fname, char *fextension)
{
	ft_strrchr(fname)
	ft_strc
}
*/


int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		fd;
	//int	i;

	if (argc != 1)
		return (1);
	if (argv)
		printf("av");
	fd = open(argv[1], O_RDONLY);
	

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	line_put(&img, 10, 10, 100, 50, 0x00FF0000);
	line_put(&img, 10, 30, 50, 200, 0x00FF0000);
	line_put(&img, 900, 600, 50, 200, 0x00FF0000);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	close(fd);
	mlx_loop(mlx);
}
