
#include "../include/cub3d.h"

void free_2d_arr(void **arr, int rows)
{
	int i;

	i = 0;
	while (i < rows)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


void free_texture_data(t_texture_data *td)
{
	free(td->path_NO);
	free(td->path_EA);
	free(td->path_SO);
	free(td->path_WE);
	free(td);
}

void free_map(t_map *map)
{
	free_2d_arr((void **)map->arr, map->height);
	free(map);
}