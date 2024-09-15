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
        fprintf(fptr, "%lf %lf\n", output[0][0], output[1][0]);
        freeMat(output,2);
    }
}

int main()
{
    float a = 2 , b = 3;
    float x1, y1, x2, y2;
    x1 = 0 , y1 = 0;
    x2 = a - b ;
    y2 = a + b;

    int m = 2, n = 1;
    double **A = createMat(m, n);
    double **B = createMat(m, n);

    A[0][0] = x1;
    A[1][0] = y1;
    B[0][0] = x2;
    B[1][0] = y2;

    FILE *fptr;
    fptr = fopen("points.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

     point_gen(fptr, A, B, 40);
     fprintf(fptr,"%lf %lf\n",B[0][0],B[1][0]);

     double **s_ab = Matsub(A, B, m, n);
     double sideAB = Matnorm(s_ab, m);

    freeMat(A,m);
    freeMat(B,m);
    freeMat(s_ab,m);

    fprintf(fptr, "The distance between the points for a = 2 and b = 3 is  %lf\n", sideAB);
    fclose(fptr);
    return 0;


}
