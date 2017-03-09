
#include "table.h"
#include "house.h"
#include "globals.h"

static int DRAWAXIS = 1;
static int DRAWSIGN = 1;
static bool DRAWFRAME = true;
static int currentView = 1;
static bool setCustom = true;;

float cameraX = 6.0;
float cameraY = 5.0;

double camMove_forward = 0;
double camMove_strafe = 0;
double camMove_vert = 0;
const double camMove_speed = 0.25 / 2.0;

//==================================================================================
using namespace std::chrono;

static int spinI = 0;
double ti=0.0;
// std::chrono::steady_clock::time_point t1 = steady_clock::now();
// std::chrono::steady_clock::time_point startTime = steady_clock::now();

bool stopped=false;

double initialRot=0;
int rotSpeed = 10;
double theta=initialRot*M_PI/180;
double omega=0;
static double penLength = .9938;  // Length of pendulum
static double grav = 9.80665;  // Normalized gravitational constant
static double b_FrictionConstant = 0.10;  // Frictional damping constant
static double mass = 1.00;  // Mass in normalized gravitational units
static double amplitudeOfDrivingForce = 0.00;  // Amplitude of initial driving force
static double freqOfDrivingForce = 0.00;  // Frequency parameter of initial driving force

// These two functions are the first and second derivative equations
// for the dynamical motion of the driven plane pendulum with damping

double thetadot(double t, double theta, double omega)
{
   return omega;
}

double omegadot(double t, double theta, double omega)
{
   // static double R = 1.00;  // Length of pendulum
   // static double g = 1.00;  // Normalized gravitational constant
   // static double b = 0.00;  // Frictional damping constant
   // static double m = 1.00;  // Mass in normalized gravitational units
   // static double A = 0.00;  // Amplitude of initial driving force
   // static double k = 0.00;  // Frequency parameter of initial driving force

   double drag, kick, denom;

   // denom = mass*pow(length,2.0);
   denom = mass*penLength*penLength;
   drag = -b_FrictionConstant*omega / denom; 
   kick =  amplitudeOfDrivingForce*cos(freqOfDrivingForce*t) / denom;

   return -grav/penLength*sin(theta)+drag+kick;
}




void step(double &t, double &theta, double &omega, int Nstep )
{
  // Time step variables
  double dt, h; 
  // variables for fourth-order Runge-Kutta method
  double k1, k2, k3, k4, j1, j2, j3, j4;
  int i; 

  h=100.0/Nstep;   // Try changing the value of Nstep above to see what happens 

      // Fourth-Order Runge-Kutta propagation step for second order dynamical systems
        k1 = thetadot(t,theta, omega); 
        j1 = omegadot(t,theta, omega); 
        k2 = thetadot(t+h/2, theta+h/2*k1, omega+h/2*j1); 
        j2 = omegadot(t+h/2, theta+h/2*k1, omega+h/2*j1); 
        k3 = thetadot(t+h/2, theta+h/2*k2, omega+h/2*j2); 
        j3 = omegadot(t+h/2, theta+h/2*k2, omega+h/2*j2); 
        k4 = thetadot(t+h, theta+h*k3, omega+h*j3); 
        j4 = omegadot(t+h, theta+h*k3, omega+h*j3); 
        theta = theta + h/6*(k1+2*k2+2*k3+k4);
        omega = omega + h/6*(j1+2*j2+2*j3+j4);
        t = t + h;
}



//==================================================================================



#define Nstep 100000



const int WINDOW_POSITION_X = 0;
const int WINDOW_POSITION_Y = 0;
int WINDOW_MAX_X = 500;
int WINDOW_MAX_Y = 500;

double SCALABLE_WINDOW_MAX_X = WINDOW_MAX_X;
double SCALABLE_WINDOW_MAX_Y = WINDOW_MAX_Y;

// Specify the coordinate ranges for the world coordinates in the 2D Frame

const double WORLD_COORDINATE_MIN_X = 000.0;
double WORLD_COORDINATE_MAX_X = 500.0;
const double WORLD_COORDINATE_MIN_Y = 000.0;
double WORLD_COORDINATE_MAX_Y = 500.0;

double scale_x = 1.0;
double scale_y = 1.0;




double currentRotX = 0.0;
double currentRotY = 0.0;
double currentRotZ = 0.0;
double rotSpeedX = 0.0;
double rotSpeedY = 0.0;
double rotSpeedZ = 0.0;


void init(void) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void idle(){
    GLOBAL.CAMERA_POS.z += camMove_vert;
    GLOBAL.CAMERA_POS.x += camMove_forward * cos(GLOBAL.CAMERA_ANGLE_HORIZONTAL*M_PI/180.0);
    GLOBAL.CAMERA_POS.y += camMove_forward * -sin(GLOBAL.CAMERA_ANGLE_HORIZONTAL*M_PI/180.0);

    GLOBAL.CAMERA_POS.x += camMove_strafe * sin(GLOBAL.CAMERA_ANGLE_HORIZONTAL*M_PI/180.0);
    GLOBAL.CAMERA_POS.y += camMove_strafe * cos(GLOBAL.CAMERA_ANGLE_HORIZONTAL*M_PI/180.0);
}



