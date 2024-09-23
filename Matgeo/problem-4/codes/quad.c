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

int main() {
    double x1, y1, x2, y2, x3, y3,x4, y4;
//    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);
    x1 = -4; y1 = 5;
    x2 = 0; y2 = 7;
    x3 = 5; y3 = -5;
    x4 = -4;y4 = -2;

    int m = 2, n = 1;
    double **A = createMat(m, n);
    double **B = createMat(m, n);
    double **C = createMat(m, n);
    double **D = createMat(m, n);
    
    A[0][0] = x1;
    A[1][0] = y1;
    B[0][0] = x2;
    B[1][0] = y2;
    C[0][0] = x3;
    C[1][0] = y3;
    D[0][0] = x4;
    D[1][0] = y4;
    double **s_ab = Matsub(A, B, m, n);
    double **s_bc = Matsub(B, C, m, n);
    double **s_cd = Matsub(C, D, m, n);
    double **s_da = Matsub(D, A, m, n);
    double sideAB = Matnorm(s_ab, m);
    double sideBC = Matnorm(s_bc, m);
    double sideCA = Matnorm(s_cd, m);
    double sideDA = Matnorm(s_da, m);
    double perimeter = sideAB + sideBC + sideCA + sideDA;


    FILE *fptr;
    fptr = fopen("quad.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(fptr,"%lf,%lf\n", A[0][0],A[1][0]);
    fprintf(fptr,"%lf,%lf\n", B[0][0],B[1][0]);
    fprintf(fptr,"%lf,%lf\n", C[0][0],C[1][0]);
    fprintf(fptr,"%lf,%lf\n", D[0][0],D[1][0]);

    point_gen(fptr, A, B, 10);
    point_gen(fptr, B, C, 10);
    point_gen(fptr, C, D, 10);
    fprintf(fptr,"%lf\n",perimeter);

    freeMat(A,m);
    freeMat(B,m);
    freeMat(C,m);

    fclose(fptr);
    return 0;
}

