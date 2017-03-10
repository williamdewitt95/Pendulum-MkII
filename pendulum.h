#ifndef pendulum
#define pendulum

#include "polygon.h"
#include "globals.h"


typedef struct pendulumHolder {
	Polygon faces[12];
} polygonListPendulumHolder;


void definePendulumHolder( Polygon *face );
void drawFilledPendulumHolder(Polygon *face, int numFaces);

void definePendulumStick( Polygon *faces );
void drawFilledPendulumStick(Polygon *face, int numFaces);

void definePendulumBall( Polygon *faces );
void drawFilledPendulumBall(Polygon *face, int numFaces);

void drawFilledPendulum(Polygon *faces1, int numFaces1, double angle);



#endif