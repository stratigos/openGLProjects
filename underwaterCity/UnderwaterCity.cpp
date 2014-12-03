/********************************************************
 *                                                      *
 *                UnderwaterCity.cpp                    *
 *                 Todd Morningstar                     *
 *                                                      *
 *                 This program creates                 *
 *                 a 3D model of a city                 *
 *                 deep under an ocean                  *
 *                                                      *
 ********************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include<GL\glut.h>
#include <iostream>
using namespace std;

double lookX = 50.0;
double lookY = 25.0;
double lookZ = 50.0;

float TIMEDELTA = 0.50;
long Time, ResetTime;
float up = 1.0;

float spotX = 10.0;
float spotY = 10.0;
float spotZ = 10.0;

GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {50.0, 40.0, 50.0, 0.0};

GLfloat diffuseB[] = {0.2, 0.0, 0.8, 1.0};
GLfloat ambientB[] = {0.2, 0.0, 0.8, 1.0};
GLfloat specularB[] = {1.0, 1.0, 1.0, 1.0};

GLfloat diffuseG[] = {0.9, 0.5, 0.0, 1.0};
GLfloat ambientG[] = {0.9, 0.5, 0.0, 1.0};
GLfloat specularG[] = {0.0, 0.0, 0.0, 1.0};

GLfloat g_ambient[] = {0.2, 0.2, 0.2, 0.0};


/*************************************
 *        initialize function        *
 *************************************/
void init (void)
{
	glClearColor (0.0, 0.8, 0.9, 0.0); // <- should make a seagreen color
    glEnable(GL_NORMALIZE);	
	glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

	//enable lighting factors
	glEnable(GL_LIGHTING);	

	//some light properties here
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//global lights
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,g_ambient);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

/*********************************************************
 * this drawCube() is the basis for the city's buildings *
 *********************************************************/
void drawCubeC(){   	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientB);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularB);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseB);

    //BOTTOM   
	glBegin(GL_POLYGON);
	  glVertex3f (0.0, 0.0, 0.0);
	  glVertex3f (1.0, 0.0, 0.0);
	  glVertex3f (1.0, 0.0, 1.0);
	  glVertex3f (0.0, 0.0, 1.0);
	glEnd();

	//TOP
	glBegin(GL_POLYGON);
	  glVertex3f (0.0, 1.0, 0.0);
	glNormal3f(0.0, 1.0, 1.0);
	  glVertex3f (0.0, 1.0, 1.0);
    glNormal3f(1.0, 1.0, 1.0);
	  glVertex3f (1.0, 1.0, 1.0);
	glNormal3f(1.0, 1.0, 0.0);
	  glVertex3f (1.0, 1.0, 0.0);
	glEnd();

	//LEFT
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 0.0);
      glVertex3f (0.0, 0.0, 0.0);
	  glVertex3f (0.0, 0.0, 1.0);
	  glVertex3f (0.0, 1.0, 1.0);
	  glVertex3f (0.0, 1.0, 0.0);
	glEnd();

	//RIGHT
	glBegin(GL_POLYGON);
	  glVertex3f (1.0, 0.0, 0.0);
	  glVertex3f (1.0, 1.0, 0.0);
	glNormal3f(1.0, 1.0, 1.0);
	  glVertex3f (1.0, 1.0, 1.0);
	  glVertex3f (1.0, 0.0, 1.0);
	glEnd();

	//FRONT
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	  glVertex3f (0.0, 0.0, 1.0);
	glNormal3f(1.0, 0.0, 1.0);
	  glVertex3f (1.0, 0.0, 1.0);
	glNormal3f(1.0, 1.0, 1.0);
	  glVertex3f (1.0, 1.0, 1.0);
	glNormal3f(0.0, 1.0, 1.0);
	  glVertex3f (0.0, 1.0, 1.0);
	glEnd();

	//BACK
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 0.0);
	  glVertex3f (0.0, 0.0, 0.0);
	  glVertex3f (0.0, 1.0, 0.0);
	  glVertex3f (1.0, 1.0, 0.0);
	  glVertex3f (1.0, 0.0, 0.0);
	glEnd();
}

/***********************************************
 *      drawSeaBed() makes the  floor of ocean *
 ***********************************************/
void drawSeaBed(){
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambientG);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specularG);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseG);

  glBegin(GL_POLYGON);
  glNormal3f(200.0, 0.0, 200.0);
	glVertex3f (-200.0, 0.0, -200.0);	
	glVertex3f (200.0, 0.0, -200.0);
    glVertex3f (200.0, 0.0, 200.0);	
  glNormal3f(200.0, 0.0, 200.0);
	glVertex3f (-200.0, 0.0, 200.0);
  glEnd();
}
  
