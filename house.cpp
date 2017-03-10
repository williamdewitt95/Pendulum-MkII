#include "house.h"




void drawFilledHouse(Polygon faces[6]){//Draw the house (with fill)
	int j;
	glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    for(j=0;j<6;j++){//House always has 7 sides

        // glColor3ub((j*45)% 255,//this gives a decent spread of colours, they are different enough from each other
        //           (j*25 +36)% 255,
        //           (j*-36 +100)% 255);

        glEnable(GL_TEXTURE_2D);
        glBegin(GL_POLYGON);
        glBindTexture(GL_TEXTURE_2D, GLOBAL.walls.texID);
        Vertex * temp = faces[j].firstVertex;
        // while(temp->next != faces[j].firstVertex){//go through vertices and add them - not a for loop because house could have pentagons on two sides
        //     glTexCoord3f();
        // 	glVertex3i(temp->getX(),
        // 			   temp->getY(),
        // 			   temp->getZ());
        // 	temp = temp->next;
        // }

        glTexCoord3f(0.0, 0.0, 0.0);//bottom left
        glVertex3i(temp->getX(),
                   temp->getY(),
                   temp->getZ());
        temp = temp->next;

        glTexCoord3f(0.0, 100.0, 0.0);
        glVertex3i(temp->getX(),
                   temp->getY(),
                   temp->getZ());
        temp = temp->next;

        glTexCoord3f(100.0, 100.0, 0.0);
        glVertex3i(temp->getX(),
                   temp->getY(),
                   temp->getZ());
        temp = temp->next;

        glTexCoord3f(100.0, 0.0, 0.0);
        glVertex3i(temp->getX(),
                   temp->getY(),
                   temp->getZ());


        // glVertex3i(temp->getX(),//add last vertex 
        // 		   temp->getY(),
        // 		   temp->getZ());

        glDisable(GL_TEXTURE_2D);
        glEnd();
    }
}



void rotateHouse(double rotX, double rotY, double rotZ, bool b){//rotate by angle for each axis
	glRotated(rotX, 1.0, 0.0, 0.0);
	glRotated(rotY, 0.0, 1.0, 0.0);
	glRotated(rotZ, 0.0, 0.0, 1.0);
	if(b) helloWorld();//putting the Hello World here ensures it is rotate properly

}

void defineHouse( Polygon *faces ){

    faces[0].addVertex(-100.0,-100.0,-010.0);//Bottom //bottom left
    faces[0].addVertex(-100.0, 100.0,-010.0);         //top left  
    faces[0].addVertex( 100.0, 100.0,-010.0);
    faces[0].addVertex( 100.0,-100.0,-010.0);

    faces[1].addVertex(-100.0,-100.0,-010.0);//Left
    faces[1].addVertex(-100.0,-100.0, 100.0);
    faces[1].addVertex( 100.0,-100.0, 100.0);
    faces[1].addVertex( 100.0,-100.0,-010.0);

    faces[2].addVertex(-100.0, 100.0,-010.0);//Right
    faces[2].addVertex(-100.0, 100.0, 100.0);
    faces[2].addVertex( 100.0, 100.0, 100.0);
    faces[2].addVertex( 100.0, 100.0,-010.0);	

    faces[3].addVertex(-100.0,-100.0,-010.0);//Back
    faces[3].addVertex(-100.0,-100.0, 100.0);
    faces[3].addVertex(-100.0, 100.0, 100.0);
    faces[3].addVertex(-100.0, 100.0,-010.0);

    faces[4].addVertex( 100.0,-100.0,-010.0);//Front
    faces[4].addVertex( 100.0,-100.0, 100.0);
    faces[4].addVertex( 100.0, 100.0, 100.0);
    faces[4].addVertex( 100.0, 100.0,-010.0);

    faces[5].addVertex(-100.0,-100.0, 100.0);//Top Left
    faces[5].addVertex(-100.0, 100.0, 100.0);
    faces[5].addVertex( 100.0, 100.0, 100.0);
    faces[5].addVertex( 100.0,-100.0, 100.0);
    /*
    faces[6].addVertex(-10.0, 10.0, 20.0);//Top Right
    faces[6].addVertex(-10.0, 00.0, 30.0);
    faces[6].addVertex( 10.0, 00.0, 30.0);
    faces[6].addVertex( 10.0, 10.0, 20.0);
    */
    // helloWorld();
    GLOBAL.walls.name = "test.raw";
    GLOBAL.walls.height=2;
    GLOBAL.walls.width=2;
    loadTextures(GLOBAL.walls);

}

void helloWorld(){//print Hello World on the roof
    void *font = GLUT_STROKE_ROMAN;

	glPushMatrix();
	char hw[] = "Hello World!"; 
	glTranslatef(0.75, 0.5, 2.51);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	// glRotatef(180.0, 0.0, 1.0, 0.0);
	glScalef(0.002,0.002,0.002);
	int len = (int) strlen(hw);
	for (int i = 0; i < len; i++) {
	    glutStrokeCharacter(font, hw[i]);
	}



	glPopMatrix();
}