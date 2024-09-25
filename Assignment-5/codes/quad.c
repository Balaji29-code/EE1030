#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "libs/matfun.h"
#include "libs/geofun.h"

void point_gen(FILE *fptr, double **A, double **B, int no_rows, int no_cols, int num_points) {
    for (double i = 0; i <= num_points; i++) {
        double **output = Matadd(A, Matscale(Matsub(B,A,no_rows,no_cols),no_rows,no_cols,(double)i/num_points), no_rows, no_cols);
        fprintf(fptr, "%lf,%lf\n", output[0][0], output[1][0]);
        freeMat(output,no_rows);
    }
    double a1, a2, b1, b2, c1, c2;
    a1 = 2; a2 = 5; b1 = 5, b2 = -2, c1 = 7, c2 = 9;
    int m = 2, n = 1;
    double **A = createMat(m, n);
    double **B = createMat(m, n);
    double **a = createMat(m, n);
    double **b = createMat(m, n);
 
    double s1 = -(a1/b1);
    double s2 = -(a2/b2);
    float x1, x2, x3, x4;
    x1 = 2 ; 
    x2 = 4 ;
    x3 = 5;
    x4 = 1;
    A[0][0] = x1;
    A[1][0] = s1*x1 + c1;
    B[0][0] = x2;
    B[1][0] = s2*x2 + c2;
    a[0][0] = x3;
    a[1][0] = s1*x3 + c1;
    b[0][0] = x4;
    b[1][0] = s2*x4 + c2;

    FILE *fptr;
    fptr = fopen("line_points.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    point_gen(fptr, 0,A , m, n, 20);
    point_gen(fptr, B,b , m, n, 20);
    freeMat(A,m);
    freeMat(B,m);
    freeMat(a,m);
    freeMat(b,m);
    
    fclose(fptr);
    return 0;
}
    







