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

int is_wall(t_dvec2 intersection, t_map *map)
{
    double x;
    double y;
    
    int x_max = map->length;
    int y_max = map->height;
    
    x = intersection.x;
    y = intersection.y;

    if (x < 0 || y < 0 || x >= x_max || y >= y_max)
        return (0);

    if (!get_fract_part(x) && get_fract_part(y))
    {   
        y = floor(y);

        if (!map->arr[(int)y][(int)x] || ((x-1) >= 0 && !map->arr[(int)y][(int)x-1]))
            return (1);
    }
    else if (!get_fract_part(y) && get_fract_part(x))
    {
        x = floor(x);
        if (!map->arr[(int)y][(int)x] || ((y-1) >= 0 && !map->arr[(int)y-1][(int)x]))
            return (1);
    }
    else if (!get_fract_part(x) && !get_fract_part(y))
    {
        if (!map->arr[(int)y][(int)x] \
        || ((x-1) >= 0 && !map->arr[(int)y][(int)x-1]) \
        || ((y-1) >= 0 && !map->arr[(int)y-1][(int)x]) \
        ||  ((y-1) >= 0 && (x-1) >= 0 && !map->arr[(int)y-1][(int)x-1]))
            return (1);
    }
    return (0);
}

double get_fract_part(double x)
{
    double int_part;
    double frac_part;

    frac_part = modf(x, &int_part);

    return (frac_part);
}

// # c = (1 - py) / sin() 
// # function returns lenght from position to next horizontal intersection
// # returns (0) if no intersection
double  get_hi_lenght(t_dvec2 position, double angle)
{
    double c;
    
    if (fabs(sin(angle)) < EPSILON)
        return (0);
    c = fabs((1 - get_fract_part(position.y)) / sin(angle));
    return (c);
}

// # c = (1 - px) / cos()
// # function returns length from position to next vertical intersection
// # returns (0) if no intersection
double  get_vi_lenght(t_dvec2 position, double angle)
{
    double c;
    if (fabs(cos(angle)) < EPSILON)
        return (0);
    c = fabs((1 - get_fract_part(position.x)) / cos(angle));
    return (c);
}

