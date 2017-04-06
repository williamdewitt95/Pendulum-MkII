#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

// These need to be global
int oldTime, currentTime;
float actualfps, fps = 0.0;


void showFPS()
{
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    char str_fps[15];
    if ( (currentTime - oldTime) > 1000 )     

    {
        actualfps = fps;
        fps = 0.0;
        oldTime = currentTime;
    }
    else
        fps++;
    sprintf(&str_fps[0], "FPS = %.0f",actualfps);


    glPushMatrix();
    glTranslatef(-3.5, -3.5, -0.5);
    drawString(&str_fps[0]);
    glPopMatrix();
}

