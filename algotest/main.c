#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323
#define EPSILON 0.000001

typedef struct s_dvec2
{
	double					x;
	double					y;
}						t_dvec2;

typedef struct s_map
{
	int					length;
	int					height;
	int					**arr;
}						t_map;

typedef struct s_player
{
	t_dvec2 position;
	t_dvec2	orientation;
    double  angle;
}						t_player;


double get_fract_part(double x);
double  get_hi_lenght(t_dvec2 position, double angle);
double  get_vi_lenght(t_dvec2 position, double angle);
t_dvec2 get_horizontal_intersection(t_dvec2 position, double angle);
t_dvec2 get_vertical_intersection(t_dvec2 position, double angle);
t_dvec2 get_intersection(t_dvec2 position, t_map *map, double angle);
double  deg2rad(double degrees);

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

        if (map->arr[(int)y][(int)x] || ((x-1) >= 0 && map->arr[(int)y][(int)x-1]))
            return (1);
    }
    else if (!get_fract_part(y) && get_fract_part(x))
    {
        x = floor(x);
        if (map->arr[(int)y][(int)x] || ((y-1) >= 0 && map->arr[(int)y-1][(int)x]))
            return (1);
    }
    else if (!get_fract_part(x) && !get_fract_part(y))
    {
        if (map->arr[(int)y][(int)x] \
        || ((x-1) >= 0 && map->arr[(int)y][(int)x-1]) \
        || ((y-1) >= 0 && map->arr[(int)y-1][(int)x]) \
        ||  ((y-1) >= 0 && (x-1) >= 0 && map->arr[(int)y-1][(int)x-1]))
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

    if (angle == 0 || angle == PI)
        intersection.y = position.y;
    else
        intersection.y = position.y + y_multiple * ((1 - get_fract_part(position.x)) * fabs(tan(angle)));
    intersection.x = position.x + x_multiple * (1 - get_fract_part(position.x));

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

t_dvec2 get_intersection(t_dvec2 position, t_map *map, double angle)
{
    t_dvec2 vertical_intersection;
    t_dvec2 horizontal_intersection;
    double d_x;
    double d_y;
    double x_i;
    double y_i;

    //angle = deg2rad(angle);

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
        while (1)
        {
            if (is_wall(horizontal_intersection, map))
                return (horizontal_intersection);
            horizontal_intersection.y += y_i;
        }
    }

    if (angle == 0 || angle == PI)
    {
        vertical_intersection = get_vertical_intersection(position, angle);
        while (1)
        {
            
            if (is_wall(vertical_intersection, map))
                return (vertical_intersection);
            vertical_intersection.x += x_i;
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
    while (1)
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
    }
}

double  deg2rad(double degrees)
{
    return (PI * degrees / 180);
}

double rad2deg(double rad)
{
    return (rad * 180 / PI);
}

int **make_map(void)
{
    int rows = 4;
    int cols = 4;

    // Dynamically allocate the 2D array
    int **map = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        map[i] = (int *)malloc(cols * sizeof(int));
    }

    // Fill the map with walls (1s) on the edges and floor (0s) in the middle
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                map[i][j] = 1; // Walls
            } else {
                map[i][j] = 0; // Floor
            }
        }
    }
    return (map);
}

t_player enter_position(void)
{
    t_player p1;

    printf("Enter x: ");
    scanf("%lf", &p1.position.x);
    printf("Enter y: ");
    scanf("%lf", &p1.position.y);

    return (p1);
}

double enter_angle(void)
{
    double angle;

    printf("Enter angle: ");
    scanf("%lf", &angle);

    angle = deg2rad(angle);
    return (angle);
}

int main(void)
{
    t_player p1;
    double c1;
    t_dvec2 intersection;
    t_map map;

    map.arr = make_map();
    map.length = 4;
    map.height = 4;

    

    p1.position.x = 1.5;
    p1.position.y = 2.5;
    p1.angle = 0;

    p1 = enter_position();
    p1.angle = enter_angle();


    // c1 = get_hi_lenght(p1.position, p1.angle);
    // if (!c1)
    //     printf ("No intersection!  ");
    // else
    //     printf("c_h = %f, ", c1);

    // intersection = get_horizontal_intersection(p1.position , p1.angle);
    // printf("x_h = %lf , y_h = %lf\n", intersection.x, intersection.y);

    // c1 = get_vi_lenght(p1.position, p1.angle);
    // if (!c1)
    //     printf ("No intersection!   ");
    // else
    //     printf("c_v = %f, ", c1);

    // intersection = get_vertical_intersection(p1.position , p1.angle);
    // printf("x_v = %lf , y_v = %lf\n", intersection.x, intersection.y);

    intersection = get_intersection(p1.position, &map, p1.angle);
    printf("x = %lf, y = %lf\n", intersection.x, intersection.y);

    /* if (map.arr[1][-1] == 1)
        printf ("test\n"); */

    // if (is_wall(p1.position, &map))
    //     printf ("WALL\n");
    // else
    //     printf("NO WALL\n");
}


