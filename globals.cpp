
#include "globals.h"

GLOBAL_SETTINGS::GLOBAL_SETTINGS(){
	WINDOW_MAX_X = 1000;
	WINDOW_MAX_Y = 1000;

	WORLD_COORDINATE_MIN_X = 0.0;
	WORLD_COORDINATE_MAX_X = 1000.0;
	WORLD_COORDINATE_MIN_Y = 0.0;
	WORLD_COORDINATE_MAX_Y = 1000.0;

	CAMERA_POS = {0,1,1};
	CAMERA_LOOK_VECTOR = {0,1,0};
	CAMERA_ANGLE_VERTICAL = 0;
	CAMERA_ANGLE_HORIZONTAL = 90;
}

GLOBAL_SETTINGS GLOBAL;


void windowResize(int width, int height){

	//move the world cordinates to match the change in the windows draw area
	GLOBAL.WORLD_COORDINATE_MIN_X += 0;
	GLOBAL.WORLD_COORDINATE_MAX_X += width - GLOBAL.WINDOW_MAX_X;
	GLOBAL.WORLD_COORDINATE_MIN_Y += 0;
	GLOBAL.WORLD_COORDINATE_MAX_Y += height - GLOBAL.WINDOW_MAX_Y;

	//remember what the new size of the window is
	GLOBAL.WINDOW_MAX_X = width;
	GLOBAL.WINDOW_MAX_Y = height;

	//make the scene visable over the whole window
	glViewport(0,0,width,height);
	glutPostRedisplay();
}

void scaleMouse(int &x, int &y){
	y=GLOBAL.WINDOW_MAX_Y-y;

	y*=(GLOBAL.WORLD_COORDINATE_MAX_Y - GLOBAL.WORLD_COORDINATE_MIN_Y) / ((double)GLOBAL.WINDOW_MAX_Y);
	x*=(GLOBAL.WORLD_COORDINATE_MAX_X - GLOBAL.WORLD_COORDINATE_MIN_X) / ((double)GLOBAL.WINDOW_MAX_X);

	y+=GLOBAL.WORLD_COORDINATE_MIN_Y;
	x+=GLOBAL.WORLD_COORDINATE_MIN_X;
}


void cameraMovement(int x, int y){//move the camera around not bound to the tank
	double movementDivisor = 6.0;
	//x and y are window cordinates
	//it is up to us to get deltas
	y=GLOBAL.WINDOW_MAX_Y-y;
	int midX = GLOBAL.WINDOW_MAX_X/2;
	int midY = GLOBAL.WINDOW_MAX_Y/2;

	int dx = x-midX;
	int dy = y-midY;
	

	double &angleH = GLOBAL.CAMERA_ANGLE_HORIZONTAL;
	double &angleV = GLOBAL.CAMERA_ANGLE_VERTICAL;
	angleH += dx/movementDivisor;
	if(angleH>360)angleH-=360;
	if(angleH<0)angleH+=360;
	angleV += dy/movementDivisor;
	if(angleV>90)angleV=90;
	if(angleV<-90)angleV=-90;

	// we will have a length of 5 for the line in the XY plane
	GLOBAL.CAMERA_LOOK_VECTOR.x = 5 * ( cos(angleH*M_PI/180.0));
	GLOBAL.CAMERA_LOOK_VECTOR.y = 5 * (-sin(angleH*M_PI/180.0));
	// make the z from pythagorean formula - our angle is measured from the horizontal plane
	GLOBAL.CAMERA_LOOK_VECTOR.z = 5 * tan(angleV*M_PI/180.0);

	if(dx==0 && dy==0)
		return; //we are not really doing anything, so we will simply ignore this thing


	glutWarpPointer(midX,GLOBAL.WINDOW_MAX_Y-midY);
}

