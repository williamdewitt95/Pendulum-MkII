

#include "table.h"

void drawFilledTableTop(Polygon faces[6]){//Draw the house (with fill)
	int j;
	glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    for(j=0;j<6;j++){//Table top always has 6 sides

        // glColor3ub((j*25+36)% 255,//this gives a decent spread of colours, they are different enough from each other
        //           (j*45)% 255,
        //           (j*-36 +100)% 255);
    	glColor3ub(255,0,0);

        glBegin(GL_POLYGON);
       
        Vertex * temp = faces[j].firstVertex;
        while(temp->next != faces[j].firstVertex){//go through vertices and add them - not a for loop because house could have pentagons on two sides
        	glVertex3i(temp->getX(),
        			   temp->getY(),
        			   temp->getZ());
        	temp = temp->next;
        }

        glVertex3i(temp->getX(),//add last vertex
        		   temp->getY(),
        		   temp->getZ());

        glEnd();
    }
}



void rotateTableTop(double rotX, double rotY, double rotZ){//rotate by angle for each axis
	glRotated(rotX, 1.0, 0.0, 0.0);
	glRotated(rotY, 0.0, 1.0, 0.0);
	glRotated(rotZ, 0.0, 0.0, 1.0);

}

void defineTableTop(Polygon * tableFaces){
    tableFaces[0].addVertex(-10.0,-10.0, 09.00);//Bottom
    tableFaces[0].addVertex(-10.0, 10.0, 09.00);
    tableFaces[0].addVertex( 10.0, 10.0, 09.00);
    tableFaces[0].addVertex( 10.0,-10.0, 09.00);

    tableFaces[1].addVertex(-10.0,-10.0, 09.00);//Left
    tableFaces[1].addVertex(-10.0,-10.0, 10.00);
    tableFaces[1].addVertex( 10.0,-10.0, 10.00);
    tableFaces[1].addVertex( 10.0,-10.0, 09.00);

    tableFaces[2].addVertex(-10.0, 10.0, 09.00);//Right
    tableFaces[2].addVertex(-10.0, 10.0, 10.00);
    tableFaces[2].addVertex( 10.0, 10.0, 10.00);
    tableFaces[2].addVertex( 10.0, 10.0, 09.00);  

    tableFaces[3].addVertex(-10.0,-10.0, 09.00);//Back
    tableFaces[3].addVertex(-10.0,-10.0, 10.00);
    tableFaces[3].addVertex(-10.0, 10.0, 10.00);
    tableFaces[3].addVertex(-10.0, 10.0, 09.00);

    tableFaces[4].addVertex( 10.0,-10.0, 09.00);//Front
    tableFaces[4].addVertex( 10.0,-10.0, 10.00);
    tableFaces[4].addVertex( 10.0, 10.0, 10.00);
    tableFaces[4].addVertex( 10.0, 10.0, 09.00);

    tableFaces[5].addVertex(-10.0,-10.0, 10.00);//Top
    tableFaces[5].addVertex(-10.0, 10.0, 10.00);
    tableFaces[5].addVertex( 10.0, 10.0, 10.00);
    tableFaces[5].addVertex( 10.0,-10.0, 10.00);
}

void drawFilledTableLeg(Polygon faces[4]){//Draw the house (with fill)
	int j;
	glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    for(j=0;j<4;j++){//Table leg always has sides

        glColor3ub(0,255,0);

        glBegin(GL_POLYGON);
       
        Vertex * temp = faces[j].firstVertex;
        while(temp->next != faces[j].firstVertex){//go through vertices and add them - not a for loop because house could have pentagons on two sides
        	glVertex3i(temp->getX(),
        			   temp->getY(),
        			   temp->getZ());
        	temp = temp->next;
        }

        glVertex3i(temp->getX(),//add last vertex
        		   temp->getY(),
        		   temp->getZ());

        glEnd();
    }
}



void rotateTableLeg(double rotX, double rotY, double rotZ){//rotate by angle for each axis
	glRotated(rotX, 1.0, 0.0, 0.0);
	glRotated(rotY, 0.0, 1.0, 0.0);
	glRotated(rotZ, 0.0, 0.0, 1.0);

}


void defineTableLeg(Polygon *legFaces){
  

    legFaces[0].addVertex(-01.0,-01.0, 00.0);//Left
    legFaces[0].addVertex(-01.0,-01.0, 09.0);
    legFaces[0].addVertex( 01.0,-01.0, 09.0);
    legFaces[0].addVertex( 01.0,-01.0, 00.0);

    legFaces[1].addVertex(-01.0, 01.0, 00.0);//Right
    legFaces[1].addVertex(-01.0, 01.0, 09.0);
    legFaces[1].addVertex( 01.0, 01.0, 09.0);
    legFaces[1].addVertex( 01.0, 01.0, 00.0);  

    legFaces[2].addVertex(-01.0,-01.0, 00.0);//Back
    legFaces[2].addVertex(-01.0,-01.0, 09.0);
    legFaces[2].addVertex(-01.0, 01.0, 09.0);
    legFaces[2].addVertex(-01.0, 01.0, 00.0);

    legFaces[3].addVertex( 01.0,-01.0, 00.0);//Front
    legFaces[3].addVertex( 01.0,-01.0, 09.0);
    legFaces[3].addVertex( 01.0, 01.0, 09.0);
    legFaces[3].addVertex( 01.0, 01.0, 00.0);

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


