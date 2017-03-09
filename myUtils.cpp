//#ifndef myUtils
//#define myUtils
#include "myUtils.h"


int dotProd3d_i( int a[], int b[] ){
return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

int dotProd2d_i( int a[], int b[] ){
return a[0]*b[0] + a[1]*b[1];
}
int dotProd2d_4i( int x1, int y1, int x2, int y2 ){
return x1*x2 + y1*y2;
}

double dotProd3d_d( double a[], double b[] ){
return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

double dotProd2d_d( double a[], double b[] ){
return a[0]*b[0]+a[1]*b[1];
}

double det2x2(double mat[2][2]){
return mat[0][0]*mat[1][1] - mat[1][0]*mat[0][1];
}

double det2x2_4d (double a, double b, double c, double d){
return a*d-b*c;
}
int det2x2_4i (int a, int b, int c, int d){
return a*d-b*c;
}
double * crossProd(double a[3], double b[3], double result[3]){

result[0] = a[1]*b[2] - b[1]*a[2];
result[1] = a[0]*b[2] - b[0]*a[2];
result[2] = a[0]*b[1] - b[0]*a[1];
return result;
}
double crossProdZ(double a[], double b[]){
return a[0]*b[1] - b[0]*a[1];
}
double crossProdZ_4d(double ax, double ay, double bx, double by){
return ax*by - ay*bx;
}

/*Where (x1,y1) forms a line with (x2,y2) and (x3,y3) forms a line with (x4,y4)*/

bool intersect2d_8i(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4){//return true if the lines intersect
	double ud = det2x2_4d(x2-x1, -1*(x4-x3), y2-y1, -1*(y4-y3));	
	if(ud==0)
		return false;
	else{
		double ua = det2x2_4d(x3-x1, -1*(x4-x3), y3-y1, -1*(y4-y3) ) / ud;
    	double ub = det2x2_4d(x2-x1, x3-x1, y2-y1, y3-y1) / ud;
		if( ((ua>0) && (ua<1)) && ((ub>0) && (ub<1)) ){
			return true;
		}
		return false;
	}
}
bool intersect2d_8d(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4){//return true if the lines intersect
	double ud = det2x2_4d(x2-x1, -1.0*(x4-x3), y2-y1, -1.0*(y4-y3));	//ad -bc
	if(float(ud)==0.0){
		// if(isCollinear(x1,y1, x3,y3, x4,y4) || isCollinear(x2,y2, x3,y3, x4,y4)){
		// 	return true;
		// }
		return false;
	}
	else{
		double ua = det2x2_4d(x3-x1, -1.0*(x4-x3), y3-y1, -1.0*(y4-y3) ) / ud; 
    	double ub = det2x2_4d(x2-x1, x3-x1, y2-y1, y3-y1) / ud;
		// if( ((ua>0.00000000000005) && (ua<0.9999999999995)) && ((ub>0.00000000000005) && (ub<0.9999999999995)) ){//floating point errors necessitate changing this from 1.0 and 0.0 to .99...995 and .00...005
    	// if( ((ua>0.0) && (ua<1.0)) && ((ub>0.0) && (ub<1.0)) ){
    	if(float(ua)>0.0 && float(ua)<1.0    &&      float(ub)>0.0 && float(ub)<1.0){
			return true;    	
		}
		return false;
	}
}

double uaIntersect2d_8d(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4){ //returns ua
	double ud = det2x2_4d(x2-x1, -1.0*(x4-x3), y2-y1, -1.0*(y4-y3));//ad - bc
	if(ud==0.0){//error
		return 0;
	}
	else{
		return det2x2_4d(x3-x1, -1.0*(x4-x3), y3-y1, -1.0*(y4-y3) ) / ud;
	}
}

double ubIntersect2d_8d(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4){//returns ub
	double ud = det2x2_4d(x2-x1, -1.0*(x4-x3), y2-y1, -1.0*(y4-y3));//ad - bc
	if(ud==0.0){//error

		return 0;
	}
	else{
		return det2x2_4d(x2-x1, x3-x1, y2-y1, y3-y1) / ud;
	}
}


bool isCollinear( double x, double y, double ax, double ay, double bx, double by){
    if (ax != bx && ay == by) {    //if ax == bx, line isn't vertical, test x
        if (ax <= x && x <= bx)
            return true;
        if (ax >= x && x >= bx)
            return true;
    }
    else if(ax == bx && ay != by){    // line is vertical, test y  
        if (ay <= y && y <= by)
            return true;
        if (ay >= y && y >= by)
            return true;
    }
    return false;
}


//#endif