#include "polygon.h"

    

Polygon::Polygon(){//where x,y is the center
	this->firstVertex = NULL;
	this->numPoints = 0;
	this->firstTextureVertex = NULL;
	this->texture2DExists = false;
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
	if(other.firstTextureVertex != NULL){
		this->firstTextureVertex = new Vertex(other.firstTextureVertex);
		this->texture = other.texture;
		this->texture2DExists=true;
	}
	else{
		this->firstTextureVertex = NULL;
		this->texture2DExists=false;
	}

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

void Polygon::drawPolygon(){
	if(numPoints<3) return;//cannot draw a Polygon if less than three sides

    glColor4ub(255,255,255,255);

	if(texture2DExists){
		glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->texture.texID);

    }

	Vertex normal;
	normal = this->getNormal();

    GLUtesselator * tess = gluNewTess();
    if(!tess) return;//tesselator failed somehow

    gluTessCallback(tess, GLU_TESS_BEGIN, (GLvoid (*)())  glBegin); //cast to void pointer //Not sure if GLVoid is needded or not, but GL seems to have problems whemn using normal types *sometimes*
    // gluTessCallback(tess, GLU_TESS_VERTEX, (GLvoid (*)()) glVertex3dv);
	gluTessCallback(tess, GLU_TESS_VERTEX_DATA, (GLvoid(*)())vertexCB);    
    gluTessCallback(tess, GLU_TESS_END, (GLvoid (*)()) glEnd);


   	gluTessBeginPolygon(tess, this);//start the polygon, then the contour, then actually throw the points at it
	gluTessBeginContour(tess);

	long count =0;
	Vertex * tempVertex = this->firstVertex;

	do{
		gluTessVertex(tess, (double *)tempVertex->coords, (void*)count);
		glNormal3d(normal.getX(), normal.getY(), normal.getZ());
        // printf("\n(%f, %f, %f)",normal.getX(), normal.getY(), normal.getZ());
		count++;

		tempVertex = tempVertex->next;
	}while(tempVertex->next != this->firstVertex);

	gluTessVertex(tess, (double *)tempVertex->coords, (void*)count);//do last one
  
    gluTessEndContour(tess);
    gluTessEndPolygon(tess);


    gluDeleteTess(tess);
        // glBegin(GL_POLYGON);
        // Vertex * temp = this->firstVertex;
        // Vertex * tempTex = this->firstTextureVertex;
        // while(temp->next != faces[j].firstVertex){//go through vertices and add them - not a for loop because house could have pentagons on two sides       
        // 	glVertex3i(temp->getX(),
        // 			   temp->getY(),
        // 			   temp->getZ());
        // 	glTexCoord3f(tempTex->getX(),tempTex->getY(),tempTex->getZ());
        // 	temp = temp->next;
        // 	tempTex = tempTex->next;
        // }
        // glVertex3i(temp->getX(),//add last vertex 
        // 		   temp->getY(),
        // 		   temp->getZ());
        // glTexCoord3f(tempTex->getX(),tempTex->getY(),tempTex->getZ());

        // glEnd();

  	if(texture2DExists){

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

	}
}

void Polygon::vertexCB(void* data, void *polygon_data){
	//data is simply the index of what point we're on
	//polygon_data is the polygon we're tesselating
	Polygon *poly = (Polygon*)polygon_data;
	if(poly==NULL){
		printf("poly is null\n");
		return;
	}
	
	Vertex * temp = poly->firstVertex;

	if(poly->texture2DExists && poly->firstTextureVertex != NULL){
		// printf("texture2DExists\n");

		Vertex * tempTex = poly->firstTextureVertex;
		for(long i=0;i<(long)data;i++){//go to the point the index asks for
			temp = temp->next;
			tempTex = tempTex->next;
		}
		// printf("data: %ld, tempTex x, y: %.1f, %.1f\ttemp x,y %.1f, %.1f\n",(long)data,tempTex->getX(), tempTex->getY(),temp->getX(), temp->getY());
		glTexCoord2f(tempTex->getX(),tempTex->getY());
	}
	else{
		// printf("texture no exist\n");
		for(long i=0;i<(long)data;i++){
			temp = temp->next;
		}
	}
	glVertex3dv((double*)&temp->coords);

}

void Polygon::setTexture(texture2D &newTex){
	this->texture = newTex;
	this->texture2DExists=true;
}


int Polygon::getNumPoints(){
	return this->numPoints;
}
Vertex Polygon::getNormal(){//returns a vertex that is the end of a vector between zero and vertex that is direction of normal
	double temp1[4][1];
	temp1[0][0] = this->firstVertex->next->getX() - this->firstVertex->getX();
	temp1[1][0] = this->firstVertex->next->getY() - this->firstVertex->getY();
	temp1[2][0] = this->firstVertex->next->getZ() - this->firstVertex->getZ();
	double temp2[4][1];
	temp2[0][0] = this->firstVertex->next->next->getX() - this->firstVertex->next->getX();
	temp2[1][0] = this->firstVertex->next->next->getY() - this->firstVertex->next->getY();
	temp2[2][0] = this->firstVertex->next->next->getZ() - this->firstVertex->next->getZ();
	Vertex normal;
	crossProd4by1(temp1, temp2, normal.coords);

	
	
	return normal;
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

void Polygon::addTextureVertex(double x, double y, double z){			//same as above, only using x, y, and z doubles as inputs instead
	if(this->firstTextureVertex == NULL){
		this->firstTextureVertex = new Vertex(x, y, z);
		// this->numPoints=1;
		this->firstTextureVertex->next = this->firstTextureVertex;
	}
	else{
		Vertex * temp = this->firstTextureVertex;
		do{
			temp = temp->next;
		}while(temp->next != firstTextureVertex);
		temp->next = new Vertex(x, y, z);
		temp->next->next = this->firstTextureVertex;
		// this->numPoints++;
	}	
}

Polygon::~Polygon(){				//kill all the pointers when polygon goes out of scope
	// printf("~polygon\n");
if(this->firstTextureVertex != NULL){
	Vertex * head = this->firstTextureVertex;
	do{
		Vertex * curr = head;
		head = head->next;
		delete curr;
	}while(head!=firstTextureVertex);
}
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