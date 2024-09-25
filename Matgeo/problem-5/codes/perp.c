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
        double **output;
        if (A != NULL && B != NULL) {
            output = Matadd(A, Matscale(Matsub(B,A,no_rows,no_cols),no_rows,no_cols,(double)i/num_points), no_rows, no_cols);
        } else if (A == NULL) {
            output = Matscale(B, no_rows, no_cols, (double)i/num_points);
        } else if (B == NULL) {
            output = Matscale(A, no_rows, no_cols, (double)i/num_points);
        }
        fprintf(fptr, "%lf,%lf\n", output[0][0], output[1][0]);
        freeMat(output,no_rows);
    }
}

int main()
{
    double a1, b1, a2, b2, c1, c2, m1, m2 ;
    double x1, y1, x2, y2, x3, y3, x4, y4 ;
    a1 =1;
    b1 = 1; 
    c1 = 1;
    a2 = 1;
    b2 = -1;
    c2 = 1;
    x1 = 1;
    m1 = -(a1/b1);
    m2 = -(a2/b2);
    y1 = m1*x1 +c1;
    x2 = -1;
    y2 = m1*x2 +c1;
    x3 = 1;
    y3 = m2*x3 +c2;
    x4 = -1;
    y4 = m2*x4 +c2;

    int m = 2, n = 1;
    double **L1p1 = createMat(m, n);
    double **L1p2 = createMat(m, n);
    double **L2p1 = createMat(m, n);
    double **L2p2 = createMat(m, n);

    L1p1[0][0] = x1;
    L1p1[1][0] = y1;
    L1p2[0][0] = x2;
    L1p2[1][0] = y2;

    L2p1[0][0] = x3;
    L2p1[1][0] = y3;
    L2p2[0][0] = x4;
    L2p2[1][0] = y4;

    FILE *fptr;
    fptr = fopen("line_points.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fptr,"%lf,%lf\n",L1p1[0][0],L1p1[1][0]);
    fprintf(fptr,"%lf,%lf\n",L1p2[0][0],L1p2[1][0]);
    fprintf(fptr,"%lf,%lf\n",L2p1[0][0],L2p1[1][0]);
    fprintf(fptr,"%lf,%lf\n",L2p2[0][0],L2p2[1][0]);
    point_gen(fptr, L1p1,L1p2 , m, n, 20);
    point_gen(fptr, L2p1,L2p2 , m, n, 20);
   
    fclose(fptr);
    return 0;



}
