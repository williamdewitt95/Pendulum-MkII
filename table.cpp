

#include "table.h"

void drawFilledTableTop(Polygon faces[6]){//Draw the house (with fill)
	int j;
	glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    for(j=0;j<6;j++){//Table top always has 6 sides

        // glColor3ub((j*25+36)% 255,//this gives a decent spread of colours, they are different enough from each other
        //           (j*45)% 255,
        //           (j*-36 +100)% 255);
    	// glColor3ub(102, 51 , 0);

     //    glBegin(GL_POLYGON);
       
     //    Vertex * temp = faces[j].firstVertex;
     //    while(temp->next != faces[j].firstVertex){//go through vertices and add them - not a for loop because house could have pentagons on two sides
     //    	glVertex3i(temp->getX(),
     //    			   temp->getY(),
     //    			   temp->getZ());
     //    	temp = temp->next;
     //    }

     //    glVertex3i(temp->getX(),//add last vertex
     //    		   temp->getY(),
     //    		   temp->getZ());

     //    glEnd();
        faces[j].drawPolygon();
    }
}



void rotateTableTop(double rotX, double rotY, double rotZ){//rotate by angle for each axis
	glRotated(rotX, 1.0, 0.0, 0.0);
	glRotated(rotY, 0.0, 1.0, 0.0);
	glRotated(rotZ, 0.0, 0.0, 1.0);

}

void defineTableTop(Polygon * tableFaces){
    {
    tableFaces[0].addVertex(-10.0,-10.0, 09.00);//Bottom
    tableFaces[0].addVertex(-10.0, 10.0, 09.00);
    tableFaces[0].addVertex( 10.0, 10.0, 09.00);
    tableFaces[0].addVertex( 10.0,-10.0, 09.00);

    tableFaces[0].setTexture(GLOBAL.table);
    tableFaces[0].addTextureVertex(0.0, 0.0, 0.0);
    tableFaces[0].addTextureVertex(0.0, 10.0, 0.0);
    tableFaces[0].addTextureVertex(10.0, 10.0, 0.0);
    tableFaces[0].addTextureVertex(10.0, 0.0, 0.0);
    }

    {
    tableFaces[1].addVertex(-10.0,-10.0, 09.00);//Left
    tableFaces[1].addVertex(-10.0,-10.0, 10.00);
    tableFaces[1].addVertex( 10.0,-10.0, 10.00);
    tableFaces[1].addVertex( 10.0,-10.0, 09.00);

    tableFaces[1].setTexture(GLOBAL.table);
    tableFaces[1].addTextureVertex(0.0, 0.0, 0.0);
    tableFaces[1].addTextureVertex(0.0, 0.75, 0.0);
    tableFaces[1].addTextureVertex(10.0, 0.75, 0.0);
    tableFaces[1].addTextureVertex(10.0, 0.0, 0.0);
    }

    {
    tableFaces[2].addVertex(-10.0, 10.0, 09.00);//Right
    tableFaces[2].addVertex(-10.0, 10.0, 10.00);
    tableFaces[2].addVertex( 10.0, 10.0, 10.00);
    tableFaces[2].addVertex( 10.0, 10.0, 09.00);
    
    tableFaces[2].setTexture(GLOBAL.table);
    tableFaces[2].addTextureVertex(0.0, 0.0, 0.0);
    tableFaces[2].addTextureVertex(0.0, 0.75, 0.0);
    tableFaces[2].addTextureVertex(10.0, 0.75, 0.0);
    tableFaces[2].addTextureVertex(10.0, 0.0, 0.0);
    }

    {
    tableFaces[3].addVertex(-10.0,-10.0, 09.00);//Back
    tableFaces[3].addVertex(-10.0,-10.0, 10.00);
    tableFaces[3].addVertex(-10.0, 10.0, 10.00);
    tableFaces[3].addVertex(-10.0, 10.0, 09.00);

    tableFaces[3].setTexture(GLOBAL.table);
    tableFaces[3].addTextureVertex(0.0, 0.0, 0.0);
    tableFaces[3].addTextureVertex(0.0, 0.75, 0.0);
    tableFaces[3].addTextureVertex(10.0, 0.75, 0.0);
    tableFaces[3].addTextureVertex(10.0, 0.0, 0.0);
    }

    {
    tableFaces[4].addVertex( 10.0,-10.0, 09.00);//Front
    tableFaces[4].addVertex( 10.0,-10.0, 10.00);
    tableFaces[4].addVertex( 10.0, 10.0, 10.00);
    tableFaces[4].addVertex( 10.0, 10.0, 09.00);

    tableFaces[4].setTexture(GLOBAL.table);
    tableFaces[4].addTextureVertex(0.0, 0.0, 0.0);
    tableFaces[4].addTextureVertex(0.0, 0.75, 0.0);
    tableFaces[4].addTextureVertex(10.0, 0.75, 0.0);
    tableFaces[4].addTextureVertex(10.0, 0.0, 0.0);
    }

    {
    tableFaces[5].addVertex(-10.0,-10.0, 10.00);//Top
    tableFaces[5].addVertex(-10.0, 10.0, 10.00);
    tableFaces[5].addVertex( 10.0, 10.0, 10.00);
    tableFaces[5].addVertex( 10.0,-10.0, 10.00);

    tableFaces[5].setTexture(GLOBAL.table);
    tableFaces[5].addTextureVertex(0.0, 0.0, 0.0);
    tableFaces[5].addTextureVertex(0.0, 10.0, 0.0);
    tableFaces[5].addTextureVertex(10.0, 10.0, 0.0);
    tableFaces[5].addTextureVertex(10.0, 0.0, 0.0);
    }

}

