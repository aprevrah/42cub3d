#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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


double  get_hi_lenght(t_dvec2 position, double angle);
double  get_vi_lenght(t_dvec2 position, double angle);
t_dvec2 get_horizontal_intersection(t_dvec2 position, double angle);
t_dvec2 get_vertical_intersection(t_dvec2 position, double angle);


// # c = (1 - py) / sin() 
double  get_hi_lenght(t_dvec2 position, double angle)
{
    double c;
    double int_part, frac_part;
    (void) angle;

    frac_part = modf(position.y, &int_part);

    printf("Fractional part: %.2f\n", frac_part);;

    return (0);
}


int main(void)
{
    t_player p1;

    p1.position.x = 1.55;
    p1.position.y = 2.59;

    p1.orientation.x = 0;
    p1.orientation.y = 1;

    get_hi_lenght(p1.position, 0);
}


