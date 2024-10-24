#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323
#define EPSILON 0.000001



double  deg2rad(double degrees)
{
    return (PI * degrees / 180);
}

int main(void)
{
    double angle;

    printf("Enter angle: ");
    scanf("%lf", &angle);

    angle = deg2rad(angle);

    printf ("angle = %.17f\n", angle);
    printf ("PI    = %.17f\n", PI);

    if (angle == PI/2)
        printf("PI/2\n");

    if (angle == PI)
        printf("PI\n");

    if (angle == 3*PI/2)
        printf ("3PI/2\n");

    // double x = tan(angle);

    // printf("%lf\n", x);



}