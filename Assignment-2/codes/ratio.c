#include <stdio.h>

int main()
{
    FILE *file = fopen("point.txt", "w"); 
    if (file == NULL)
    {
        perror("Error opening file");
        return 1; 
    }

    double k , yR; //Variables to be found
    double P[2][1] = {2 , -2}; //Co-ordinates of the point P
    double Q[2][1] = {3 , 7}; //Co-Ordinate of the point Q
    double R[2][1] ; 
    R[0][0] = (float)24/11; // X-coordinate of R 
    // Finding K using the x-coordinates of the P, Q and R
   
     k = (R[0][0] - P[0][0]) / (Q[0][0] - R[0][0]);

     //Find the value of y using the K we found from the above equation
     yR = (k * Q[1][0] + P[1][0]) / (k + 1);
     R[1][0] = yR; // Y-coordinate of R
     fprintf(file, "%.2f  %.2f \n", P[0][0], P[1][0]);
     fprintf(file, "%.2f  %.2f \n", Q[0][0], Q[1][0]);
     fprintf(file, "%.2f  %.2f \n", R[0][0], R[1][0]);

     fclose(file); //Ends the file
     
}
