#ifndef house
#define house

#include "globals.h"
#include "polygon.h"


typedef struct polygonList {
	Polygon faces[6];
} polygonList;


void defineHouse( Polygon *face );
void drawFilledHouse(Polygon *face);
void rotateHouse(double rotX, double rotY, double rotZ, bool b);
// void helloWorld();



#endif