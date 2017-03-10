#include "pendulum.h"

void drawFilledPendulumHolder(Polygon faces[], int numFaces){//Draw the house (with fill)
	int j;
	glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    for(j=0;j<numFaces;j++){//Table top always has 6 sides

        glColor3ub((j*25+36)% 255,//this gives a decent spread of colours, they are different enough from each other
                  (j*45)% 255,
                  (j*-36 +100)% 255);
    	// glColor3ub(0,0,125);

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



void definePendulumHolder(Polygon * faces){
    
    faces[0].addVertex(-1.0,-1.0, 10.00);//Left
    faces[0].addVertex(-1.0,-1.0, 15.00);
    // faces[0].addVertex( 3.5,-1.0, 13.00);
    // faces[0].addVertex( 3.5,-1.0, 12.00);
    faces[0].addVertex( 1.0,-1.0, 14.00);
    faces[0].addVertex( 1.0,-1.0, 10.00);

    faces[1].addVertex(-1.0,-1.0, 15.00);    //Left2
    faces[1].addVertex( 5.5,-1.0, 15.00);
    faces[1].addVertex( 5.5,-1.0, 14.00);
    faces[1].addVertex( 1.0,-1.0, 14.00);
    

    faces[2].addVertex(-1.0, 1.0, 10.00);//Right
    faces[2].addVertex(-1.0, 1.0, 15.00);
    // faces[2].addVertex( 3.5, 1.0, 13.00);
    // faces[2].addVertex( 3.5, 1.0, 12.00);
    faces[2].addVertex( 1.0, 1.0, 14.00);
    faces[2].addVertex( 1.0, 1.0, 10.00);  
  
    faces[3].addVertex(-1.0, 1.0, 15.00);//Right2
    faces[3].addVertex( 5.5, 1.0, 15.00);
    faces[3].addVertex( 5.5, 1.0, 14.00);
    faces[3].addVertex( 1.0, 1.0, 14.00);
     
    faces[4].addVertex(-1.0,-1.0, 10.00);//Back
    faces[4].addVertex(-1.0,-1.0, 15.00);
    faces[4].addVertex(-1.0, 1.0, 15.00);
    faces[4].addVertex(-1.0, 1.0, 10.00);

    faces[5].addVertex( 1.0,-1.0, 10.00);//Front bottom
    faces[5].addVertex( 1.0,-1.0, 14.00);
    faces[5].addVertex( 1.0, 1.0, 14.00);
    faces[5].addVertex( 1.0, 1.0, 10.00);

    faces[6].addVertex(-1.0,-1.0, 15.00);//Top
    faces[6].addVertex(-1.0, 1.0, 15.00);
    faces[6].addVertex( 5.5, 1.0, 15.00);
    faces[6].addVertex( 5.5,-1.0, 15.00);

    faces[7].addVertex( 5.5,-1.0, 14.00);//Front top
    faces[7].addVertex( 5.5,-1.0, 15.00);
    faces[7].addVertex( 5.5, 1.0, 15.00);
    faces[7].addVertex( 5.5, 1.0, 14.00);

    faces[8].addVertex( 1.0,-1.0, 14.00);//Bottom
    faces[8].addVertex( 1.0, 1.0, 14.00);
    faces[8].addVertex( 5.5, 1.0, 14.00);
    faces[8].addVertex( 5.5,-1.0, 14.00);


}

void definePendulumStick( Polygon *faces ){
    double X=0.0;
    double Y=0.0;
    double Z=0.0;
    double pendWidth = 1.0;
    double pendLength = 8.0;
    double ballLength = 2.0;
    faces[0].addVertex(-pendWidth, -pendWidth, -pendLength);//Bottom
    faces[0].addVertex(-pendWidth,  pendWidth, -pendLength);
    faces[0].addVertex( pendWidth,  pendWidth, -pendLength);
    faces[0].addVertex( pendWidth, -pendWidth, -pendLength);

    faces[1].addVertex(-pendWidth, -pendWidth, -pendLength);//Left
    faces[1].addVertex(-pendWidth, -pendWidth, + 0.0      );
    faces[1].addVertex( pendWidth, -pendWidth, + 0.0      );
    faces[1].addVertex( pendWidth, -pendWidth, -pendLength);

    faces[2].addVertex(-pendWidth,  pendWidth, -pendLength);//Right
    faces[2].addVertex(-pendWidth,  pendWidth, + 0.0      );
    faces[2].addVertex( pendWidth,  pendWidth, + 0.0      );
    faces[2].addVertex( pendWidth,  pendWidth, -pendLength);   

    faces[3].addVertex(-pendWidth, -pendWidth, -pendLength);//Back
    faces[3].addVertex(-pendWidth, -pendWidth, + 0.0      );
    faces[3].addVertex(-pendWidth,  pendWidth, + 0.0      );
    faces[3].addVertex(-pendWidth,  pendWidth, -pendLength);

    faces[4].addVertex( pendWidth, -pendWidth, -pendLength);//Front
    faces[4].addVertex( pendWidth, -pendWidth, + 0.0      );
    faces[4].addVertex( pendWidth,  pendWidth, + 0.0      );
    faces[4].addVertex( pendWidth,  pendWidth, -pendLength);

    faces[5].addVertex(-pendWidth, -pendWidth, + 0.0      );//Top
    faces[5].addVertex(-pendWidth,  pendWidth, + 0.0      );
    faces[5].addVertex( pendWidth,  pendWidth, + 0.0      );
    faces[5].addVertex( pendWidth, -pendWidth, + 0.0      );






    faces[6].addVertex(-pendWidth, -pendWidth, -pendLength-ballLength);//Bottom
    faces[6].addVertex(-pendWidth,  pendWidth, -pendLength-ballLength);
    faces[6].addVertex( pendWidth,  pendWidth, -pendLength-ballLength);
    faces[6].addVertex( pendWidth, -pendWidth, -pendLength-ballLength);

    faces[7].addVertex(-pendWidth, -pendWidth, -pendLength-ballLength);//Left
    faces[7].addVertex(-pendWidth, -pendWidth, -pendLength+ 0.0       );
    faces[7].addVertex( pendWidth, -pendWidth, -pendLength+ 0.0       );
    faces[7].addVertex( pendWidth, -pendWidth, -pendLength-ballLength);

    faces[8].addVertex(-pendWidth,  pendWidth, -pendLength-ballLength);//Right
    faces[8].addVertex(-pendWidth,  pendWidth, -pendLength+ 0.0       );
    faces[8].addVertex( pendWidth,  pendWidth, -pendLength+ 0.0       );
    faces[8].addVertex( pendWidth,  pendWidth, -pendLength-ballLength);   

    faces[9].addVertex(-pendWidth, -pendWidth, -pendLength-ballLength);//Back
    faces[9].addVertex(-pendWidth, -pendWidth, -pendLength+ 0.0       );
    faces[9].addVertex(-pendWidth,  pendWidth, -pendLength+ 0.0       );
    faces[9].addVertex(-pendWidth,  pendWidth, -pendLength-ballLength);

    faces[10].addVertex( pendWidth, -pendWidth, -pendLength-ballLength);//Front
    faces[10].addVertex( pendWidth, -pendWidth, -pendLength+ 0.0       );
    faces[10].addVertex( pendWidth,  pendWidth, -pendLength+ 0.0       );
    faces[10].addVertex( pendWidth,  pendWidth, -pendLength-ballLength);

    faces[11].addVertex(-pendWidth, -pendWidth, -pendLength+ 0.0       );//Top
    faces[11].addVertex(-pendWidth,  pendWidth, -pendLength+ 0.0       );
    faces[11].addVertex( pendWidth,  pendWidth, -pendLength+ 0.0       );
    faces[11].addVertex( pendWidth, -pendWidth, -pendLength+ 0.0       );

}


void definePendulumBall( Polygon *faces ){
    double pendWidth = 1.0;
    double pendLength = 2.0;
    


}

void drawFilledPendulumStick(Polygon faces[], int numFaces){//Draw the house (with fill)
    int j;
    glPushMatrix();
    // glTranslated(4.5,0.0,14.0);
    glScaled(0.3,0.3,0.25);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    for(j=6;j<numFaces;j++){//Table top always has 6 sides

        // glColor3ub((j*25+36)% 255,//this gives a decent spread of colours, they are different enough from each other
        //           (j*45)% 255,
        //           (j*-36 +100)% 255);
        glColor3ub(255,255,125);

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
    glScaled(0.1,0.1,1.0);
    for(j=0;j<6;j++){//Table top always has 6 sides

        // glColor3ub((j*25+36)% 255,//this gives a decent spread of colours, they are different enough from each other
        //           (j*45)% 255,
        //           (j*-36 +100)% 255);
        glColor3ub(0,255,125);

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
    glPopMatrix();
}

void drawFilledPendulumBall(Polygon faces[], int numFaces){//Draw the house (with fill)
    int j;
    glPushMatrix();
    glScaled(0.3, 0.3, 0.3);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    for(j=0;j<numFaces;j++){//Table top always has 6 sides

        // glColor3ub((j*25+36)% 255,//this gives a decent spread of colours, they are different enough from each other
        //           (j*45)% 255,
        //           (j*-36 +100)% 255);
        glColor3ub(125,50,125);

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
    glPopMatrix();
}

void drawFilledPendulum(Polygon *stick, int numFacesStick,  double angle){
    glPushMatrix();
    glTranslated(4.5, 0.0, 14.0);
    glRotated(angle,1,0,0);
    drawFilledPendulumStick(stick, numFacesStick); 
    // drawFilledPendulumBall(ball, numFacesBall);

    glPopMatrix();

}



