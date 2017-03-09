#ifndef vertex
#define vertex

#include <stdio.h>

class Vertex{
public:

	Vertex();
	Vertex(double xcoord, double ycoord);
	Vertex(double xcoord, double ycoord, double zcoord);
	Vertex(double xcoord, double ycoord, Vertex &v);
	Vertex(Vertex * v);//create a copy of this vertex, and also copy the entire list all the way (Assume circularly linked!)
	Vertex(Vertex * v, Vertex * otherFirstVertex);//unused/dysfunctional (?)

	void setNewXYZ(Vertex v, double xcoord, double ycoord, double zcoord);//set x,y,z of some vertex v
	void setNewXYZ(double xcoord, double ycoord, double zcoord);//set x,y,z of this vertex
	void setNewXY(Vertex v, double x, double y);//set x,y of vertex v
	void setNewXY(double x, double y);			//set x,y of this vertex
	void setNext(Vertex v1, Vertex& v2);		
	double getX() const;
	double getY() const;
	double getZ() const;
	Vertex getNext() const;
	Vertex* getNextPointer() const;
	Vertex * next;							//the next vertex in the list
	Vertex& operator=(const Vertex& other);//copy the vertex
	double coords[4][1];	//4by1 array to hold the coordinates: x,y,z,w


};



#endif