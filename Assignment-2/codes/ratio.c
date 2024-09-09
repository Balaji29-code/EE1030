#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "libs/matfun.h"
#include "libs/geofun.h"

float find_k( double , double ,double  );

int main()
{

    float x1 = 2 , x2 = 3 , y1 = -2 , y2 = 7 , x3 = (float)24/11 ;
    float y3;
    int m = 2 , n = 1;
    double **P, **Q, **R , **temp;

    P = createMat(m,n);
    Q = createMat(m,n);
    R = createMat(m,n);
    temp = createMat(m,n);

    P[0][0] = x1;
    P[1][0] = y1;
    Q[0][0] = x2;
    Q[1][0] = y2;
    R[0][0] = x3;
    float k = find_k(P[0][0], Q[0][0], R[0][0] );

     FILE *file = fopen("point.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }
        
   
   temp = Matscale( Q,  m,  n,  k);
   temp = Matadd(temp, P , m , n);
   temp = Matscale(temp ,m, n, 1.0/(k+1) );
   R = temp;

   fprintf(file, "%f %f\n", P[0][0], P[1][0]);
    fprintf(file, "%f %f\n", Q[0][0], Q[1][0]);
    fprintf(file, "%f %f\n", R[0][0], R[1][0]);
     fclose(file);

   




    
    
}

float find_k( double a, double b,double c )
{
    float k ;
    k = (float)(a - c) / (c - b);
    return k ;


}

