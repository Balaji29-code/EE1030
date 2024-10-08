#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "libs/matfun.h"
#include "libs/geofun.h"

void circle_gen(FILE *fptr, double **centre, double radius, int num_points)
{
    double **Point_on_circle = createMat(2,1);
    double angle_step = 4*M_PI/num_points;
    double angle;
    for(int i = 0; i <= num_points ; i++)
    {
        angle = i*angle_step;
        Point_on_circle[0][0] = centre[0][0] + radius*cos(angle);
        Point_on_circle[1][0] = centre[1][0] + radius*sin(angle);
        fprintf(fptr,"%lf %lf\n", Point_on_circle[0][0], Point_on_circle[1][0]);
    }
}

void parab_y2_4ax_gen(FILE *fptr, double limit_x, double a, double num_points)
{
    double **coord_of_parb = createMat(2,1);
    for(double i = limit_x ; i > 0  ; i = i - (limit_x)/num_points   )
    {
        coord_of_parb[0][0] = a*i*i;
        coord_of_parb[1][0] = 2*a*i;
        fprintf(fptr,"%lf %lf\n", coord_of_parb[0][0], coord_of_parb[1][0]);
    }
     for(double i = 0 ; i <= limit_x ; i = (limit_x)/num_points + i )
    {
        coord_of_parb[0][0] = a*i*i;
        coord_of_parb[1][0] = -2*a*i;
        fprintf(fptr,"%lf %lf\n", coord_of_parb[0][0], coord_of_parb[1][0]);
    }


}


double function_parb(double x)
{
	return x*x/2  ;
}

double area_parb(double left_limit, double right_limit)
{
	double sum=0;
	for ( double i = left_limit; i<=right_limit; i+=1e-7 )
	{
		sum += function_parb(i)*1e-7 ;
	}
	return sum ;
}

double function_circle(double x)
{
    return sqrt(8*x - pow(x,2));
}

double area_circle(double left_limit, double right_limit)
{
	double sum=0;
	for ( double i = left_limit; i<=right_limit; i+=1e-7 )
	{
		sum += function_circle(i)*1e-7 ;
	}
	return sum ;
}


int main()
{
    int num_points_c = 200;
    double **C = createMat(2,1);
    C[0][0] = 4;
    C[1][0] = 0;
    double f = 0;
    double radius = sqrt(pow(C[0][0],2) + pow(C[1][0],2) - f);
    FILE *fptr;
    fptr = fopen("circ_parb.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    circle_gen(fptr,C,radius,num_points_c);
    double a = 1;
    double limit_x = 3;
    double num_points_p = 100;

    parab_y2_4ax_gen(fptr, limit_x, a, num_points_p);
    fprintf(fptr,"The Area between circle and the parabola is %lf", 2*area_parb(0,4)+2*area_circle(4,8));
    fclose(fptr);

}
