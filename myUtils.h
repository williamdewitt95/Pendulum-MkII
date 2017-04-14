#ifndef myUtils
#define myUtils

int dotProd3d_i( int a[], int b[] );
int dotProd2d_i( int a[], int b[] );
int dotProd2d_4i( int x1, int y1, int x2, int y2 );


double dotProd3d_d( double a[], double b[] );
double dotProd2d_d( double a[], double b[] );

double det2x2(double mat[2][2]);
int det2x2_4i (int a, int b, int c, int d);

double det2x2_4d (double a, double b, double c, double d);

double * crossProd(double a[], double b[]);

double crossProdZ(double a[], double b[]);
void crossProd4by1(double a[4][1], double b[4][1], double result[4][1]);
double crossProdZ_4d(double ax, double ay, double bx, double by);


bool intersect2d_8i(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4);
bool intersect2d_8d(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4);//return true if the lines intersect

double uaIntersect2d_8d(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4);
double ubIntersect2d_8d(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4);

bool isCollinear( double x, double y, double ax, double ay, double bx, double by);




#endif
