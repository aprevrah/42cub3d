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

t_dvec2 get_horizontal_intersection(t_dvec2 position, double angle)
{
    t_dvec2 intersection;
    int     x_multiple;
    int     y_multiple;
    double  d_y;
    double  d_x ;

    if (angle > PI/2 && angle < 3*PI/2)
        x_multiple = -1;
    else
        x_multiple = 1;
    if (angle > 0 && angle < PI)
        y_multiple = -1;
    else
        y_multiple = 1;

    if (angle > 0 && angle < PI)
        d_x = get_fract_part(position.y) / fabs(tan(angle));
    else
        d_x = ((1 - get_fract_part(position.y)) / fabs(tan(angle)));

    if (angle > 0 && angle < PI)
        d_y = get_fract_part(position.y);
    else
        d_y = 1 - get_fract_part(position.y);

 
    if (fabs(angle - 0) < EPSILON || fabs(angle - PI) < EPSILON)
    {
        intersection.x = -1;
        intersection.y = -1;
        return (intersection);
    }

    if (angle == PI/2 || angle == 3*PI/2)
        intersection.x = position.x;
    else
        intersection.x = position.x + x_multiple * d_x;
    intersection.y = position.y + y_multiple * d_y;

    return (intersection);
}

t_dvec2 get_vertical_intersection(t_dvec2 position, double angle)
{
    t_dvec2 intersection;
    int     x_multiple;
    int     y_multiple;
    double  d_x;
    double  d_y;

    // Use fabs to check if the difference is within a small range (epsilon) // ! change
    if (fabs(angle - PI/2) < EPSILON || fabs(angle - 3*PI/2) < EPSILON)
    {
        intersection.x = -1;
        intersection.y = -1;
        return (intersection);
    }

    if (angle > PI/2 && angle < 3*PI/2)
        x_multiple = -1;
    else
        x_multiple = 1;
    if (angle > 0 && angle < PI)
        y_multiple = -1;
    else
        y_multiple = 1;


    if (angle > PI/2 && angle < 3*PI/2)
        d_y = get_fract_part(position.x) * fabs(tan(angle));
    else
        d_y = ((1 - get_fract_part(position.x)) * fabs(tan(angle)));

    if (angle > PI/2 && angle < 3*PI/2)
        d_x = get_fract_part(position.x);
    else
        d_x = 1 - get_fract_part(position.x);



    if (angle == 0 || angle == PI)
        intersection.y = position.y;
    else
        intersection.y = position.y + y_multiple * d_y;
    intersection.x = position.x + x_multiple * d_x;

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

t_dvec2 get_intersection(t_player player, t_map *map, double angle)
{
    t_dvec2 position;
    t_dvec2 vertical_intersection;
    t_dvec2 horizontal_intersection;
    double d_x;
    double d_y;
    double x_i;
    double y_i;
    int i;
    
    position = player.position;

    d_x = get_dx(angle);
    d_y = get_dy(angle);

    if (angle > PI/2 && angle < 3*PI/2)
        x_i = -1;
    else
        x_i = 1;

    if (angle > 0 && angle < PI)
        y_i = -1;
    else
        y_i = 1;
    
    if (angle == PI/2 || angle == 3*PI/2)
    {
        horizontal_intersection = get_horizontal_intersection(position, angle);
        return (horizontal_intersection);
        //TODO: this is an end less loop when angle is PI/2 or ... having the max ray is a temp fix -> rethink iswall()
        i = 0;
        while (i < MAX_RAY)
        {
            if (smart_is_wall(map, horizontal_intersection, x_i, y_i, true))
                return (horizontal_intersection);
            horizontal_intersection.y += y_i;
            i++;
        }
    }
    if (angle == 0 || angle == PI)
    {
        vertical_intersection = get_vertical_intersection(position, angle);
        //TODO: this is an end less loop when angle is PI or 0 having the max ray is a temp fix -> rethink iswall()
        i = 0;
        while (i < MAX_RAY)
        {
            if (smart_is_wall(map, vertical_intersection, x_i, y_i, false)) //horizotal and vertical mix up here fixed
                return (vertical_intersection);
            vertical_intersection.x += x_i;
            i++;
        }
    }

    vertical_intersection = get_vertical_intersection(position, angle);
    horizontal_intersection = get_horizontal_intersection(position, angle);

    i = 0;

    while (i < MAX_RAY)
    {
        if (smart_is_wall(map, vertical_intersection, x_i, y_i, false))
            break;
        vertical_intersection.x += x_i;
        vertical_intersection.y += fabs(d_y) * y_i;
        i++;
    }

    i = 0;
    while (i < MAX_RAY)
    {
        if (smart_is_wall(map, horizontal_intersection, x_i, y_i, true))
            break;
        horizontal_intersection.x += fabs(d_x) * x_i;
        horizontal_intersection.y += y_i;
        i++;
    }

    // printf("x_v = %lf , y_v = %lf\n", vertical_intersection.x, vertical_intersection.y);
    // printf("x_h = %lf , y_h = %lf\n", horizontal_intersection.x, horizontal_intersection.y);

    return (closer_to_p1(position, vertical_intersection, horizontal_intersection));
}

double  deg2rad(double degrees)
{
    return (PI * degrees / 180);
}

double rad2deg(double rad)
{
    return (rad * 180 / PI);
}