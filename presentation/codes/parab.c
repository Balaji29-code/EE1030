
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "libs/matfun.h"
#include "libs/geofun.h"

typedef struct 
{
    double **p;
}Point;

typedef struct 
{
    double **V;
    double **u;
    double f;
}Parabola;

void InitializePoint(Point *point)
{
    point->p = createMat(2,1);
}

void InitializeParabola(Parabola *parabola)
{
    parabola->V = createMat(2,2);
    parabola->u = createMat(2,1);
    parabola->f = 0;
}

void parab_y2_4ax_gen(FILE *fptr, Point *x1, Point *x2, double a, int num_points) 
{
    double tinit = (x1->p[0][0] / (2 * a));
    double tfinal = (x2->p[1][0] / (2 * a));

    Point coord;
    InitializePoint(&coord);
    if (tfinal > tinit)
    {
        for (double i = tinit; i <= tfinal; i += 1.0 / num_points) 
        {
            coord.p[0][0] = a*i*i;
            coord.p[1][0] = 2*a*i;
            fprintf(fptr,"%lf,%lf\n", coord.p[0][0], coord.p[1][0] );
        }
    }
    else
    {
        for (double i = tfinal; i <= tinit; i += 1.0 / num_points)
        {
            coord.p[0][0] = a*i*i;
            coord.p[1][0] = 2*a*i;
            fprintf(fptr,"%lf,%lf\n", coord.p[0][0], coord.p[1][0] );
        }

    }
}

Point* intersect_of_parab_line(Parabola *parabola, Point *point_line, Point *slope)
{
    double m1 = slope->p[0][0];
    double m2 = slope->p[1][0];

    double h1 = point_line->p[0][0];
    double h2 = point_line->p[1][0];


    double V1 = parabola->V[0][0];
    double V2 = parabola->V[1][0];
    double V3 = parabola->V[0][1];
    double V4 = parabola->V[1][1];

    double u1 = parabola->u[0][0];
    double u2 = parabola->u[1][0];

    double A = V1 * m1 * m1 + (V2 + V3) * m1 * m2 + V4 * m2 * m2;
    double B = 2 * (m1 * (V1 * h1 + V2 * h2 + u1) + m2 * (V3 * h1 + V4 * h2 + u2));
    double C = h1 * (V1 * h1 + V2 * h2) + h2 * (V3 * h1 + V4 * h2) + 2 * (u1 * h1 + u2 * h2) + parabola->f;

    if (B * B - 4 * A * C < 0) 
    {
        return NULL;
    }
    else
    {
        Point *intersection = malloc(2*sizeof(Point));
        InitializePoint(&intersection[0]);
        InitializePoint(&intersection[1]);

        if (B * B - 4 * A * C == 0) {
            double k = -B / (2 * A);
            intersection[0].p[0][0] = point_line->p[0][0] + k * slope->p[0][0];
            intersection[0].p[1][0] = point_line->p[1][0] + k * slope->p[1][0];
            return intersection;
        }
        else
        {
            double k1 = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
            double k2 = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
            intersection[0].p[0][0] = point_line->p[0][0] + k1 * slope->p[0][0];
            intersection[0].p[1][0] = point_line->p[1][0] + k1 * slope->p[1][0];
            intersection[1].p[0][0] = point_line->p[0][0] + k2 * slope->p[0][0];
            intersection[1].p[1][0] = point_line->p[1][0] + k2 * slope->p[1][0];
            return intersection;

        }


    }

}

int main()
{
    Parabola parabola;
    Point p1;
    Point p2;
    Point slope;
    Point point_line;

    InitializeParabola(&parabola);
    InitializePoint(&p1);
    InitializePoint(&p2);
    InitializePoint(&slope);

    parabola.V[0][0] = 0;
    parabola.V[0][1] = 0;
    parabola.V[1][0] = 0;
    parabola.V[1][1] = 1;
    parabola.u[0][0] = 0;
    parabola.u[1][0] = -4*sqrt(2);
    parabola.f = 0;

    point_line.p[0][0] = 8*sqrt(2);
    point_line.p[1][0] = 0;

    slope.p[0][0] = 0;
    slope.p[1][0] = 1;

    Point *intersection = intersect_of_parab_line(&parabola, &point_line, &slope);

    p1.p[0][0] = intersection[0].p[0][0];
    p1.p[1][0] = intersection[0].p[1][0];

    p2.p[0][0] = intersection[1].p[0][0];
    p2.p[1][0] = intersection[1].p[1][0];

    
    FILE *fptr = fopen("parab.txt", "w");
    if (fptr == NULL) 
    {
        printf("Error opening file!\n");
        return 1;

    }

    parab_y2_4ax_gen(fptr, &p1, &p2, -parabola.u[1][0] / 2, 150);
    fclose(fptr);
    return 0;

}

