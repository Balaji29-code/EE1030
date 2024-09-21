#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "libs/matfun.h"
#include "libs/geofun.h"

void point_gen(FILE *fptr, double **A, double **B, int num_points) {
    for (double i = 0; i <= num_points; i++) {
        double **output = Matsec(A, B, 2, (double) i / num_points);
        fprintf(fptr, "%lf,%lf\n", output[0][0], output[1][0]);
        freeMat(output,2);
    }
}

int main()
{
    double a, b, c, x1, y1, x2, y2, x3, y3, angleb;
    a = 12;
    c =  5;
    angleb = 90;
    b = sqrt(pow(a,2)+pow(c,2)- (2*a*c*cos(angleb)));
    
    int m = 2, n = 1;
    double **A = createMat(m, n);
    double **B = createMat(m, n);
    double **C = createMat(m, n);
    double radianb = angleb*M_PI/180;

    A[0][0] = c*cos(radianb);
    A[1][0] = c*sin(radianb);
    B[0][0] = 0;
    B[1][0] = 0;
    C[0][0] = a;
    C[1][0] = 0;

    FILE *fptr;
    fptr = fopen("triangle_points.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    point_gen(fptr, A, B, 10);
    point_gen(fptr, B, C, 20);
    point_gen(fptr, C, A, 20);

    freeMat(A, m);
    freeMat(B, m) ;
    freeMat(C, m) ;

    fclose(fptr) ;
}
