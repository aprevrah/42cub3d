#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265359

typedef struct s_dvec2
{
	double					x;
	double					y;
}						t_dvec2;

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
t_dvec2 get_intersection(t_dvec2 position, int **map, double angle);

int is_wall(t_dvec2 intersection, int **map)
{
    int x;
    int y;
    
    x = intersection.x;
    y = intersection.y;

    // if (!get_fract_part(x) && !get_fract_part(y))
    //     check_4(intersection);
    // else
    //     check_2(intersection);

    if (!get_fract_part(x) && get_fract_part(y))
    {
        x = floor(x);
        if (map[y][x] || map[y-1][x])
            return (1);
    }
    else if (!get_fract_part(y) && get_fract_part(x))
    {
        y = floor(y);
        if (map[y][x] || map[y][x-1])
            return (1);
    }
    else if (!get_fract_part(x) && !get_fract_part(y))
    {
        if (map[y][x] || map[y][x-1] || map[y-1][x] || map[y-1][x-1])
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
// # returns (-1) if no intersection
double  get_hi_lenght(t_dvec2 position, double angle)
{
    double c;
    
    if (!sin(angle))
        return (-1);
    c = (1 - get_fract_part(position.y)) / sin(angle);
    return (c);
}

// # c = (1 - px) / cos()
// # function returns length from position to next vertical intersection
// # returns (-1) if no intersection
double  get_vi_lenght(t_dvec2 position, double angle)
{
    double c;
    
    if (!cos(angle))
        return (-1);
    c = (1 - get_fract_part(position.x)) / cos(angle);
    return (c);
}

t_dvec2 get_horizontal_intersection(t_dvec2 position, double angle)
{
    t_dvec2 intersection;

    if (angle == PI/2 || angle == 3*PI/2)
        intersection.x = position.x;
    else
        intersection.x = position.x + ((1 - get_fract_part(position.y)) / tan(angle));
    intersection.y = position.y - get_fract_part(position.y);

    return (intersection);
}

t_dvec2 get_vertical_intersection(t_dvec2 position, double angle)
{
    t_dvec2 intersection;

    intersection.x = position.x + 1 - get_fract_part(position.x);
    if (!tan(angle))
        intersection.y = position.y;
    else
        intersection.y = position.y - ((1 - get_fract_part(position.x)) * tan(angle));

    return (intersection);
}

t_dvec2 get_intersection(t_dvec2 position, int **map, double angle)
{
    t_dvec2 new_position;
    double c_h;
    double c_v;

    c_h = get_hi_lenght(position, angle);
    c_v = get_vi_lenght(position, angle);

    if (c_h < c_v)
        new_position = get_horizontal_intersection(position, angle);
    else
        new_position = get_vertical_intersection(position, angle);
    
    if (is_wall(new_position, map))
        return (new_position);
    else
        return (get_intersection(new_position, map, angle));
}


int main(void)
{
    t_player p1;
    double c1;
    t_dvec2 intersection;

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

    p1.position.x = 1.5;
    p1.position.y = 2.5;

    p1.orientation.x = 0;
    p1.orientation.y = 1;

    intersection = get_intersection(p1.position, map, PI/4);

    printf("x = %lf, y = %lf\n", intersection.x, intersection.y);

    
    // c1 = get_hi_lenght(p1.position, PI/4);
    // if (c1 < 0)
    //     printf ("No intersection!\n");
    // else
    //     printf("c_h = %f\n", c1);

    // intersection = get_horizontal_intersection(p1.position , PI/4);
    // printf("x_h = %lf , y_h = %lf\n", intersection.x, intersection.y);

    // c1 = get_vi_lenght(p1.position, PI/4);
    // if (c1 < 0)
    //     printf ("No intersection!\n");
    // else
    //     printf("c_v = %f\n", c1);

    // intersection = get_vertical_intersection(p1.position , PI/4);
    // printf("x_v = %lf , y_v = %lf\n", intersection.x, intersection.y);
}


