#include "polygon.h"

    

Polygon::Polygon(){//where x,y is the center
	this->firstVertex = NULL;
	this->numPoints = 0;
}
 Polygon::Polygon(const Polygon& other){//where other is another polygon you want to copy
 	if(other.numPoints > 0){
		this->firstVertex = new Vertex(other.firstVertex);
		this->numPoints = other.numPoints;
	}
	else{
		this->firstVertex = NULL;
		this->numPoints = 0;
	}

 }

void Polygon::makeArrow(int xStretch, int yStretch){//this will initialize the arrow at the start of the program with center at the origin
	//Make Points here

	//xStretch,yStretch typically  600,300, all values listed will be assuming those

	this->firstVertex= new Vertex(0.0-xStretch*1.0/2.0, 0.0-yStretch*1.0/3.0);//-300,-100
	
	this->firstVertex->next = new Vertex(xStretch*1.0/6.0, 0.0-yStretch*1.0/3.0);//vertex 1 next is 2 (100,-100)
	Vertex * curr = this->firstVertex->next;

 	curr->next = new Vertex(xStretch*1.0/12.0, 0.0-yStretch*1.0/2.0);//vertex 2 next is 3 (50,-150)
 	curr = curr->next;
 	curr->next = new Vertex(xStretch*1.0/2.0, 0.0);//vertex 3 next is 4 (300,0)
 	curr = curr->next;
 	curr->next = new Vertex(xStretch*1.0/12.0, yStretch*1.0/2.0);//vertex 4 next is 5 (50,150)
 	curr = curr->next;
 	curr->next = new Vertex(xStretch*1.0/6.0, yStretch*1.0/3.0);//vertex 5 next is 6 (100,100)
 	curr = curr->next;
 	curr->next = new Vertex(0.0-xStretch*1.0/2.0, yStretch*1.0/3.0);//vertex 6 next is 7 (-300,100)
 	curr = curr->next;
 	curr->next = this->firstVertex;//vertex 7 next is 1
	
	numPoints = 7;//tracks the number of vertices contained in the polygon
}

void Polygon::drawPolygonOutline(){//draw the lines
	// printf("%lu\n",this->firstVertex);
	if(numPoints<3){//cannot draw a Polygon if less than three sides
		// printf("numPoints<3");
		return;
	}
	glColor3f( 1.0, 0.0, 0.0 );
	glBegin(GL_LINE_LOOP);
	
 	Vertex * temp = (this->firstVertex);
	do{
		glVertex2i(temp->getX()*1, temp->getY()*1);
		// printf("drawPolygonOutline x,y: %f, %f\n",temp->getX(), temp->getY());
		temp = temp->next;
	}while(temp != this->firstVertex);

	glEnd();
}




int Polygon::getNumPoints(){
	return this->numPoints;
}


void Polygon::translatePolygon(double x, double y){
		 // printf("\ntranslateArrow(), x,y: %f,%f\n",x,y);

	double translateMatrix[4][4];
	buildZTranslateMatrix(translateMatrix, x, y, 0.0);
	double temp[4][1];
	Vertex * tempVertex = firstVertex;
	do{
		mv_mult(translateMatrix,4,4,tempVertex->coords,4,1,temp,4,1);
		matrixCopy_Xby1(temp, tempVertex->coords, 4);
		tempVertex = tempVertex->next;	

	}while(tempVertex != firstVertex);
	

}


void Polygon::rotatePolygon(double rotSpeed){//rotate the polygon by rotSpeed degrees

	double rotMatrix[4][4];
	buildZRotationMatrix(rotMatrix,rotSpeed);//build a rotation matrix
	Vertex * tempVertex = firstVertex;
	double temp[4][1];
	
	do{
		mv_mult(rotMatrix,4,4,tempVertex->coords,4,1,temp,4,1);	//multiply the matrices together, put result into temp[4][1]
		matrixCopy_Xby1(temp, tempVertex->coords, 4);			//copy back the matrix into the coordinate points
		tempVertex = tempVertex->next;							//move the pointer to the next vertex
	}while(tempVertex != firstVertex);

}
void Polygon::rotatePolygon(double rotSpeedX, double rotSpeedY, double rotSpeedZ){//rotate the polygon by rotSpeed degrees

	double rotMatrixZ[4][4];
	buildZRotationMatrix(rotMatrixZ,rotSpeedZ);//build a rotation matrix
	Vertex * tempVertex = firstVertex;
	double temp[4][1];
	
	do{
		mv_mult(rotMatrixZ,4,4,tempVertex->coords,4,1,temp,4,1);	//multiply the matrices together, put result into temp[4][1]
		matrixCopy_Xby1(temp, tempVertex->coords, 4);			//copy back the matrix into the coordinate points
		tempVertex = tempVertex->next;							//move the pointer to the next vertex
	}while(tempVertex != firstVertex);

	double rotMatrixY[4][4];
	buildZRotationMatrix(rotMatrixY,rotSpeedY);//build a rotation matrix
	tempVertex = firstVertex;
	// double temp[4][1];
	
	do{
		mv_mult(rotMatrixY,4,4,tempVertex->coords,4,1,temp,4,1);	//multiply the matrices together, put result into temp[4][1]
		matrixCopy_Xby1(temp, tempVertex->coords, 4);			//copy back the matrix into the coordinate points
		tempVertex = tempVertex->next;							//move the pointer to the next vertex
	}while(tempVertex != firstVertex);

	double rotMatrixX[4][4];
	buildZRotationMatrix(rotMatrixX,rotSpeedX);//build a rotation matrix
	tempVertex = firstVertex;
	// double temp[4][1];
	
	do{
		mv_mult(rotMatrixX,4,4,tempVertex->coords,4,1,temp,4,1);	//multiply the matrices together, put result into temp[4][1]
		matrixCopy_Xby1(temp, tempVertex->coords, 4);			//copy back the matrix into the coordinate points
		tempVertex = tempVertex->next;							//move the pointer to the next vertex
	}while(tempVertex != firstVertex);


}