void drawAxes(int length)
{   
    int i, len;

    // Set up some character arrays for axis labels
    char xaxis[] = "X"; 
    char yaxis[] = "Y";
    char zaxis[] = "Z";

    // Select the Stroke font we want to use
    void *font = GLUT_STROKE_ROMAN;

    // This provides a coordinate axis about the origin. 
    glPointSize(1.0);
    glColor3f(1.0,0.0,0.0);

    glBegin(GL_LINES);
    glVertex3i(0,length,0);
    glVertex3i(0,-length,0);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex3i(length,0,0);
    glVertex3i(-length,0,0);
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
    glVertex3i(0,0,length);
    glVertex3i(0,0,-length);
    glEnd();
    glColor3f(1.0,1.0,1.0);

    // And now we  add some lettering.

    // Z - Label
    glPushMatrix();
    glTranslatef(-0.2, 0.2, 4);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(0.002,0.002,0.002);
    len = (int) strlen(zaxis);
    for (i = 0; i < len; i++) {
        glutStrokeCharacter(font, zaxis[i]);
    }
    glPopMatrix();

    // Y - Label
    glPushMatrix();
    glTranslatef(0.0, 4, -.4);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(0.002,0.002,0.002);
    len = (int) strlen(yaxis);
    for (i = 0; i < len; i++) {
        glutStrokeCharacter(font, yaxis[i]);
    }
    glPopMatrix();

    // X - Label 
    glPushMatrix();
    glTranslatef(4.0, 0.0, -.4);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.002,0.002,0.002);
    len = (int) strlen(xaxis);
    for (i = 0; i < len; i++) {
        glutStrokeCharacter(font, xaxis[i]);
    }

    glPopMatrix();
}


void look(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspect = (GLOBAL.WINDOW_MAX_X/(double)GLOBAL.WINDOW_MAX_Y);

    gluPerspective(90,aspect,0.1,1000);
    {
        double temp[3]={
            GLOBAL.CAMERA_POS.x + GLOBAL.CAMERA_LOOK_VECTOR.x,
            GLOBAL.CAMERA_POS.y + GLOBAL.CAMERA_LOOK_VECTOR.y,
            GLOBAL.CAMERA_POS.z + GLOBAL.CAMERA_LOOK_VECTOR.z
        };
        gluLookAt(
                GLOBAL.CAMERA_POS.x,GLOBAL.CAMERA_POS.y,GLOBAL.CAMERA_POS.z,
                temp[0],temp[1],temp[2],
                0,0,1
                );
    }
    // glMatrixMode(GL_MODELVIEW)

}

void display(void){

    Polygon faces[6];

    Polygon tableTop[6];
    Polygon tableLegs[4];
    look();//sets view

    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();             /* clear the matrix */
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // reportView();//Places text informing user of current view

    if (DRAWAXIS) drawAxes(10);//large axis is better
    defineHouse(faces);
    drawFilledHouse(faces);
    
    defineTableTop(tableTop);
    drawFilledTableTop(tableTop);

    defineTableLeg(tableLegs);
    drawFourLegs(tableLegs);
  
    // glFlush();
    glutSwapBuffers();
    glutPostRedisplay();//Marks display to draw again

}




void onAxis(int msg)//View the axis or no
{
    switch (msg) {
        case 1:
            DRAWAXIS = 1; 
            break;
        case 2:
            DRAWAXIS = 0; 
            break;
    }
    glutPostRedisplay();
}


void doNothing(int msg)
{
}



void reshape (int w, int h)//resize
{

    WORLD_COORDINATE_MAX_X += w - WINDOW_MAX_X;
    WORLD_COORDINATE_MAX_Y += h - WINDOW_MAX_Y;

    SCALABLE_WINDOW_MAX_X = w;
    SCALABLE_WINDOW_MAX_Y = h;


    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    glutPostRedisplay();
}

void moveCam(){
    if(camMove_forward > camMove_speed)
        camMove_forward = camMove_speed;
    if(camMove_forward < -1 * camMove_speed)
        camMove_forward = -1 * camMove_speed;

    if(camMove_strafe > camMove_speed)
        camMove_strafe = camMove_speed;
    if(camMove_strafe < -1 * camMove_speed)
        camMove_strafe = -1 * camMove_speed;

    if(camMove_vert > camMove_speed)
        camMove_vert = camMove_speed;
    if(camMove_vert < -1 * camMove_speed)
        camMove_vert = -1 * camMove_speed;
}



void keyboard( unsigned char key, int x, int y )
{ 
  if(key == 'q' || key == 'Q'){
        exit(0);
    }else if(key == 'w' || key == 'W'){
        camMove_forward += camMove_speed;
    }else if(key == 's' || key == 'S'){
        camMove_forward -= camMove_speed;
    }else if(key == 'a' || key == 'A'){
        camMove_strafe += camMove_speed;
    }else if(key == 'd' || key == 'D'){
        camMove_strafe -= camMove_speed;
    }else if(key == 'c' || key == 'C'){
        camMove_vert += camMove_speed;
    }else if(key == ' '){
        camMove_vert -= camMove_speed;
    }

  
}

