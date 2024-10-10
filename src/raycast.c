#include "../include/cub3d.h"

int is_wall(t_dvec2 intersection, t_map *map)
{
    double x;
    double y;
    
    x = intersection.x;
    y = intersection.y;

    if (!get_fract_part(x) && get_fract_part(y))
    {
        y = floor(y);
        //printf("x: %f, y: %f --- ", x, y);
        if (!map->arr[(int)y][(int)x] || (((int)x >= 1) && !map->arr[(int)y][(int)x-1]))
            return (1);
    }
    else if (get_fract_part(x) && !get_fract_part(y))
    {
        x = floor(x);
        //printf("test");
        if (!map->arr[(int)y][(int)x] || (((int)x >= 1) && !map->arr[(int)y][(int)x-1]))
            return (1);
    }
    else if (!get_fract_part(x) && !get_fract_part(y))
    {
        if (!map->arr[(int)y][(int)x] || (((int)x >= 1) && !map->arr[(int)y][(int)x-1]) || \
        (((int)x >= 1) && !map->arr[(int)y][(int)x-1]) || (((int)x >= 1) && ((int)y >= 1) && !map->arr[(int)y-1][(int)x-1]))
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

    if (angle > PI/2 && angle < 3*PI/2)
        x_multiple = -1;
    else
        x_multiple = 1;
    if (angle > 0 && angle < PI)
        y_multiple = -1;
    else
        y_multiple = 1;
 
    if (fabs(angle - 0) < EPSILON || fabs(angle - PI) < EPSILON)
    {
        intersection.x = -1;
        intersection.y = -1;
        return (intersection);
    }

    if (angle == PI/2 || angle == 3*PI/2)
        intersection.x = position.x;
    else
        intersection.x = position.x + x_multiple * ((1 - get_fract_part(position.y)) / fabs(tan(angle)));
    intersection.y = position.y + y_multiple * (1 - get_fract_part(position.y));

    return (intersection);
}

t_dvec2 get_vertical_intersection(t_dvec2 position, double angle)
{
    t_dvec2 intersection;
    int     x_multiple;
    int     y_multiple;

    // Use fabs to check if the difference is within a small range (epsilon)
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

    if (!tan(angle))
        intersection.y = position.y;
    else
        intersection.y = position.y + y_multiple * ((1 - get_fract_part(position.x)) * fabs(tan(angle)));
    intersection.x = position.x + x_multiple * (1 - get_fract_part(position.x));

    return (intersection);
}

t_dvec2 get_intersection(t_dvec2 position, t_map *map, double angle)
{
    t_dvec2 new_position;
    double c_h;
    double c_v;

    c_h = get_hi_lenght(position, angle);
    c_v = get_vi_lenght(position, angle);

    if ((c_h && !c_v) || c_h < c_v)
        new_position = get_horizontal_intersection(position, angle);
    else
        new_position = get_vertical_intersection(position, angle);
    
    if (is_wall(new_position, map))
        return (new_position);
    else
        return (get_intersection(new_position, map, angle));
    return new_position;
}

double  deg2rad(double degrees)
{
    return (PI * degrees / 180);
}

double rad2deg(double rad)
{
    return (rad * 180 / PI);
}