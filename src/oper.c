/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeniga@student.42vienna.com <tmeniga>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:23:53 by aprevrha          #+#    #+#             */
/*   Updated: 2024/10/28 15:47:19 by tmeniga@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>



t_dvec2 vec_dir(t_dvec2 dir, t_dvec2 v)
{
    t_dvec2 dir_vec;
    dir_vec.y = dir.y * v.y - dir.x * v.x;
    dir_vec.x = dir.x * v.y + dir.y * v.x;
    return (dir_vec);
}

int** createMap() {
    // Allocate memory for the map
    int** map = (int**)malloc(10 * sizeof(int*));
    for (int i = 0; i < 10; i++) {
        map[i] = (int*)malloc(10 * sizeof(int));
    }

    // Initialize the map with walls (0) and floors (1)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == 0 || i == 10 - 1 || j == 0 || j == 10 - 1) {
                map[i][j] = 0;  // Set walls (edges) to 0
            } else {
                map[i][j] = 1;  // Set floor (interior) to 1
            }
        }
    }

    return map;
}

int is_wall_tile(t_dvec2 pos, int **map)
{
    double x;
    double y;
    
    x = floor(pos.x);
    y = floor(pos.y);

    if (x < 0 || x  > 9 || y < 0 || y  > 9)
        return (1);
    if (map[(int)y][(int)x]) 
        return (1);
    return (0);
}

void move(t_data *data, void *args) 
{
    t_move_args *a = (t_move_args *)args;
    t_player *player = a->player;
    t_dvec2 direction = a->direction;
    t_dvec2 move_vec;
    
    // int **map;
    // map = createMap();
    // t_dvec2 temp;

    
    
    move_vec = vec_dir(player->orientation, direction);
    player->position.x += move_vec.x * player->movement_speed * data->delta_time;
    player->position.y += move_vec.y * player->movement_speed * data->delta_time;


    //printf("Moved player to position: (%f, %f)\n", 
        	// player->position.x, player->position.y);

    // temp.x += move_vec.x * player->movement_speed; 
    // temp.y += move_vec.y * player->movement_speed;
    // if (is_wall_tile(temp, map))
    //     return ;
    // player->position.x += move_vec.x * player->movement_speed; 
    // player->position.y += move_vec.y * player->movement_speed; 
}

double vec_length(t_dvec2 vec)
{
    return (sqrt(pow(fabs(vec.x), 2) + pow(fabs(vec.y), 2)));
}

t_dvec2 vec_rotate(double angle, t_dvec2 vec)
{
    t_dvec2 rotated_vec;
    double	cos_theta;
	double	sin_theta;

    cos_theta = cos(angle);
	sin_theta = sin(angle);

    rotated_vec.x = vec.x * cos_theta - vec.y * sin_theta;
    rotated_vec.y = vec.x * sin_theta + vec.y * cos_theta;
    return (rotated_vec);
}

void look(t_data *data, void *args) 
{
    t_look_args *a = (t_look_args *)args;
    t_player *player = a->player;
    double rotation = a->rotation;
    
    player->orientation = vec_rotate(rotation * player->look_speed * data->delta_time, player->orientation);
    // printf("Rotated player to: (%f, %f) len: %f\n", 
    // player->orientation.x, player->orientation.y, vec_length(player->orientation));
}