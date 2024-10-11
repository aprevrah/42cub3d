#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265359
#define EPSILON 0.000001

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

double  deg2rad(double degrees)
{
    return (PI * degrees / 180);
}

double rad2deg(double rad)
{
    return (rad * 180 / PI);
}


double vec2angle(t_dvec2 vec)
{
    double alpha;

    // Use atan2 to get the angle in radians
    alpha = atan2(vec.y, vec.x);

    // Ensure alpha is positive by adding 2*PI if necessary (keep in [0, 2PI] range)
    if (alpha < 0)
        alpha += 2 * PI;

    // Shift the angle by 3PI/2 to account for your mirrored system
    alpha = fmod((alpha + (3.0 * PI / 2.0)), 2 * PI);

    return alpha;
}
int main(void)
{
    t_dvec2 v1;
    t_dvec2 v2;
    double x;
    double x2;

    v1.x = 1;
    v1.y = 0;

    v2.x = -1;
    v2.y = -1;

    x = vec2angle(v1);
    x = rad2deg(x);

    printf("x = %.5lf°\n", x);
}