void keyboardUp(unsigned char key, int x, int y){
    if(key == 'q' || key == 'Q'){
        exit(0);
    }else if(key == 'w' || key == 'W'){
        camMove_forward -= camMove_speed;
    }else if(key == 's' || key == 'S'){
        camMove_forward += camMove_speed;
    }else if(key == 'a' || key == 'A'){
        camMove_strafe -= camMove_speed;
    }else if(key == 'd' || key == 'D'){
        camMove_strafe += camMove_speed;
    }else if(key == 'c' || key == 'C'){
        camMove_vert -= camMove_speed;
    }else if(key == ' '){
        camMove_vert += camMove_speed;
    }

}



void changeRotSpeed(int x, int y, bool b){
     if(x < WORLD_COORDINATE_MAX_X && x > 0 && y < WORLD_COORDINATE_MAX_Y && y>0){//inside viewport
        if(b){//Increase
            if( ((y < x * WORLD_COORDINATE_MAX_Y/WORLD_COORDINATE_MAX_X && x < WORLD_COORDINATE_MAX_X / 2.0) 
                || (x > WORLD_COORDINATE_MAX_X / 2.0 && y < WORLD_COORDINATE_MAX_Y  - 1.0*x*WORLD_COORDINATE_MAX_Y/WORLD_COORDINATE_MAX_X))  && rotSpeedZ < 10.0){
                rotSpeedZ += 1;
            }
            else if(x < WORLD_COORDINATE_MAX_X / 2.0 && rotSpeedY < 10.0){
                rotSpeedY += 1;
            }
            else if(rotSpeedX < 10.0){
                rotSpeedX += 1;

            }
        }
        else{//decrease
            if( ((y < x * WORLD_COORDINATE_MAX_Y/WORLD_COORDINATE_MAX_X && x < WORLD_COORDINATE_MAX_X / 2.0) 
                || (x > WORLD_COORDINATE_MAX_X / 2.0 && y < WORLD_COORDINATE_MAX_Y  - 1.0*x*WORLD_COORDINATE_MAX_Y/WORLD_COORDINATE_MAX_X))  && rotSpeedZ < 10.0){
                rotSpeedZ -= 1;
            }
            else if(x < WORLD_COORDINATE_MAX_X / 2.0 && rotSpeedY < 10.0){
                rotSpeedY -= 1;
            }
            else if(rotSpeedX < 10.0){
                rotSpeedX -= 1;

            }
        }
    }
    
}




void keyboardButtons_special(int key,int x,int y){
    if(key == GLUT_KEY_PAGE_UP){//zoom in
        cameraX--;
        cameraY--;
    }
    else if(key == GLUT_KEY_PAGE_DOWN){//zoom out
        cameraX++;
        cameraY++;
    }
    else{
        printf("Unknown Key Down %d\n",key);
    }
}

void passiveMouseMovement(int x, int y){
    cameraMovement(x,y);
}

void mouse( int button, int state, int x, int y ){

    typedef GLfloat point[2];     
    point p;
    
    p[0]=x;
    p[1]=SCALABLE_WINDOW_MAX_Y-y;
 
    p[0] *= (WORLD_COORDINATE_MAX_X - WORLD_COORDINATE_MIN_X) / (double)SCALABLE_WINDOW_MAX_X ;
    p[0] +=  WORLD_COORDINATE_MIN_X;

    p[1] *= (WORLD_COORDINATE_MAX_Y-WORLD_COORDINATE_MIN_Y) / (double)SCALABLE_WINDOW_MAX_Y;
    p[1] += WORLD_COORDINATE_MIN_Y;
 

  if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {//inside viewport + right mb = decrease rotation speed (max of 10)
        changeRotSpeed(p[0], p[1], false);
     }


  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {//inside viewport + left mb  = increase rotation speed (max of 10)
      changeRotSpeed(p[0], p[1], true);
  }
}

int main(int argc, char** argv){

    int menu, axis, view, sign, fill;

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (SCALABLE_WINDOW_MAX_X, SCALABLE_WINDOW_MAX_Y); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display); 
    glutReshapeFunc(windowResize);

    glutKeyboardFunc(keyboard); /* Define Keyboard Handler */
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(keyboardButtons_special);//Define special keys handler
    glutMouseFunc(mouse);//Define mouse handler
    glutPassiveMotionFunc(passiveMouseMovement);
    glutIdleFunc(idle);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);

    // Turn on or off axes //
    axis = glutCreateMenu(onAxis);
    glutAddMenuEntry("On", 1);
    glutAddMenuEntry("Off", 2);


    //Create the menu 
    menu = glutCreateMenu(doNothing);
    glutAddSubMenu("Axes", axis);
  


    glutAttachMenu(GLUT_MIDDLE_BUTTON);


    glutMainLoop();
    return 0;
}
