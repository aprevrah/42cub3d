/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:34:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/06 19:12:53 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <X11/keysym.h>

typedef struct	s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map
{
	int	*arr;
	int	length;
	int	hight;
}				t_map;


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
}*/

int	close_win(int keycode, t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	return (0);
}

int	handle_keydown(int keycode, t_data *data)
{
	printf("Keycode: %i\n", keycode);
	if (keycode == XK_Escape)
		mlx_destroy_window(data->mlx, data->win);
	return (0);
}

char	*str_append(char *a, char *b)
{
	char	*str;
	str = ft_strjoin(a, b);
	free(a);
	free(b);
	if (!str)
		return (NULL);
	return (a = NULL, b = NULL, str);
}

unsigned int	count_token(char *str, char c)
{
	unsigned int	i;
	unsigned int	count;
	int				in_token;

	i = 0;
	in_token = 0;
	count = 0;
	while (str[i])
	{
		if (!in_token && str[i] != c)
		{
			in_token = 1;
			count++;
		}
		else if (in_token && str[i] == c)
		{
			in_token = 0;
		}
		i++;
	}
	return (count);
}

void	*parse_map(int	fd)
{
	char	*line;
	char	*content;
	t_map	map;

	map.hight = 0;
	map.length = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!content)
		{
			map.length = count_token(line, ' ');
			content = ft_strdup(line);
			free(line);
		}
		else
			content = str_append(content, line);
	}
	printf("\n%s\n", content);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	data;
	int		fd;

	if (argc > 2)
		return (1);
	if (argv)
		printf("av\n");
	fd = open(argv[1], O_RDONLY);
	

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	my_mlx_pixel_put(&data, 5, 5, 0x00FF0000);
	line_put(&data, 10, 10, 100, 50, 0x00FF0000);
	line_put(&data, 10, 30, 50, 200, 0x00FF0000);
	line_put(&data, 900, 600, 50, 200, 0x00FF0000);
	parse_map(fd);

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	close(fd);
	mlx_hook(data.win, 2, 1L<<0, handle_keydown, &data);
	mlx_hook(data.win, 17, 0, close_win, &data);
	mlx_loop(data.mlx);
}
