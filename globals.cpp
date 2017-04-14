
#include "globals.h"

GLOBAL_SETTINGS::GLOBAL_SETTINGS(){
	WINDOW_MAX_X = 1000;
	WINDOW_MAX_Y = 1000;

	WORLD_COORDINATE_MIN_X = 0.0;
	WORLD_COORDINATE_MAX_X = 1000.0;
	WORLD_COORDINATE_MIN_Y = 0.0;
	WORLD_COORDINATE_MAX_Y = 1000.0;

	CAMERA_POS = {0,1,1};
	CAMERA_LOOK_VECTOR = {0,1,0};
	CAMERA_ANGLE_VERTICAL = 0;
	CAMERA_ANGLE_HORIZONTAL = 90;
}

GLOBAL_SETTINGS GLOBAL;


void windowResize(int width, int height){

	//move the world cordinates to match the change in the windows draw area
	GLOBAL.WORLD_COORDINATE_MIN_X += 0;
	GLOBAL.WORLD_COORDINATE_MAX_X += width - GLOBAL.WINDOW_MAX_X;
	GLOBAL.WORLD_COORDINATE_MIN_Y += 0;
	GLOBAL.WORLD_COORDINATE_MAX_Y += height - GLOBAL.WINDOW_MAX_Y;

	//remember what the new size of the window is
	GLOBAL.WINDOW_MAX_X = width;
	GLOBAL.WINDOW_MAX_Y = height;

	//make the scene visable over the whole window
	glViewport(0,0,width,height);
	glutPostRedisplay();
}

void scaleMouse(int &x, int &y){
	y=GLOBAL.WINDOW_MAX_Y-y;

	y*=(GLOBAL.WORLD_COORDINATE_MAX_Y - GLOBAL.WORLD_COORDINATE_MIN_Y) / ((double)GLOBAL.WINDOW_MAX_Y);
	x*=(GLOBAL.WORLD_COORDINATE_MAX_X - GLOBAL.WORLD_COORDINATE_MIN_X) / ((double)GLOBAL.WINDOW_MAX_X);

	y+=GLOBAL.WORLD_COORDINATE_MIN_Y;
	x+=GLOBAL.WORLD_COORDINATE_MIN_X;
}


void cameraMovement(int x, int y){//move the camera around not bound to the tank
	double movementDivisor = 6.0;
	//x and y are window cordinates
	//it is up to us to get deltas
	y=GLOBAL.WINDOW_MAX_Y-y;
	int midX = GLOBAL.WINDOW_MAX_X/2;
	int midY = GLOBAL.WINDOW_MAX_Y/2;

	int dx = x-midX;
	int dy = y-midY;
	

	double &angleH = GLOBAL.CAMERA_ANGLE_HORIZONTAL;
	double &angleV = GLOBAL.CAMERA_ANGLE_VERTICAL;
	angleH += dx/movementDivisor;
	if(angleH>360)angleH-=360;
	if(angleH<0)angleH+=360;
	angleV += dy/movementDivisor;
	if(angleV>90)angleV=90;
	if(angleV<-90)angleV=-90;

	// we will have a length of 5 for the line in the XY plane
	GLOBAL.CAMERA_LOOK_VECTOR.x = 5 * ( cos(angleH*M_PI/180.0));
	GLOBAL.CAMERA_LOOK_VECTOR.y = 5 * (-sin(angleH*M_PI/180.0));
	// make the z from pythagorean formula - our angle is measured from the horizontal plane
	GLOBAL.CAMERA_LOOK_VECTOR.z = 5 * tan(angleV*M_PI/180.0);

	if(dx==0 && dy==0)
		return; //we are not really doing anything, so we will simply ignore this thing


	glutWarpPointer(midX,GLOBAL.WINDOW_MAX_Y-midY);
}