void Polygon::scalePolygon(double scale){//scale the polygon

 	double scaleMatrix[4][4];
 	buildZScaleMatrix(scaleMatrix, scale, scale, 1);//build a scale matrix
 	Vertex * tempVertex = firstVertex;
 	double temp[4][1];
 	
	do{
		mv_mult(scaleMatrix,4,4,tempVertex->coords,4,1,temp,4,1);	//multiply the matrices together, put result into temp[4][1]
		matrixCopy_Xby1(temp, tempVertex->coords, 4);				//copy back the matrix into the coordinate points
		tempVertex = tempVertex->next;								//move the pointer to the next vertex

	}while(tempVertex != firstVertex);
 }

void Polygon::reflectPolygon(){//create a reflection matrix
	double reflectMatrix[4][4];
	buildYReflectionMatrix(reflectMatrix);//build the reflection matrix
	Vertex * tempVertex = firstVertex;
 	double temp[4][1];
	do{
		mv_mult(reflectMatrix,4,4,tempVertex->coords,4,1,temp,4,1); 	//multiply the matrices together, put result into temp[4][1]
		matrixCopy_Xby1(temp, tempVertex->coords, 4);					//copy back the matrix into the coordinate points
		tempVertex = tempVertex->next;									//move the pointer to the next vertex

	}while(tempVertex != firstVertex);

}

void Polygon::addVertex(Vertex v){//add a vertex to the polygon
	if(this->numPoints <= 0){									//if the polygon is empty
		this->firstVertex = new Vertex(v.getX(), v.getY());		//Make a new vertex and set it to firstVertex
		this->numPoints=1;
		this->firstVertex->next = this->firstVertex;			//Always be circularly linked
	}
	else{
		Vertex * temp = this->firstVertex;						//polygon isn't empty
		do{
			temp = temp->next;									//move to the end and add it there
		}while(temp->next != firstVertex);
		temp->next = new Vertex(v.getX(), v.getY());
		temp->next->next = this->firstVertex;					//always be circularly linked
		this->numPoints++;										//we have more points now, increment
	}
}
void Polygon::addVertex(double x, double y){			//same as above, only using x, and y doubles as inputs instead
	if(numPoints <= 0){
		this->firstVertex = new Vertex(x, y);
		this->numPoints=1;
		this->firstVertex->next = this->firstVertex;
	}
	else{
		Vertex * temp = this->firstVertex;
		do{
			temp = temp->next;
		}while(temp->next != firstVertex);
		temp->next = new Vertex(x,y);
		temp->next->next = this->firstVertex;
		this->numPoints++;
	}	
}
void Polygon::addVertex(double x, double y, double z){			//same as above, only using x, y, and z doubles as inputs instead
	if(numPoints <= 0){
		this->firstVertex = new Vertex(x, y, z);
		this->numPoints=1;
		this->firstVertex->next = this->firstVertex;
	}
	else{
		Vertex * temp = this->firstVertex;
		do{
			temp = temp->next;
		}while(temp->next != firstVertex);
		temp->next = new Vertex(x,y, z);
		temp->next->next = this->firstVertex;
		this->numPoints++;
	}	
}

Polygon::~Polygon(){				//kill all the pointers when polygon goes out of scope
	// printf("~polygon\n");
if(this->firstVertex==NULL)
	return;
Vertex * head = this->firstVertex;
do{
	// printf("%lu\n",head);
	Vertex * curr = head;
	head = head->next;
	delete curr;
}while(head!=firstVertex);
// printf("Done deconstructor\n");
}