#ifndef polygon
#define polygon

#include "vertex.h"
#include "matrixWork.h"
#include <GL/glut.h>

class Polygon{
public:
	Polygon();
	Polygon(const Polygon& other);
	void makeArrow(int xStretch, int yStretch);//creates an arrow with 7 points 
	void drawPolygonOutline();//draws the polygon onto the screen
	int getNumPoints();
	Vertex * firstVertex;//the first vertex, used to link to the linked list of vertex points
	Vertex center;//currently unused
	int numPoints;
	void translatePolygon(double x, double y);
	void rotatePolygon(double rotSpeed);
	void rotatePolygon(double rotSpeedX, double rotSpeedY, double rotSpeedZ);
	void scalePolygon(double scale);
	void reflectPolygon();
	void addVertex(Vertex v);			//add vertex, can add even if polygon is empty
	void addVertex(double x, double y);	//overload
	void addVertex(double x, double y, double z);	//overload

	~Polygon();		//kill all the pointers when deconstructing


};




#endif