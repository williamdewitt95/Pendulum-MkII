#include "house.h"




void drawFilledHouse(Polygon faces[6]){//Draw the house (with fill)

    int j;
    for(j=0;j<6;j++){//House always has 7 sides

        glColor3ub((j*45)% 255,//this gives a decent spread of colours, they are different enough from each other
                  (j*25 +36)% 255,
                  (j*-36 +100)% 255);

                faces[j].drawPolygon();


    }
    // printf("draw house\n");
}



void rotateHouse(double rotX, double rotY, double rotZ, bool b){//rotate by angle for each axis
	glRotated(rotX, 1.0, 0.0, 0.0);
	glRotated(rotY, 0.0, 1.0, 0.0);
	glRotated(rotZ, 0.0, 0.0, 1.0);
	// if(b) helloWorld();//putting the Hello World here ensures it is rotate properly

}

void defineHouse( Polygon *faces ){
    {
    faces[0].addVertex( 100.0,-100.0, 000.0);
    faces[0].addVertex( 100.0, 100.0, 000.0);
    faces[0].addVertex(-100.0, 100.0, 000.0);         //top left  
    faces[0].addVertex(-100.0,-100.0, 000.0);//Bottom //bottom left

    faces[0].setTexture(GLOBAL.floor);
    faces[0].addTextureVertex(0.0, 0.0, 0.0);
    faces[0].addTextureVertex(0.0, 100.0, 0.0);
    faces[0].addTextureVertex(100.0, 100.0, 0.0);
    faces[0].addTextureVertex(100.0, 0.0, 0.0);
    }

    {
    faces[1].addVertex( 100.0,-100.0, 000.0);
    faces[1].addVertex( 100.0,-100.0, 100.0);
    faces[1].addVertex(-100.0,-100.0, 100.0);
    faces[1].addVertex(-100.0,-100.0, 000.0);//Left

    faces[1].setTexture(GLOBAL.walls);
    faces[1].addTextureVertex(0.0, 0.0, 0.0);
    faces[1].addTextureVertex(0.0, 10.0, 0.0);
    faces[1].addTextureVertex(10.0, 10.0, 0.0);
    faces[1].addTextureVertex(10.0, 0.0, 0.0);
    }

    {
    faces[2].addVertex(-100.0, 100.0, 000.0);//Right
    faces[2].addVertex(-100.0, 100.0, 100.0);
    faces[2].addVertex( 100.0, 100.0, 100.0);
    faces[2].addVertex( 100.0, 100.0, 000.0);

    faces[2].setTexture(GLOBAL.walls);
    faces[2].addTextureVertex(0.0, 0.0, 0.0);
    faces[2].addTextureVertex(0.0, 10.0, 0.0);
    faces[2].addTextureVertex(10.0, 10.0, 0.0);
    faces[2].addTextureVertex(10.0, 0.0, 0.0);
    }   

    {
    faces[3].addVertex(-100.0, 100.0, 000.0);
    faces[3].addVertex(-100.0, 100.0, 100.0);
    faces[3].addVertex(-100.0,-100.0, 100.0);
    faces[3].addVertex(-100.0,-100.0, 000.0);//Back

    faces[3].setTexture(GLOBAL.walls);
    faces[3].addTextureVertex(0.0, 0.0, 0.0);
    faces[3].addTextureVertex(0.0, 10.0, 0.0);
    faces[3].addTextureVertex(10.0, 10.0, 0.0);
    faces[3].addTextureVertex(10.0, 0.0, 0.0);
    }

    {
    faces[4].addVertex( 100.0,-100.0, 000.0);//Front
    faces[4].addVertex( 100.0,-100.0, 100.0);
    faces[4].addVertex( 100.0, 100.0, 100.0);
    faces[4].addVertex( 100.0, 100.0, 000.0);

    faces[4].setTexture(GLOBAL.walls);
    faces[4].addTextureVertex(0.0, 0.0, 0.0);
    faces[4].addTextureVertex(0.0, 10.0, 0.0);
    faces[4].addTextureVertex(10.0, 10.0, 0.0);
    faces[4].addTextureVertex(10.0, 0.0, 0.0);
    }

    {
    faces[5].addVertex(-100.0,-100.0, 100.0);//Top
    faces[5].addVertex(-100.0, 100.0, 100.0);
    faces[5].addVertex( 100.0, 100.0, 100.0);
    faces[5].addVertex( 100.0,-100.0, 100.0);

    faces[5].setTexture(GLOBAL.ceiling);
    faces[5].addTextureVertex(0.0, 0.0, 0.0);
    faces[5].addTextureVertex(0.0, 10.0, 0.0);
    faces[5].addTextureVertex(10.0, 10.0, 0.0);
    faces[5].addTextureVertex(10.0, 0.0, 0.0);
    }
    /*
    faces[6].addVertex(-10.0, 10.0, 20.0);//Top Right
    faces[6].addVertex(-10.0, 00.0, 30.0);
    faces[6].addVertex( 10.0, 00.0, 30.0);
    faces[6].addVertex( 10.0, 10.0, 20.0);
    */
    // helloWorld();
    


}
