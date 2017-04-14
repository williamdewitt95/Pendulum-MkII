#ifndef polygon
#define polygon

#include "globals.h"

#include "vertex.h"
#include "matrixWork.h"
#include "myUtils.h"
#include <GL/glut.h>


class Polygon{
public:
	Polygon();
	Polygon(const Polygon& other);
	void drawPolygonOutline();//draws the polygon onto the screen
	void drawPolygon();//3d
	int getNumPoints();
	Vertex * firstVertex;//the first vertex, used to link to the linked list of vertex points
	Vertex center;//currently unused
	Vertex * firstTextureVertex;//for mapping textures
	bool texture2DExists;
	int numPoints;
	texture2D texture;
	Vertex getNormal();
	void translatePolygon(double x, double y);
	void rotatePolygon(double rotSpeed);
	void rotatePolygon(double rotSpeedX, double rotSpeedY, double rotSpeedZ);
	void scalePolygon(double scale);
	void reflectPolygon();
	void addVertex(Vertex v);			//add vertex, can add even if polygon is empty
	void addVertex(double x, double y);	//overload
	void addVertex(double x, double y, double z);	//overload
	void addTextureVertex(double x, double y, double z);//Add verices but to the texture vertex list
	void setTexture(texture2D &newTex);
	static void vertexCB(void* data, void *polygon);



	~Polygon();		//kill all the pointers when deconstructing


};




#endif