

#include "vertex.h"

Vertex::Vertex(double xcoord, double ycoord){
	this->coords[0][0] = xcoord;
	this->coords[1][0] = ycoord;
	this->coords[2][0] = 0;//z
	this->coords[3][0] = 1;//w
	this->next = NULL;//No next point
	this->normal[0][0] = 0;
	this->normal[1][0] = 0;
	this->normal[2][0] = 0;
	this->normal[3][0] = 0;
}
Vertex::Vertex(double xcoord, double ycoord, double zcoord){
	this->coords[0][0] = xcoord;
	this->coords[1][0] = ycoord;
	this->coords[2][0] = zcoord;//z
	this->coords[3][0] = 1;//w
	this->next = NULL;//No next point
	this->normal[0][0] = 0;
	this->normal[1][0] = 0;
	this->normal[2][0] = 0;
	this->normal[3][0] = 0;
}
Vertex::Vertex(double xcoord, double ycoord, Vertex &v){
	this->coords[0][0] = xcoord;
	this->coords[1][0] = ycoord;
	this->coords[2][0] = 0;//z
	this->coords[3][0] = 1;//w
	this->next = &v;
	this->normal[0][0] = 0;
	this->normal[1][0] = 0;
	this->normal[2][0] = 0;
	this->normal[3][0] = 0;
}
Vertex::Vertex(){
	this->coords[2][0] = 0;//z
	this->coords[3][0] = 1;//w
	this->normal[0][0] = 0;
	this->normal[1][0] = 0;
	this->normal[2][0] = 0;
	this->normal[3][0] = 0;
}

Vertex::Vertex(Vertex * v){//Copy the entire linked list of vertices all the way down
	this->coords[0][0] = v->getX();
	this->coords[1][0] = v->getY();
	this->coords[2][0] = v->getZ();
	this->coords[3][0] = 1;

	Vertex * head = v;
	Vertex * curr = this;
	do{
		curr->next = new Vertex();
		curr = curr->next;
		head = head->next;
		curr->coords[0][0] = head->getX();
		curr->coords[1][0] = head->getY();
		curr->coords[2][0] = head->getZ();
		curr->coords[3][0] = 1;

	}while(head->next != v);
	curr->next = this;
	this->normal[0][0] = 0;
	this->normal[1][0] = 0;
	this->normal[2][0] = 0;
	this->normal[3][0] = 0;
}
Vertex::Vertex(Vertex * v, Vertex * otherFirstVertex){//currently unused?  Keep for now, may add functionality later
	this->coords[0][0] = v->getX();
	this->coords[1][0] = v->getY();
	this->coords[2][0] = v->getZ();
	this->coords[3][0] = 1;
	if(v!= otherFirstVertex){
		Vertex *curr = new Vertex(v->next, otherFirstVertex);
		this->next = curr;
	}
	else{
		this->next = NULL;
	}
	this->normal[0][0] = 0;
	this->normal[1][0] = 0;
	this->normal[2][0] = 0;
	this->normal[3][0] = 0;
}


void Vertex::setNewXYZ(Vertex v, double xcoord, double ycoord, double zcoord){//set x,y,z of some vertex v
	v.coords[0][0] = xcoord;
	v.coords[1][0] = ycoord;
	v.coords[2][0] = zcoord;
}

void Vertex::setNewXYZ(double xcoord, double ycoord, double zcoord){//set x,y,z of this vertex
	this->coords[0][0] = xcoord;
	this->coords[1][0] = ycoord;
	this->coords[2][0] = zcoord;
}

void Vertex::setNewXY(Vertex v, double xcoord, double ycoord){//set x,y of some vertex v
	v.coords[0][0] = xcoord;
	v.coords[1][0] = ycoord;
}

void Vertex::setNewXY(double xcoord, double ycoord){//set x,y of this vertex
	this->coords[0][0] = xcoord;
	this->coords[1][0] = ycoord;
}


double Vertex::getX() const{
	return this->coords[0][0];
}
double Vertex::getY() const{
	return this->coords[1][0];
}
double Vertex::getZ() const{
	return this->coords[2][0];
}
Vertex Vertex::getNext() const{
	return *(this->next);
}
Vertex* Vertex::getNextPointer() const{
	return this->next;
}
Vertex& Vertex::operator=(const Vertex& other){//copy the vertex
	this->coords[0][0] = other.getX();
	this->coords[1][0] = other.getY();
	this->coords[2][0] = other.getZ();
	this->next = other.getNextPointer();
}

void Vertex::setNormal(double x, double y, double z){
	this->normal[0][0] = x;
	this->normal[1][0] = y;
	this->normal[2][0] = z;
	this->normal[3][0] = 0;
}
double Vertex::getNormalX(){
	return this->normal[0][0];
}
double Vertex::getNormalY(){
	return this->normal[1][0];
}
double Vertex::getNormalZ(){
	return this->normal[2][0];
}
void Vertex::getNormal(double arr[4][1]){
	arr[0][0] = this->normal[0][0];
	arr[1][0] = this->normal[1][0];
	arr[2][0] = this->normal[2][0];
	arr[3][0] = this->normal[3][0];

}