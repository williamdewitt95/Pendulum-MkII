#ifndef GLOP_GLOBALS
#define GLOP_GLOBALS

#include <GL/glew.h> 

#include <iostream>
#include <string.h>

#include <GL/glut.h>
#include <chrono>
#include <ratio>
#include <ctime>
#include <cmath>
#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include "SOIL.h"   

typedef struct colortype {
	float red;
	float green;
	float blue;
} colortype;

struct texture2D{
	std::string name;
	int width;
	int height;
	GLuint texID;
};

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

	texture2D walls;
	texture2D table;
	texture2D pendulumStick;
	texture2D pendulumHolder;
	texture2D pendulumBall;
	texture2D floor;
	texture2D ceiling;

};

extern GLOBAL_SETTINGS GLOBAL;

void windowResize(int width, int height);
void scaleMouse(int &x, int &y);
void cameraMovement(int x, int y);
void loadTextures(texture2D &tex);
void initLight();
#endif
