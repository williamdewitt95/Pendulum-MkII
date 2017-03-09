#ifndef GLOP_GLOBALS
#define GLOP_GLOBALS

#include <iostream>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <chrono>
#include <ratio>
#include <ctime>
#include <cmath>

typedef struct colortype {
	float red;
	float green;
	float blue;
} colortype;

class GLOBAL_SETTINGS{
public:
	GLOBAL_SETTINGS();
	int WINDOW_MAX_X;
	int WINDOW_MAX_Y;

	double WORLD_COORDINATE_MIN_X;
	double WORLD_COORDINATE_MAX_X;
	double WORLD_COORDINATE_MIN_Y;
	double WORLD_COORDINATE_MAX_Y;

	struct {
		double x;
		double y;
		double z;
	} CAMERA_POS;
	struct {
		double x;
		double y;
		double z;
	} CAMERA_LOOK_VECTOR;
	double CAMERA_ANGLE_VERTICAL;
	double CAMERA_ANGLE_HORIZONTAL;

};

extern GLOBAL_SETTINGS GLOBAL;

void windowResize(int width, int height);
void scaleMouse(int &x, int &y);
void cameraMovement(int x, int y);
#endif
