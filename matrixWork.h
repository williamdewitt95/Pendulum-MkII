#ifndef matrixWork
#define matrixWork
#include <cstdio>
#include <cmath>


void mv_mult ( double a[][4], int dim1a, int dim2a,
               double b[][1], int dim1b, int dim2b,
               double c[][1], int dim1c, int dim2c );

void buildZRotationMatrix( double mat[][4], double theta );

void buildXRotationMatrix( double mat[][4], double theta );

void buildYRotationMatrix( double mat[][4], double theta );

void buildZTranslateMatrix(double mat[][4], double tx, double ty, double tz);

void buildZScaleMatrix(double mat[][4], double sx, double sy, double sz);

void buildYReflectionMatrix(double mat[][4]);

void matrixCopy_Xby1(double matOriginal[][1], double matCopy[][1], int dimension); //copy the matrix


#endif