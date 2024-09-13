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
    float a, b;
    float x1 = 0, y1 = 0;
    a = 2;
    b = 3;
    float x2 = (a - b);
    float y2 = (a + b);

    int m = 2, n = 1;
    double **A = createMat(m, n);
    double **B = createMat(m, n);

    A[0][0] = x1;
    A[1][0] = y1;
    B[0][0] = x2;
    B[1][0] = y2;

    FILE *file = fopen("distance.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }
    
    double **s_ab = Matsub(A, B, m, n);
    double sideAB = Matnorm(s_ab, m);
    fprintf(file, "%f %f\n", A[0][0], A[1][0]);
    fprintf(file, "%f %f\n", B[0][0], B[1][0]);
    fprintf(file, "The distance between the points is %lf" ,sideAB);


}
