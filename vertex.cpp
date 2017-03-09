

#include "vertex.h"

Vertex::Vertex(double xcoord, double ycoord){
	this->coords[0][0] = xcoord;
	this->coords[1][0] = ycoord;
	this->coords[2][0] = 0;//z
	this->coords[3][0] = 1;//w
	this->next = NULL;//No next point
}
Vertex::Vertex(double xcoord, double ycoord, double zcoord){
	this->coords[0][0] = xcoord;
	this->coords[1][0] = ycoord;
	this->coords[2][0] = zcoord;//z
	this->coords[3][0] = 1;//w
	this->next = NULL;//No next point
}
Vertex::Vertex(double xcoord, double ycoord, Vertex &v){
	this->coords[0][0] = xcoord;
	this->coords[1][0] = ycoord;
	this->coords[2][0] = 0;//z
	this->coords[3][0] = 1;//w
	this->next = &v;
}
Vertex::Vertex(){
	this->coords[2][0] = 0;//z
	this->coords[3][0] = 1;//w
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