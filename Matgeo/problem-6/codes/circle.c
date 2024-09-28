#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "libs/matfun.h"
#include "libs/geofun.h"
int main() 
{
    int num_points = 250;
   int m = 2, n = 1;
    double **C = createMat(m, n);
    C[0][0] = 2;
    C[1][0] = 4 ;
    double f = -45;
    double radius = sqrt(pow(C[0][0],2) + pow(C[1][0],2) - f);
     double angle_step = 4 * M_PI / num_points;
     
     
     FILE *fptr;
    fptr = fopen("circle.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fptr, "%lf %lf\n", C[0][0], C[1][0]);
    for (int i = 0; i <= num_points; ++i) {
        double angle = i * angle_step;
        double x = C[0][0] + radius * cos(angle);
        double y = C[1][0] + radius * sin(angle);

        fprintf(fptr, "%f %f\n", x, y);
    }

     fclose(fptr);
    return 0;
}
