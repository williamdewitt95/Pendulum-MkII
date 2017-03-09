#include "matrixWork.h"


// This procedure multiplies matrix a and vector b to return vector c
void mv_mult ( double a[][4], int dim1a, int dim2a,
               double b[][1], int dim1b, int dim2b,
               double c[][1], int dim1c, int dim2c ){

int i, j, k;

for (i=0; i<dim1a; i++) {
    for (j=0; j<dim2b; j++) {
       c[i][j] = 0.0;
       for (k=0; k<dim1a; k++) c[i][j] += a[i][k] * b[k][j]; 
    }
}


}


void buildZRotationMatrix( double mat[][4], double theta ){

theta = theta * M_PI / 180.0;

/* Define Rotation Matrix around Z-Axis */

mat[0][0] = cos(theta); mat[0][1] = -sin(theta); mat[0][2] = 0.0; mat[0][3] = 0.0;
mat[1][0] = sin(theta); mat[1][1] =  cos(theta); mat[1][2] = 0.0; mat[1][3] = 0.0;
mat[2][0] =    0.0    ; mat[2][1] =     0.0    ; mat[2][2] = 1.0; mat[2][3] = 0.0;
mat[3][0] =    0.0    ; mat[3][1] =     0.0    ; mat[3][2] = 0.0; mat[3][3] = 1.0;

}

void buildXRotationMatrix( double mat[][4], double theta ){

theta = theta * M_PI / 180.0;

/* Define Rotation Matrix around X-Axis */

mat[0][0] =    1.0    ; mat[0][1] = 	0.0      ; mat[0][2] = 0.0;	           mat[0][3] = 0.0;
mat[1][0] =    0.0    ; mat[1][1] =  cos(theta); mat[1][2] = -sin(theta);    mat[1][3] = 0.0;
mat[2][0] =    0.0    ; mat[2][1] =  sin(theta); mat[2][2] = cos(theta);     mat[2][3] = 0.0;
mat[3][0] =    0.0    ; mat[3][1] =     0.0    ; mat[3][2] = 0.0;            mat[3][3] = 1.0;

}

void buildYRotationMatrix( double mat[][4], double theta ){

theta = theta * M_PI / 180.0;

/* Define Rotation Matrix around Y-Axis */

mat[0][0] = cos(theta) ;  mat[0][1] =     0.0    ; mat[0][2] =  sin(theta)  ; mat[0][3] = 0.0;
mat[1][0] =    0.0     ;  mat[1][1] =     1.0    ; mat[1][2] =   0.0        ; mat[1][3] = 0.0;
mat[2][0] = -sin(theta);  mat[2][1] =     0.0    ; mat[2][2] =  cos(theta)  ; mat[2][3] = 0.0;
mat[3][0] =    0.0     ;  mat[3][1] =     0.0    ; mat[3][2] =   0.0        ; mat[3][3] = 1.0;

}




void buildZTranslateMatrix(double mat[][4], double tx, double ty, double tz){

mat[0][0] =    1.0    ; mat[0][1] = 	0.0      ; mat[0][2] = 0.0; mat[0][3] = tx;
mat[1][0] =	   0.0    ; mat[1][1] = 	1.0      ; mat[1][2] = 0.0; mat[1][3] = ty;
mat[2][0] =    0.0    ; mat[2][1] =     0.0    ; mat[2][2] = 1.0; mat[2][3] = tz;
mat[3][0] =    0.0    ; mat[3][1] =     0.0    ; mat[3][2] = 0.0; mat[3][3] = 1.0;

}

void buildZScaleMatrix(double mat[][4], double sx, double sy, double sz){

mat[0][0] =    sx; 		mat[0][1] = 	0.0; 	 mat[0][2] = 0.0; mat[0][3] = 0.0;
mat[1][0] =	   0.0; 	mat[1][1] = 	sy; 	 mat[1][2] = 0.0; mat[1][3] = 0.0;
mat[2][0] =    0.0    ; mat[2][1] =     0.0    ; mat[2][2] = sz;  mat[2][3] = 0.0;
mat[3][0] =    0.0    ; mat[3][1] =     0.0    ; mat[3][2] = 0.0; mat[3][3] = 1.0;

}

void buildYReflectionMatrix(double mat[][4]){

mat[0][0] =   -1.0;    mat[0][1] =   0.0;   mat[0][2] = 0.0; mat[0][3] = 0.0;
mat[1][0] =    0.0;    mat[1][1] =   1.0;    mat[1][2] = 0.0; mat[1][3] = 0.0;
mat[2][0] =    0.0    ; mat[2][1] =     0.0    ; mat[2][2] = 1.0;  mat[2][3] = 0.0;
mat[3][0] =    0.0    ; mat[3][1] =     0.0    ; mat[3][2] = 0.0; mat[3][3] = 1.0;

}

void matrixCopy_Xby1(double matOriginal[][1], double matCopy[][1], int dimension){//copy the matrix over

  for(int i=0; i< dimension; i++){
      matCopy[i][0] = matOriginal[i][0];
  }

}