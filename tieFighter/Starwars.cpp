/********************************************************
 *                                                      *
 *               Wire Frame TIE Fighter					*
 *					Todd Morningstar                    *
 *														*
 *  			Program creates 4 viewports             *
 *            that display a wire frame space           *
 *            ship from the Star Wars universe          *
 ********************************************************/

/* NOTE: 1) A TIE fighter's "wings" are actually a hexagon
            shape, but this program displays them as a rectangle
		 2) Some Functions previously written by Dr. Mooney */

#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
using namespace std;

GLUquadricObj* quad;

int i = 0;
const int MAX_WING_LENGTH = 18;
float zVal = 0.0;

//used these values for the keyboard function
float EX = 0.0;
float WIE = 0.0;
float SSE = 0.0;
float offEX = 0.0;
float offWIE = 0.0;
float offSSE = 0.0;

float theta = 0.0;

/*************************************
 *               drawAxes            *
 *************************************/
void drawAxes (void){
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	  glVertex3f(0.0, 0.0, 0.0);
	  glVertex3f(4.0, 0.0, 0.0);
	  glVertex3f(0.0, 0.0, 0.0);
	  glVertex3f(0.0, 4.0, 0.0);
	  glVertex3f(0.0, 0.0, 0.0);
	  glVertex3f(0.0, 0.0, 4.0);
	glEnd();
	glRasterPos3f(2.1, 0.1, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'x');
	glRasterPos3f(0.1, 2.1, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'y');
	glRasterPos3f(0.1, 0.1, 2.0);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'z');
}

/*************************************
 *         draw pilot pod            *
 *************************************/
void drawPilotPod(){
	gluSphere(quad, 1.0, 32, 5);
}

/*************************************
 *          drawArm             *
 *************************************/
void drawArm(){
	gluCylinder(quad, 0.1, 0.1, 0.5, 4, 10);
}

/*************************************
 *          drawWireRect:            *
 *    I decided on making a wire     *
 *    rectangle of my own. Those     *
 *    provided did not coincide      *
 *    asthetically with the rest     *
 *        of my TIE fighter.         *
 *************************************/
void drawWireRect(){
	glBegin(GL_POLYGON);
	  glVertex3f(0.0, -2.25, 1.0);
	  glVertex3f(0.0, 2.25, 1.0);
	  glVertex3f(0.2, 2.25, 1.0);
	  glVertex3f(0.2, -2.25, 1.0);
	  glVertex3f(0.0, -2.25, 1.0);
	  glVertex3f(0.0, -2.25, 0.8);	  
	  glVertex3f(0.0, 2.25, 0.8);
	  glVertex3f(0.0, 2.25, 1.0);
	  glVertex3f(0.0, 2.25, 0.8);
	  glVertex3f(0.2, 2.25, 0.8);
	  glVertex3f(0.2, 2.25, 1.0);
	  glVertex3f(0.2, 2.25, 0.8);
	  glVertex3f(0.2, -2.25, 0.8);
	  glVertex3f(0.2, -2.25, 1.0);
	glEnd();
}

/*************************************
 *          drawWing                 *
 *************************************/
void drawWing(){
	zVal = 0.0;
	//this loop creates a bunch of 3d rects that form the wire wing
	for (i = 0; i < MAX_WING_LENGTH; ++i) {
		glPushMatrix();
		  glTranslatef(0.0, 0.0, zVal);
	      drawWireRect();
        glPopMatrix();
	zVal = zVal - 0.2;
	}
}

/*************************************
 *          drawTIEfighter           *
 *************************************/
void drawTIEfighter(){
	glPushMatrix();
	  glTranslatef(1.0, 0.0, 0.0);
	  drawPilotPod();
	glPopMatrix();
	
	//right 'Arm'
	glPushMatrix();
	  glTranslatef(1.95, 0.0, 0.0);
	  glRotatef(90.0, 0.0, 0.5, 0.0);
	  drawArm();
	glPopMatrix();

	//the left Arm
	glPushMatrix();
	  glTranslatef(-0.45, 0.0, 0.0);
	  glRotatef(90.0, 0.0, 0.5, 0.0);
	  drawArm();
	glPopMatrix(); 

	//the right Wing part
	glPushMatrix();
	  glTranslatef(2.42, 0.0, 0.8);
	  drawWing();
	glPopMatrix();
		
	//drawLeftWing();
	glPushMatrix();
	  glTranslatef(-0.63, 0.0, 0.8);
	  drawWing();
	glPopMatrix();
}

/*************************************
 *        keyboard function          *
 *************************************/
void keyboard(int key, int x, int y){
	if (key == GLUT_KEY_UP) {
		if(SSE < 1.0){
			SSE = 10.0;
		}
		SSE = SSE - 1.0;
	}
	if (key == GLUT_KEY_DOWN) {
		if(SSE > 11.0){
			SSE = 10.0;
		}
		SSE = SSE + 1.0;
	}
	if (key == GLUT_KEY_LEFT) {
		theta = theta + 2.0;
		if( theta > 178.0)
			theta = 0.0;
	}
	if (key == GLUT_KEY_RIGHT) {
		theta = theta - 2.0;
		if( theta < 2.0)
			theta = 180.0;
	}
	glutPostRedisplay();
}

/*************************************
 *               display             *
 *************************************/
void display (void){
	glClear (GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	offEX = EX + 10.0;
	offWIE = WIE + 10.0;
	offSSE = SSE + 10.0;

	//top view in upper left corner
	/* had some problems with this i couldnt fix - when u use any
	   keyboard func or do anything to the window, this one dissapears */
	gluLookAt(EX, offWIE, SSE, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	glViewport(20, 300, 250, 250);
	drawAxes();
	drawTIEfighter();
	
	//side elevation in top right corner
	glLoadIdentity();
	gluLookAt(offEX, WIE, SSE, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glViewport(300, 320, 250, 250);
	drawAxes();
	drawTIEfighter();

	//front elevation in bottom left corner
	glLoadIdentity();
	gluLookAt(EX, WIE, offSSE, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glViewport(20, 20, 250, 250);
	drawAxes();
	drawTIEfighter();
	
	//isometric view in bottom right corner
	glLoadIdentity();
	gluLookAt(offEX, offWIE, offSSE, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glViewport(290, 30, 270, 260);
	drawAxes();
	glPushMatrix();
	  glRotatef(theta, 0.0, 1.0, 0.0);
	  drawTIEfighter();
	glPopMatrix();
	
	glFlush ();
}

/*************************************
 *                init               *
 *************************************/
void init (void){
	glClearColor (1.0, 1.0, 1.0, 0.0);
	quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_LINE);
	gluQuadricOrientation(quad, GLU_OUTSIDE);

}

/*************************************
 *    reshape  w/static viewports    *
 *************************************/
void reshape (int w, int h){
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (-3.0, 3.0, -3.0, 3.0, 5.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*************************************
 *                main               *
 *************************************/
int main (int argc, char** argv){
	cout << "USE KEYBOARD ARROW KEYS TO MOVE THE TIE FIGHER \n";
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);
	init ();
	glutDisplayFunc (display);
	glutMainLoop ();
	return 0;
}