/***************************************************************
 *      airBubble() uses above unitsquare to make tiny squares *
 ***************************************************************/
void airBubble() {
 GLfloat diffuseA[] = {0.8, 0.8, 0.8, 1.0};
 GLfloat ambientA[] = {0.2, 0.2, 0.2, 1.0};
 GLfloat specularA[] = {0.9, 0.5, 0.5, 1.0};

 glMaterialfv(GL_FRONT, GL_AMBIENT, ambientA);
 glMaterialfv(GL_FRONT, GL_SPECULAR, specularA);
 glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseA);

 glBegin(GL_POLYGON);
   glNormal3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.2, 0.0, 0.0);
	glVertex3f(0.2, 0.2, 0.0);
	glVertex3f(0.0, 0.2, 0.0);
 glEnd();
}

/*************************************
 *        group of airBubble()s      *
 *************************************/
void makeAirBubbles() {
	airBubble();
	glPushMatrix();
	  glTranslatef(0.5, 0.3, 0.0);
	  airBubble();
	glPopMatrix();
	glPushMatrix();
	  glTranslatef(0.0, 0.6, 0.0);
	  airBubble();
	glPopMatrix();
	glPushMatrix();
	  glTranslatef(0.4, 0.9, 0.0);
	  airBubble();
	glPopMatrix();
}

/*********************************************************
 *   notYellowSubmarine() is a cool sumbarine that looks *
 *       as though it has a spotlight to see the city    *
 *********************************************************/
void notYellowSubmarine() {
	glPushMatrix();
	 glScalef(10.0, 4.0, 4.0);
	 drawCubeC();
	glPopMatrix();
	glPushMatrix();
	 glTranslatef(5.0, 4.0, 2.0);
	 glScalef(1.0, 3.0, 1.0);
	 drawCubeC();
	glPopMatrix();
	glPushMatrix();
	  glTranslatef(4.0, 6.0, 2.0);
	  glScalef(1.0, 1.0, 1.0);
	  drawCubeC();
	glPopMatrix();
}


/*********************************************
 *        idle() function makes bubbles move *
 *********************************************/
void idle (void) {
	Time = clock();
	if (Time > ResetTime) {
		ResetTime = ResetTime + TIMEDELTA * CLOCKS_PER_SEC;
        up = up + 1.0;
		glutPostRedisplay();
	}
}

/*************************************
 *        reshape() function         *
 *************************************/
void reshape (int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -100.0, 100.0);
}


/**************************************
 *        display() function          *
 *      this display creates the city,*
 *      the sub, air bubbles, and the *
 *              spotlight             *
 **************************************/
void display (void)
{
	if (up > 12.0)
		up = 1.0;
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	gluLookAt(lookX, lookY, lookZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  //normal right view

	GLfloat lightS_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightS_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightS_position[] = {spotX, spotY, spotZ, 1.0};
    GLfloat lightS_direction[] = {0.0, 0.0, -1.0};
  
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, 90.0); 
	glLightf(GL_LIGHT1,GL_SPOT_EXPONENT, 2.0);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightS_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightS_direction);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightS_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightS_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, lightS_position);

	glPushMatrix();
	  glScalef(7.0, 25.0, 7.0);
	  drawCubeC();
	glPopMatrix();
	
	glPushMatrix();
	  glTranslatef(10.0, 0.0, 10.0);
	  glScalef(10.0, 20.0, 10.0);
	  drawCubeC();
	glPopMatrix();
	
	glPushMatrix();
	  glTranslatef(5.0, 0.0, 30.0);
	  glScalef(10.0, 30.0, 10.0);
	  drawCubeC();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(2.0, 0.0, 22.0);
	  glScalef(4.0, 11.0, 6.0);
	  drawCubeC();
	glPopMatrix();
	
	glPushMatrix();
	  glTranslatef(51.0, 0.0, 50.0);
	  glScalef(5.0, 3.5, 5.0);
	  drawCubeC();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(42.0, 0.0, 38.0);
	  glScalef(5.0, 5.0, 5.0);
	  drawCubeC();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(47.0, 0.0, 20.0);
	  glScalef(5.0, 5.0, 5.0);
	  drawCubeC();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(20.0, 0.0, 42.0);
	  glScalef(10.0, 5.0, 5.0);
	  drawCubeC();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(30.0, 0.0, 22.0);
	  glScalef(5.0, 5.0, 8.0);
	  drawCubeC();
	glPopMatrix();

    glPushMatrix();
	  glTranslatef(-30.0, 0.0, 22.0);
	  glScalef(5.0, 9.0, 8.0);
	  drawCubeC();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(-15.0, 0.0, 2.0);
	  glScalef(10.0, 10.0, 4.0);
	  drawCubeC();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(-42.0, 0.0, 19.0);
	  glScalef(5.0, 15.0, 5.0);
	  drawCubeC();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(-10.0, 0.0, 15.0);
	  glScalef(5.0, 5.0, 5.0);
	  drawCubeC();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(-15.0, 0.0, 25.0);
	  glScalef(2.0, 30.0, 2.0);
	  drawCubeC();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(10.0, 45.0, 10.0);
	  notYellowSubmarine();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(20.1, (up + 45.0), 13.0);
	  glScalef(3.0, 3.0, 0.0);
	  makeAirBubbles();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(40.0, up, 45.0);
	  glScalef(3.0, 3.0, 0.0);
	  makeAirBubbles();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(4.0, (up + 29.0), 27.0);
	  glScalef(3.0, 3.0, 0.0);
	  makeAirBubbles();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(-15.0, (up + 31.0), 25.0);
	  glScalef(3.0, 3.0, 0.0);
	  makeAirBubbles();
	glPopMatrix();

	drawSeaBed();

	glutSwapBuffers();
	glFlush();
}