void drawFilledTableLeg(Polygon faces[4]){//Draw the house (with fill)
	int j;
	glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    for(j=0;j<4;j++){//Table leg always has sides

        // glColor3ub(0,255,0);

        // glBegin(GL_POLYGON);
       
        // Vertex * temp = faces[j].firstVertex;
        // while(temp->next != faces[j].firstVertex){//go through vertices and add them - not a for loop because house could have pentagons on two sides
        // 	glVertex3i(temp->getX(),
        // 			   temp->getY(),
        // 			   temp->getZ());
        // 	temp = temp->next;
        // }

        // glVertex3i(temp->getX(),//add last vertex
        // 		   temp->getY(),
        // 		   temp->getZ());

        // glEnd();
        faces[j].drawPolygon();
    }
}



void rotateTableLeg(double rotX, double rotY, double rotZ){//rotate by angle for each axis
	glRotated(rotX, 1.0, 0.0, 0.0);
	glRotated(rotY, 0.0, 1.0, 0.0);
	glRotated(rotZ, 0.0, 0.0, 1.0);

}


void defineTableLeg(Polygon *faces){
  
    {
    faces[0].addVertex(-01.0,-01.0, 00.0);//Left
    faces[0].addVertex(-01.0,-01.0, 09.0);
    faces[0].addVertex( 01.0,-01.0, 09.0);
    faces[0].addVertex( 01.0,-01.0, 00.0);

    faces[0].setTexture(GLOBAL.table);
    faces[0].addTextureVertex(10.0, 00.0, 00.0);
    faces[0].addTextureVertex(00.0, 00.0, 00.0);
    faces[0].addTextureVertex(00.0, 01.1, 00.0);
    faces[0].addTextureVertex(10.0, 01.1, 00.0);
    }

    {
    faces[1].addVertex(-01.0, 01.0, 00.0);//Right
    faces[1].addVertex(-01.0, 01.0, 09.0);
    faces[1].addVertex( 01.0, 01.0, 09.0);
    faces[1].addVertex( 01.0, 01.0, 00.0);  

    faces[1].setTexture(GLOBAL.table);
    faces[1].addTextureVertex(10.0, 00.0, 0.0);
    faces[1].addTextureVertex(00.0, 00.0, 0.0);
    faces[1].addTextureVertex(00.0, 01.0, 0.0);
    faces[1].addTextureVertex(10.0, 01.0, 0.0);
    }

    {
    faces[2].addVertex(-01.0,-01.0, 00.0);//Back
    faces[2].addVertex(-01.0,-01.0, 09.0);
    faces[2].addVertex(-01.0, 01.0, 09.0);
    faces[2].addVertex(-01.0, 01.0, 00.0);

    faces[2].setTexture(GLOBAL.table);
    faces[2].addTextureVertex(10.0, 00.0, 0.0);
    faces[2].addTextureVertex(00.0, 00.0, 0.0);
    faces[2].addTextureVertex(00.0, 0.75, 0.0);
    faces[2].addTextureVertex(10.0, 0.75, 0.0);
    }

    {
    faces[3].addVertex( 01.0,-01.0, 00.0);//Front
    faces[3].addVertex( 01.0,-01.0, 09.0);
    faces[3].addVertex( 01.0, 01.0, 09.0);
    faces[3].addVertex( 01.0, 01.0, 00.0);

    faces[3].setTexture(GLOBAL.table);
    faces[3].addTextureVertex(10.0, 00.0, 0.0);
    faces[3].addTextureVertex(00.0, 00.0, 0.0);
    faces[3].addTextureVertex(00.0, 1.25, 0.0);
    faces[3].addTextureVertex(10.0, 1.25, 0.0);
    }

}

void drawFourLegs(Polygon *face){
	glPushMatrix();

	glTranslated( 07.5, 07.5, 00.0);
	drawFilledTableLeg(face);

	glTranslated( 00.0,-15.0, 00.0);
	drawFilledTableLeg(face);

	glTranslated(-15.0, 00.0, 00.0);
	drawFilledTableLeg(face);

	glTranslated( 00.0, 15.0, 00.0);
	drawFilledTableLeg(face);

	glPopMatrix();

}


