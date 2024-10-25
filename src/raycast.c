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

// t_dvec2 get_intersection(t_dvec2 position, int **map, double angle)
// {
//     t_dvec2 new_position;
//     double c_h;
//     double c_v;

//     c_h = get_hi_lenght(position, angle);
//     c_v = get_vi_lenght(position, angle);

//     if (c_h < c_v || !c_h)
//         new_position = get_horizontal_intersection(position, angle);
//     else
//         new_position = get_vertical_intersection(position, angle);
    
//     if (is_wall(new_position, map))
//         return (new_position);
//     else
//         return (get_intersection(new_position, map, angle));
//     return new_position;
// }

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

t_dvec2 get_intersection(t_player player, t_map *map, double angle)
{
    t_dvec2 position;
    t_dvec2 vertical_intersection;
    t_dvec2 horizontal_intersection;
    double d_x;
    double d_y;
    double x_i;
    double y_i;
    
    
    position = player.position;
    //angle = vec2angle(player.orientation);
    // printf("angle = %lf\n", angle);

    // angle = deg2rad(315);
    // printf("angle = %lf\n", angle);

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
        // while (1)
        // {
        //     if (is_wall(horizontal_intersection, map))
        //         return (horizontal_intersection);
        //     printf("x = %lf, y = %lf\n", horizontal_intersection.x, horizontal_intersection.y);
        //     horizontal_intersection.y += y_i;
        //     //printf("test3\n");

        // }
    }

    if (angle == 0 || angle == PI)
    {
        vertical_intersection = get_vertical_intersection(position, angle);
        while (1)
        {
            
            if (is_wall(vertical_intersection, map))
                return (vertical_intersection);
            vertical_intersection.x += x_i;
            printf("test2\n");

        }
    }

    // # if angle is 90 || 270 then only horizontal

    // if (fabs(angle - PI/2) < EPSILON || fabs(angle - 3*PI/2) < EPSILON)
    // {   
    //     horizontal_intersection = get_horizontal_intersection(position, angle);
    //     while (1)
    //     {
    //         if (is_wall(horizontal_intersection, map))
    //             return (horizontal_intersection);
    //         //position
    //     }
    // }

    // # if angle is 0 || 180 then only vertical

    // # 1. get nearest vertical and horizontal intersection
    vertical_intersection = get_vertical_intersection(position, angle);
    horizontal_intersection = get_horizontal_intersection(position, angle);

    // # 2. check if these intersections are in a wall
    // if (is_wall(vertical_intersection, map) && is_wall(horizontal_intersection, map))
    //     return (closer_to_p1(position, vertical_intersection, horizontal_intersection));
    // if (is_wall(vertical_intersection, map))
    //     return (vertical_intersection);
    // if (is_wall(horizontal_intersection, map))
    //     return (horizontal_intersection);

    // # add dx to horzontal and dy to vertical intersection
    // # check if one of them hits a wall 
    // # if both of them hit a wall use return the shorter one 

    int i = 0;

    while (i < 10)
    {
        if (is_wall(vertical_intersection, map) && is_wall(horizontal_intersection, map))
            return (closer_to_p1(position, vertical_intersection, horizontal_intersection));
        if (is_wall(vertical_intersection, map))
            return (vertical_intersection);
        if (is_wall(horizontal_intersection, map))
            return (horizontal_intersection);
 
        vertical_intersection.x += x_i;
        vertical_intersection.y += fabs(d_y) * y_i;
        horizontal_intersection.x += fabs(d_x) * x_i;
        horizontal_intersection.y += y_i;
        printf("test1\n");
        i++;
    }
    return (vertical_intersection);
}

double  deg2rad(double degrees)
{
    return (PI * degrees / 180);
}

double rad2deg(double rad)
{
    return (rad * 180 / PI);
}