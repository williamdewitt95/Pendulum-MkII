#ifndef table3d
#define table3d

#include "polygon.h"
#include "globals.h"



typedef struct polygonListTableTop {
	Polygon tableFaces[6];
} polygonListTableTop;

typedef struct polygonListTableLegs {
	Polygon legFaces[4];
} polygonListTableLegs;

void defineTableTop( Polygon *face );
void drawFilledTableTop(Polygon *face);
void rotateTableTop(double rotX, double rotY, double rotZ);

void defineTableLeg( Polygon *face );
void drawFourLegs(Polygon *face);
void drawFilledTableLeg(Polygon *face);
void rotateTableLeg(double rotX, double rotY, double rotZ);


#endif