t_dvec2 get_horizontal_intersection(t_ray ray)
{
    t_dvec2 intersection;
    //int     x_multiple;
    //int     y_multiple;
    double  d_y;
    double  d_x;
    t_dvec2 position = ray.start_pos;

    // if (ray.angle > PI/2 && ray.angle < 3*PI/2)
    //     x_multiple = -1;
    // else
    //     x_multiple = 1;
    // if (ray.angle > 0 && ray.angle < PI)
    //     y_multiple = -1;
    // else
    //     y_multiple = 1;

    //if (ray.angle > 0 && ray.angle < PI)
    //    d_x = get_fract_part(position.y) / fabs(tan(ray.angle));
    //else
    //    d_x = ((1 - get_fract_part(position.y)) / fabs(tan(ray.angle)));
    //
    //if (ray.angle > 0 && ray.angle < PI)
    //    d_y = get_fract_part(position.y);
    //else
    //    d_y = 1 - get_fract_part(position.y);

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
    //int     x_multiple;
    //int     y_multiple;
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

    // if (ray.angle > PI/2 && ray.angle < 3*PI/2)
    //     x_multiple = -1;
    // else
    //     x_multiple = 1;
    // if (ray.angle > 0 && ray.angle < PI)
    //     y_multiple = -1;
    // else
    //     y_multiple = 1;


    // if (ray.angle > PI/2 && ray.angle < 3*PI/2)
    //     d_y = get_fract_part(position.x) * fabs(tan(ray.angle));
    // else
    //     d_y = ((1 - get_fract_part(position.x)) * fabs(tan(ray.angle)));

    // if (ray.angle > PI/2 && ray.angle < 3*PI/2)
    //     d_x = get_fract_part(position.x);
    // else
    //     d_x = 1 - get_fract_part(position.x);

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

// bool smart_is_wall_x(t_map *map, int x, int y, int x_i)
// {
    
//         if (x < 0 || y < 0 || x >= map->length || y >= map->height)
//             return (false);
//         if (x_i == -1 && !map->arr[y][x-1])
//             return (true);
//         if (y_i == -1 && !map->arr[y-1][x])
//             return (true);
//         if (!map->arr[y][x])
//             return (true);
//         return false;
// }

// bool smart_is_wall(t_map *map, int x, int y, int x_i, int y_i)
// {
    
//         if (x < 0 || y < 0 || x >= map->length || y >= map->height)
//             return (false);
//         if (x_i == -1 && !map->arr[y][x-1])
//             return (true);
//         if (y_i == -1 && !map->arr[y-1][x])
//             return (true);
//         if (!map->arr[y][x])
//             return (true);
//         return false;
// }
// bool is_vertical_wall()
// {
    
// }

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

t_ray raycast(t_player player, t_map *map, double angle)
{
    t_ray   ray;
    //put this in ray where it makes sense
    t_dvec2 vertical_intersection;
    t_dvec2 horizontal_intersection;
    //double d_x;
    //double d_y;
    int i;
    
    ray.start_pos = player.position;
    ray.angle = angle;
    set_sign(&ray);

    ray.delta.x = get_dx(angle);
    ray.delta.y = get_dy(angle);

    //TODO: We do need this but it could be in the loops below?

    // if (angle == PI/2 || angle == 3*PI/2)
    // {
    //     horizontal_intersection = get_horizontal_intersection(ray.start_pos, angle);
    //     return (horizontal_intersection);
    //     //TODO: this is an end less loop when angle is PI/2 or ... having the max ray is a temp fix -> rethink iswall()
    //     i = 0;
    //     while (i < MAX_RAY)
    //     {
    //         if (smart_is_wall(map, horizontal_intersection, ray.sign.x, y_i, true))
    //             return (horizontal_intersection);
    //         horizontal_intersection.y += y_i;
    //         i++;
    //     }
    // }
    // if (angle == 0 || angle == PI)
    // {
    //     vertical_intersection = get_vertical_intersection(ray.start_pos, angle);
    //     //TODO: this is an end less loop when angle is PI or 0 having the max ray is a temp fix -> rethink iswall()
    //     i = 0;
    //     while (i < MAX_RAY)
    //     {
    //         if (smart_is_wall(map, vertical_intersection, ray.sign.x, y_i, false)) //horizotal and vertical mix up here fixed
    //             return (vertical_intersection);
    //         vertical_intersection.x += ray.sign.x;
    //         i++;
    //     }
    // }

    vertical_intersection = get_vertical_intersection(ray);
    horizontal_intersection = get_horizontal_intersection(ray);

    //TODO: can we do with one loop?
    i = 0;
    while (i < MAX_RAY)
    {
        if (smart_is_wall(map, vertical_intersection, ray.sign.x, ray.sign.y, false))
            break;
        vertical_intersection.x += ray.sign.x;
        vertical_intersection.y += fabs(ray.delta.y) * ray.sign.y;
        i++;
    }

    i = 0;
    while (i < MAX_RAY)
    {
        if (smart_is_wall(map, horizontal_intersection, ray.sign.x, ray.sign.y, true))
            break;
        horizontal_intersection.x += fabs(ray.delta.x) * ray.sign.x;
        horizontal_intersection.y += ray.sign.y;
        i++;
    }

    // printf("x_v = %lf , y_v = %lf\n", vertical_intersection.x, vertical_intersection.y);
    // printf("x_h = %lf , y_h = %lf\n", horizontal_intersection.x, horizontal_intersection.y);
    // ray.hit_pos = closer_to_p1(ray.start_pos, vertical_intersection, horizontal_intersection);
    if (squared_distance(ray.start_pos, vertical_intersection) < squared_distance(ray.start_pos, horizontal_intersection))
    {
        ray.hit_pos = vertical_intersection;
        if (ray.sign.x == 1)
            ray.texture = WEST;
        else
            ray.texture = EAST;
    }
    else
    {
         ray.hit_pos = horizontal_intersection;
         if (ray.sign.y == 1)
            ray.texture = NORTH;
        else
            ray.texture = SOUTH;
    }
    return (ray);
}

double  deg2rad(double degrees)
{
    return (PI * degrees / 180);
}

double rad2deg(double rad)
{
    return (rad * 180 / PI);
}