void loadTextures(texture2D &texture){//we will read raw image files (the 2d array of pixels directly)
	   // printf("%d\n",texture.texID);

	 unsigned char *data;
     // FILE *file;
          // printf("\nloadTextures");

     // open texture data
 //     file = fopen(texture.name.c_str(), "rb");
 //    if (file == NULL){
 //    	printf("file == NULL\n");
 //    	return;
	// }
 //     // allocate buffer
 //     data = (unsigned char*) malloc(texture.width * texture.height * 3);

 //     if(data == NULL){
 //     	printf("\ndata null");
 //     	return;
 //     }

 //     // read texture data
 //     // int asdf = fread(data, texture.width * texture.height * 3, 1, file);
 //     fclose(file);
	data = SOIL_load_image(texture.name.c_str(), &texture.width, &texture.height, 0, SOIL_LOAD_RGB);



	GLuint textureID;
	glGenTextures(1, &textureID);//allocate texture

	glBindTexture(GL_TEXTURE_2D, textureID);//select texture as current

	// glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); // make the color of the polygons and the lighting affect the image

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//should wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//should wrap

	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glGenerateMipmap(GL_TEXTURE_2D);
	// gluBuild2DMipmaps(GL_TEXTURE_2D, 4,texture.width, texture.height, GL_RGB, GL_UNSIGNED_BYTE, data);

	// Black/white checkerboard
	// float pixels[] = {
	//     0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
	//     1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
	// };
	// texture.width = 2;
	// texture.height = 2;
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_FLOAT, pixels);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	texture.texID = textureID;//so we can reference it later
	glBindTexture(GL_TEXTURE_2D, 0);//reset
// 	float vertices[] = {
// //  Position      Color             Texcoords
//     -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
//      0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
//      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
//     -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
// 	};


    SOIL_free_image_data(data);



}


void initLight(){

	glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    glPushMatrix();
    glLoadIdentity();

 	GLfloat material_ambient[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat diffuseMaterial[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    // glMaterialf(GL_FRONT, GL_SHININESS, 25.0);





    GLfloat light_0_position[4] = 	{ -.01, 1.0, 0.0, 1.0 };
    GLfloat light_0_ambient[4] =	{ 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_0_diffuse[4] = 	{ 0.0, 1.0, 0.0, 1.0 };
    GLfloat light_0_specular[4] =	{ 1.0, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular);

    glEnable(GL_LIGHT0);




    GLfloat light_1_position[4] = 	{-1.0, 0.0, 1.0, 0.0 };
    GLfloat light_1_ambient[4] =	{ 0.0, 0.0, 1.0, 1.0 };
    GLfloat light_1_diffuse[4] = 	{ 1.0, 0.0, 0.0, 1.0 };
    GLfloat light_1_specular[4] =	{ 1.0, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT1, GL_POSITION, light_1_position);
	// glLightfv(GL_LIGHT1, GL_AMBIENT, light_1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_1_specular);

    // glEnable(GL_LIGHT1);





	GLfloat light_2_position[4] =  {  0.0,  0.0, 25.0, 1.0 };
	GLfloat light_2_ambient[4]  =  {  1.0,  1.0,  1.0, 1.0 };
	GLfloat light_2_diffuse[4]  =  {  0.1,  0.1,  0.1, 1.0 };
	GLfloat light_2_specular[4] =  {  1.0,  1.0,  1.0, 1.0 };
	GLfloat light_2_spot_direction[3] = { 0.0, 0.0,-1.0 };
	GLfloat light_2_spot_cutoff = 30.0;
	GLfloat light_2_spot_exponent = 2;//64
	GLfloat light_2_gl_linear_attenuation = .3;

	glLightfv(GL_LIGHT2, GL_POSITION, light_2_position);
	// glLightfv(GL_LIGHT2, GL_AMBIENT, light_2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_2_specular);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_2_spot_direction);
	glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, &light_2_spot_cutoff);
	glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, &light_2_spot_exponent);
	glLightfv(GL_LIGHT2, GL_LINEAR_ATTENUATION, &light_2_gl_linear_attenuation);
 

	// glEnable(GL_LIGHT2);




    // glColorMaterial(GL_FRONT, GL_DIFFUSE);
    // glEnable(GL_COLOR_MATERIAL);

    glPopMatrix();
}
