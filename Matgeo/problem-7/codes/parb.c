#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "libs/matfun.h"
#include "libs/geofun.h"

void parab_y2_4ax_gen(FILE *fptr, double **x1, double **x2, double a, int num_points) {
    
    double tinit = (x1[1][0] / (2 * a));
    double tfinal = (x2[1][0] / (2 * a));
    double **point = createMat(2, 1);
    if (tfinal > tinit) {
        for (double i = tinit; i <= tfinal; i += 1.0 / num_points) {
            point[0][0] = a * i * i;
            point[1][0] = 2 * a * i;
            fprintf(fptr, "%lf,%lf\n", point[0][0], point[1][0]);  // Don't forget newline for correct formatting
    }
}
    else{
    	for (double i = tfinal; i <= tinit; i += 1.0 / num_points) {
            point[0][0] = a * i * i;
            point[1][0] = 2 * a * i;
            fprintf(fptr, "%lf,%lf\n", point[0][0], point[1][0]);  // Don't forget newline for correct formatting
        }
    }
    freeMat(point, 2);  // Free point vector
}

double** intersect_of_parab_line(double **V,double **u,double f,double **point_on_line,double **dir){
	double m1 = dir[0][0];
	double m2 = dir[1][0];
	double V1 = V[0][0];
	double V2 = V[1][0];
	double V3 = V[0][1];
	double V4 = V[1][1];
	double u1 = u[0][0];
	double u2 = u[1][0];
	double h1 = point_on_line[0][0];
	double h2 = point_on_line[1][0];
	
	double A = V1*m1*m1+(V2+V3)*m1*m2+V4*m2*m2;
	double B = 2*(m1*(V1*h1+V2*h2+u1)+m2*(V3*h1+V4*h2+u2));
	double C = h1*(V1*h1+V2*h2)+h2*(V3*h1+V4*h2)+2*(u1*h1+u2*h2)+f;
	
	if(B*B-4*A*C<0){
		return NULL;
	}
	else if(B*B-4*A*C==0){
		double k;
		double **intersect;
		
		k = (-B)/(2*A);
		intersect = createMat(2,1);
		intersect = Matadd(point_on_line, Matscale(dir,2,1,k),2,1);
		return intersect;
	}
	else if(B*B-4*A*C>0){
		double k1 = (-B+sqrt(B*B-4*A*C))/(2*A), k2 = (-B-sqrt(B*B-4*A*C))/(2*A);
		double **intersect1 = createMat(2,1);
		double **intersect2 = createMat(2,1);
		double **intersect = createMat(2,2);
		intersect1 = Matadd(point_on_line, Matscale(dir,2,1,k1),2,1);
		intersect2 = Matadd(point_on_line, Matscale(dir,2,1,k2),2,1);
		intersect[0][0] = intersect1[0][0];
		intersect[1][0] = intersect1[1][0];
		intersect[0][1] = intersect2[0][0];
		intersect[1][1] = intersect2[1][0];
		return intersect;
	}
}


int main(){
	double **V = createMat(2,2), **u = createMat(2,1), f, **point_on_line = createMat(2,1), **dir = createMat(2,1);
    
    V[0][0] = 0;
    V[1][0] = 0;
    V[0][1] = 0;
    V[1][1] = 1;
    
    u[0][0] = -4*sqrt(2);
    u[1][0] = 0;
    
    f = 0;
    
    point_on_line[0][0] = 8*sqrt(2);
    point_on_line[1][0] = 0;
    
    dir[0][0] = 0;
    dir[1][0] = 1;
    
    double **intersection = createMat(2,2);
    intersection = intersect_of_parab_line(V,u,f,point_on_line,dir);
    
    double **x1 = createMat(2,1);
    double **x2 = createMat(2,1);
    x1[0][0] = intersection[0][0];
    x1[1][0] = intersection[1][0];
    x2[0][0] = intersection[0][1];
    x2[1][0] = intersection[1][1];
    
    // Open file to write points
    FILE *fptr;
    fptr = fopen("parab.dat", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    parab_y2_4ax_gen(fptr,x1,x2,-u[0][0]/2,150);
    
        
    // Close the file
    fclose(fptr);

    // Free all allocated memory
    freeMat(x1, 2);
    freeMat(x2, 2);
    freeMat(dir,2);
    freeMat(point_on_line,2);

    return 0;
}