/*************************************
 *        keyboard() function        *
 *           moves spotlight         *
 *************************************/
void keyboard(int key, int x, int y){
	if (key == GLUT_KEY_UP) {
		if (spotY > 50.0) {
			spotY = 49.0;
		}
		spotY = spotY + 1.0;
	}
	if (key == GLUT_KEY_DOWN) {
		if (spotY < 1.0) {
			spotY = 1.0;
		}
		spotY = spotY - 1.0;
	}
	if (key == GLUT_KEY_LEFT) {
		if (spotX < -25.0) {
			spotX = -24.0;
		}
		spotX = spotX - 1.0;
	}
	if (key == GLUT_KEY_RIGHT) {
		if (spotX < 25.0) {
			spotX = 24.0;
		}
		spotX = spotX + 1.0;
	}
	if (key == GLUT_KEY_PAGE_UP) {
		if (spotZ > 50.0) {
			spotZ = 49.0;
		}
		spotZ = spotZ + 1.0;
	}
	if (key == GLUT_KEY_PAGE_DOWN) {
		if (spotZ < -10.0) {
			spotZ = -9.0;
		}
		spotZ = spotZ - 1.0;
	}
	glutPostRedisplay();
}

/*************************************
 *        menu choice  function      *
 *************************************/
void choiceMain(int selection){
	if (selection == 1) {
		lookX = 50.0;
		lookY = 25.0;
		lookZ = 50.0;
	}
	if (selection == 2) {
		lookX = -50.0;
	}
	if (selection == 3) {
		lookX = -50.0;
		lookY = 40.0;
		lookZ = -30.0;
	}
	if (selection == 4) {
		glEnable(GL_LIGHT0);
	}
	if (selection == 5) {
		glDisable(GL_LIGHT0);
	}
	if (selection == 6) {
		float spotX = 10.0;
        float spotY = 10.0;
        float spotZ = 10.0;
		glEnable(GL_LIGHT1);
	}
	if (selection == 7) {
		glDisable(GL_LIGHT1);
	}
}

/*************************************
 *        main()   function          *
 *************************************/
int main (int argc, char** argv)
{
	cout << "USE KEYBOARD ARROW KEYS/PAGE UP OR DOWN TO MOVE THE SPOTLIGHT!\n";
	cout << "\n";
	cout << "RIGHT CLICK FOR A MENU\n";
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize (700, 700);
	glutInitWindowPosition (200, 100);
	glutCreateWindow (argv[0]);
	glutIdleFunc(idle);
	init ();

	  glutCreateMenu(choiceMain);
		glutAddMenuEntry("View from right side", 1);
		glutAddMenuEntry("View from left side", 2);
		glutAddMenuEntry("Top view from behind", 3);
		glutAddMenuEntry("Turn on ambient lighting", 4);
		glutAddMenuEntry("Turn off ambient lighting", 5);
		glutAddMenuEntry("Enable original spotlight", 6);
		glutAddMenuEntry("Turn off spotlight", 7);

		glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutCreateMenu(choiceMain);
	glutSpecialFunc(keyboard);
	glutDisplayFunc (display);
	glutReshapeFunc(reshape);
	Time = clock();
	ResetTime = Time + TIMEDELTA * CLOCKS_PER_SEC;
	glutMainLoop ();
	return 0;
}
