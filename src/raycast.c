#include "../include/cub3d.h"

double squared_distance(t_dvec2 p1, t_dvec2 p2)
{
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

t_dvec2 closer_to_p1(t_dvec2 p1, t_dvec2 p2, t_dvec2 p3)
{
    double dist_p2 = squared_distance(p1, p2);
    double dist_p3 = squared_distance(p1, p3);

    if (dist_p2 < dist_p3)
        return (p2);
    else
        return (p3);
}

double get_fract_part(double x)
{
    double int_part;
    double frac_part;

    frac_part = modf(x, &int_part);

    return (frac_part);
}

t_dvec2 get_horizontal_intersection(t_ray ray)
{
    t_dvec2 intersection;
    double  d_y;
    double  d_x;
    t_dvec2 position = ray.start_pos;

    // Use fabs to check if the difference is within a small range (epsilon) // ! change
    if (fabs(ray.angle - 0) < EPSILON || fabs(ray.angle - PI) < EPSILON)
    {
        intersection.x = position.x;
        intersection.y = floor(position.y) + (ray.sign.y  - 1) / 2;
        return (intersection);
    }

    if (ray.sign.y == -1)
    {
        d_x = get_fract_part(position.y) / fabs(tan(ray.angle));
        d_y = get_fract_part(position.y);
    }
    else
    {
        d_x = ((1 - get_fract_part(position.y)) / fabs(tan(ray.angle)));
        d_y = 1 - get_fract_part(position.y);
    }

    if (ray.angle == PI/2 || ray.angle == 3*PI/2)
        intersection.x = ray.start_pos.x;
    else
        intersection.x = ray.start_pos.x + ray.sign.x * d_x;
    intersection.y = ray.start_pos.y + ray.sign.y * d_y;

    return (intersection);
}

t_dvec2 get_vertical_intersection(t_ray ray)
{
    t_dvec2 intersection;
    double  d_x;
    double  d_y;
    t_dvec2 position = ray.start_pos;

    // Use fabs to check if the difference is within a small range (epsilon) // ! change
    if (fabs(ray.angle - PI/2) < EPSILON || fabs(ray.angle - 3*PI/2) < EPSILON)
    {
        intersection.x = floor(position.x) + (ray.sign.x  - 1) / 2;
        intersection.y = position.y;
        return (intersection);
    }
    if (ray.sign.x == -1)
    {
        d_y = get_fract_part(position.x) * fabs(tan(ray.angle));
        d_x = get_fract_part(position.x);
    }
    else
    {
        d_y = ((1 - get_fract_part(position.x)) * fabs(tan(ray.angle)));
        d_x = 1 - get_fract_part(position.x);
    }


    if (ray.angle == 0 || ray.angle == PI)
        intersection.y = position.y;
    else
        intersection.y = position.y + ray.sign.y * d_y;
    intersection.x = position.x + ray.sign.x * d_x;

    return (intersection);
}

double  get_dx(double angle)
{
    if (angle == PI/2 || angle == 3*PI/2)
        return (1);
    if (angle == 0 || angle == PI)
        return (0);
    return (1 / tan(angle)); 
}

double get_dy(double angle)
{
    if (angle == PI/2 || angle == 3*PI/2)
        return (0);
    if (angle == 0 || angle == PI)
        return (1);
    return (tan(angle));
}

double vec2angle(t_dvec2 vec)
{
    double angle;

    angle = atan2( -1 * vec.y, vec.x); 

    if (angle == 0)
        return (0);
    if (angle < 0)
        angle = 2*PI + angle;

    return (angle);
}

int smart_is_wall(t_map *map, t_dvec2 intersection, int x_i, int y_i, bool horizontal)
{
    double x;
    double y;
    x = intersection.x;
    y = intersection.y;
    (void)x_i;
    (void)y_i;

    if (x < 0 || y < 0 || x >= map->length || y >= map->height)
        return (0);

    if (!horizontal)//!get_fract_part(x) && get_fract_part(y))
    {   
        //y = floor(y);
        if (!map->arr[(int)y][(int)x] || ((x-1) >= 0 && !map->arr[(int)y][(int)x-1]))
            return (1);
    }
    else if (horizontal)//!get_fract_part(y) && get_fract_part(x))
    {
        //x = floor(x);
        if (!map->arr[(int)y][(int)x] || ((y-1) >= 0 && !map->arr[(int)y-1][(int)x]))
            return (1);
    }
    // else if (!get_fract_part(x) && !get_fract_part(y))
    // {
    //      if (!map->arr[(int)y][(int)x] || ((x-1) >= 0 && !map->arr[(int)y][(int)x-1]) || ((y-1) >= 0 && !map->arr[(int)y-1][(int)x]) 
    //      ||  ((y-1) >= 0 && (x-1) >= 0 && !map->arr[(int)y-1][(int)x-1]))
    //          return (1);
    // }
    return (0);
}

void set_sign(t_ray *ray)
{
    if (ray->angle > PI/2 && ray->angle < 3*PI/2)
        ray->sign.x = -1;
    else
        ray->sign.x = 1;

    if (ray->angle > 0 && ray->angle < PI)
        ray->sign.y = -1;
    else
        ray->sign.y = 1;
}

void ray_cal_hit_and_dir(t_ray *ray)
{

    if (squared_distance(ray->start_pos, ray->vertical_intersection) < squared_distance(ray->start_pos, ray->horizontal_intersection))
    {
        ray->hit_pos = ray->vertical_intersection;
        if (ray->sign.x == 1)
            ray->texture = WEST;
        else
            ray->texture = EAST;
    }
    else
    {
         ray->hit_pos = ray->horizontal_intersection;
         if (ray->sign.y == 1)
            ray->texture = NORTH;
        else
            ray->texture = SOUTH;
    }
}

t_ray raycast(t_player player, t_map *map, double angle)
{
    t_ray   ray;
    int i;
    
    ray.start_pos = player.position;
    ray.angle = angle;
    set_sign(&ray);
    ray.delta.x = get_dx(angle);
    ray.delta.y = get_dy(angle);

    /* //TODO: rethink this hacky bs... this method creates visual bugs when out of map and look dir {1, 0}
    ray.horizontal_intersection = (t_dvec2){ray.start_pos.x + MAX_RAY, ray.start_pos.y + MAX_RAY};
    ray.vertical_intersection = (t_dvec2){ray.start_pos.x + MAX_RAY, ray.start_pos.y + MAX_RAY};
    //TODO: We do need this but it could be in the loops below?
    if (angle == PI/2 || angle == 3*PI/2)
    {
        ray.horizontal_intersection = get_horizontal_intersection(ray);
        i = 0;
        while (i < MAX_RAY)
        {
            if (smart_is_wall(map, ray.horizontal_intersection, ray.sign.x, ray.sign.y, true))
                return (ray_cal_hit_and_dir(&ray, ray.vertical_intersection, ray.horizontal_intersection), ray);
            ray.horizontal_intersection.y += ray.sign.y;
            i++;
        }
    }
    else if (angle == 0 || angle == PI)
    {
        ray.vertical_intersection = get_vertical_intersection(ray);
        i = 0;
        while (i < MAX_RAY)
        {
            if (smart_is_wall(map, ray.vertical_intersection, ray.sign.x, ray.sign.y, false))
                return (ray_cal_hit_and_dir(&ray, ray.vertical_intersection, ray.horizontal_intersection), ray);
            ray.vertical_intersection.x += ray.sign.x;
            i++;
        }
    } */

    ray.vertical_intersection = get_vertical_intersection(ray);
    ray.horizontal_intersection = get_horizontal_intersection(ray);

    //TODO: can we do with one loop?
    i = 0;
    
    while (i < MAX_RAY && ray.delta.x != 0)
    {
        if (smart_is_wall(map, ray.vertical_intersection, ray.sign.x, ray.sign.y, false))
            break;
        ray.vertical_intersection.x += ray.sign.x;
        ray.vertical_intersection.y += fabs(ray.delta.y) * ray.sign.y;
        i++;
    }
    if (ray.delta.x == 0)
    {
        ray.vertical_intersection.y = 100000;
        ray.vertical_intersection.x = 100000;
        //printf("i = %i\n", i);
    }
        
    i = 0;
    while (i < MAX_RAY && ray.delta.y != 0)
    {
        if (smart_is_wall(map, ray.horizontal_intersection, ray.sign.x, ray.sign.y, true))
            break;
        ray.horizontal_intersection.x += fabs(ray.delta.x) * ray.sign.x;
        ray.horizontal_intersection.y += ray.sign.y;
        i++;
    }
    if (ray.delta.y == 0)
    {
       // printf("i = %i\n", i);
        ray.vertical_intersection.y = 100000;
        ray.vertical_intersection.x = 100000;
        //printf("x_v = %lf , y_v = %lf\n", ray.vertical_intersection.x, ray.vertical_intersection.y);
        //printf("x_h = %lf , y_h = %lf\n", ray.horizontal_intersection.x, ray.horizontal_intersection.y);
        //printf("\n");
    }

    // printf("x_v = %lf , y_v = %lf\n", ray.vertical_intersection.x, ray.vertical_intersection.y);
    // printf("x_h = %lf , y_h = %lf\n", ray.horizontal_intersection.x, ray.horizontal_intersection.y);
    // ray.hit_pos = closer_to_p1(ray.start_pos, ray.vertical_intersection, ray.horizontal_intersection);
    ray_cal_hit_and_dir(&ray); 
    return (ray);
}

/* 
double  deg2rad(double degrees)
{
    return (PI * degrees / 180);
}

double rad2deg(double rad)
{
    return (rad * 180 / PI);
}
*/