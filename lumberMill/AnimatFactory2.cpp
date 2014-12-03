/********************************************************
 *                                                      *
 *              Animated Factory PART 2                 *
 *                 Todd Morningstar                     *
 *                                                      *
 *                 This program creates                 *
 *                a 2D image of a factory               *
 *                   with moving parts                  *
 *                                                      *
 ********************************************************/

/*some functions edited by Todd Morningstar,
originally written by Dr. Mooney */

#include <GL\glut.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <iostream>
using namespace std;

float TIMEDELTA = 0.50;
long Time, ResetTime;
static float slide = 0.0;	//change in position for translation of 'lumber'
float speed = 5.0;			//how fast conveyer belt moves lumber
static float spin = 0.0;	//angle that saw rotates at

void init (void){
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}

//draws a 'unit' square at the origin
void unitSquare (){
	glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.0);
		glVertex2f(1.0, 0.0);
		glVertex2f(1.0, 1.0);
		glVertex2f(0.0, 1.0);
	glEnd();
}

//draws a 'unit' equilateral triangle at the origin
void unitTriangle (){
	glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.0);
		glVertex2f(1.0, 0.0);
		glVertex2f(0.5, 0.866f);
	glEnd();
}

//bottom sawblade
void unitUpsideDownTriangle (){
	glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.0);
		glVertex2f(1.0, 0.0);
		glVertex2f(0.5, -0.866f);
	glEnd();
}

//right sawblade
void unitRightTriangle (){
	glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 1.0);
		glVertex2f(0.866f, 0.5);
	glEnd();
}

//left sawblade
void unitLeftTriangle (){
	glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 1.0);
		glVertex2f(-0.866f, 0.5);
	glEnd();
}

//big object at top of screen to make it look like a workshop
void nameDuct() {
	glPushMatrix();
	  glTranslatef(50.0, 350.0, 0.0);
	  glScalef(550.0, 70.0, 1.0);
	  glColor3f(1.0, 1.0, 1.0);
	  unitSquare();
	glPopMatrix();
}

//factory name spelled out on here, on the "top" of factory cross section
void textForNameDuct() {
	glColor3f(1.0,0.0,0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
		//"L"
		glVertex2i(180, 400);
		glVertex2i(180, 390);
		glVertex2i(180, 390);
		glVertex2i(185, 390);
		//"U"
		glVertex2i(195, 400);
		glVertex2i(195, 390);
		glVertex2i(200, 400);
		glVertex2i(200, 390);
		glVertex2i(200, 390);
		glVertex2i(195, 390);
		//"M"
		glVertex2i(210, 400);
		glVertex2i(210, 390);
		glVertex2i(210, 400);
		glVertex2i(212, 398);
		glVertex2i(212, 398);
		glVertex2i(215, 400);
		glVertex2i(215, 400);
		glVertex2i(215, 390);		
		//"B"
		glVertex2i(225, 400);
		glVertex2i(225, 390);
		glVertex2i(225, 400);
		glVertex2i(230, 400);
		glVertex2i(230, 400);
		glVertex2i(230, 395);
		glVertex2i(230, 395);
		glVertex2i(225, 395);
		glVertex2i(230, 395);
		glVertex2i(230, 390);
		glVertex2i(230, 390);
		glVertex2i(225, 390);
		//"E"
		glVertex2i(240, 400);
		glVertex2i(240, 390);
		glVertex2i(240, 400);
		glVertex2i(245, 400);
		glVertex2i(245, 395);
		glVertex2i(240, 395);
		glVertex2i(245, 390);
		glVertex2i(240, 390);
		//"R"
		glVertex2i(255, 400);
		glVertex2i(255, 390);
		glVertex2i(255, 400);
		glVertex2i(260, 400);
		glVertex2i(260, 400);
		glVertex2i(260, 395);
		glVertex2i(260, 395);
		glVertex2i(255, 395);
		glVertex2i(255, 396);
		glVertex2i(260, 390);
		//"C"
		glVertex2i(455, 400);
		glVertex2i(450, 395);
		glVertex2i(450, 395);
		glVertex2i(455, 390);
		//"O"
		glVertex2i(465, 400);
		glVertex2i(465, 390);
		glVertex2i(465, 400);
		glVertex2i(470, 400);
		glVertex2i(470, 400);
		glVertex2i(470, 390);
		glVertex2i(470, 390);
		glVertex2i(465, 390);
	glEnd();
}

//some box connected to the duct with the name on it
void factoryishMetalThing(){
	glPushMatrix();
	  glTranslatef(600.0, 320.0, 0.0);
	  glScalef(60.0, 130.0, 1.0);
	  glColor3f(1.0, 1.0, 1.0);
	  unitSquare();	  
	glPopMatrix();
}

//some pipeish object connecting ceiling equipment to bottom
void supplyDuct(){
	glPushMatrix();
	  glTranslatef(58.0, 120.0, 0.0);
	  glScalef(10.0, 280.0, 1.0);
	  glColor3f(1.0, 1.0, 1.0);
	  unitSquare();
	glPopMatrix();
}

/*box that conveyer belt comes out of, has buttons for speed
"bottom" of factory 2d cross section */
void conveyorBox(){
	glPushMatrix();
	  glTranslatef(15.0, 20.0, 0.0);
	  glScalef(100.0, 35.0, 1.0);
	  unitSquare();
	  glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
	glPushMatrix();
	  glTranslatef(15.0, 20.0, 0.0);
	  glScalef(90.0, 55.0, 1.0);
	  unitSquare();
	  glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
	  glPushMatrix();
	  glTranslatef(15.0, 75.0, 0.0);
	  glScalef(100.0, 65.0, 1.0);
	  unitSquare();
	  glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();

	//buttons
	//each are given their own seperate matrix due to
	//problems with the colors
	glPushMatrix();
	  glTranslatef(100.0, 105.0, 0.0);
	  glScalef(10.0, 10.0, 1.0);
	  glColor3f(1.0, 0.0, 0.0);
	  unitSquare();
	glPopMatrix();
	glPushMatrix();
	  glTranslatef(80.0, 105.0, 0.0);
	  glScalef(10.0, 10.0, 1.0);
	  glColor3f(0.0, 0.5, 0.0);
	  unitSquare();
	glPopMatrix();
	glPushMatrix();
	  glTranslatef(60.0, 105.0, 0.0);
	  glScalef(10.0, 10.0, 1.0);
	  glColor3f(0.0, 0.0, 0.5);
	  unitSquare();
	glPopMatrix();
}

//forward motion belt for lumber
void conveyorBelt(){
	glPushMatrix();
	  glTranslatef(105.0, 56.0, 0.0);
	  glScalef(540.0, 15.0, 1.0);
	  glColor3f(0.6, 0.5, 0.3);
	  unitSquare();
	glPopMatrix();
}

//after "sawed", lumber slides into some sort of collecting machine
void cutLumberCollector(){
	glPushMatrix();
	  glTranslatef(636.0, 20.0, 0.0);
	  glScalef(44.0, 125.0, 1.0);
	  glColor3f(1.0, 1.0, 1.0);
	  unitSquare();
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(620.0, 20.0, 0.0);
	  glScalef(31.0, 45.0, 1.0);
	  unitTriangle();
	glPopMatrix();
}

//mechanical arm attatched to saw
void sawbladeArm(){
	glColor3f(0.6, 0.5, 0.4);
	glLineWidth(3.0);
	glBegin(GL_LINES);
		glVertex2i(598.0, 125.0);
		glVertex2i(626.0, 171.0);        
	glEnd();

	glPushMatrix();
	  glTranslatef(621.0, 165.0, 0.0);
	  glScalef(10.0, 200.0, 1.0);
	  unitSquare();
	glPopMatrix();
} 

//the saw
void saw(){
	glPushMatrix();
	  glTranslatef(596.0, 125.0, 0.0);
	  glScalef(6.0, 40.0, 1.0);
	  glColor3f(0.0, 0.5, 0.5);
	  unitTriangle();
	glPopMatrix();
	glPushMatrix();
	  glTranslatef(596.0, 125.0, 0.0);
	  glScalef(6.0, 40.0, 1.0);
	  unitUpsideDownTriangle();
	glPopMatrix();
	glPushMatrix();
	  glTranslatef(596.0, 125.0, 0.0);
	  glScalef(40.0, 6.0, 1.0);
	  unitRightTriangle();
	glPopMatrix();
	glPushMatrix();
	  glTranslatef(596.0, 125.0, 0.0);
	  glScalef(40.0, 6.0, 1.0);
	  unitLeftTriangle();
	glPopMatrix();
}

//method below called to get value for saw rotation
void spinSaw(){
	spin = spin + 5.0;
	if (spin == 25.0)
		spin = spin - 25.0;
}

//a piece of wood
void lumber(){	
	glPushMatrix();
	  glTranslatef(126.0, 73.0, 0.0);
	  glScalef(40.0, 10.0, 1.0);
	  glColor3f(0.6, 0.5, 0.4);
      unitSquare();
	glPopMatrix();
}

//method below called to get/change lumber position
void slideLumber() {
	slide = slide + speed;
	if ( (slide > 500.0) && (slide < 700.0) ) 
		slide = slide - 500.0;
}	

void drawFactory() {
	nameDuct();
	textForNameDuct();
	supplyDuct();
	conveyorBox();
	conveyorBelt();
	cutLumberCollector();
	sawbladeArm();
	factoryishMetalThing();
}


/* mouse function checks to see if buttons are in target area
and if so, changes conveyer belt speed to appropriate value */
void mouse (int button, int state, GLint x, GLint y){
	GLfloat pixel[4];
	GLfloat r, g, b;
	int wHt;
	wHt = glutGet(GLUT_WINDOW_HEIGHT);
	y = wHt - y;
	glReadBuffer(GL_BACK);
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		glReadPixels(x, y, 1.0, 1.0, GL_RGBA, GL_FLOAT, &pixel);
		r = pixel[0]; g = pixel[1]; b = pixel[2];
		if( (r==1.0) && (g==0.0) && (b==0.0) )
			speed = 50.0;
		if( (r==0.0) && (g==1.0) && (b==0.0) )
			speed = 25.0;
		if( (r==0.0) && (g==0.0) && (b==1.0) )
			speed = 5.0;
	}
}

//forces object movement
void idle (void) {
	Time = clock();
	if (Time > ResetTime) {
		ResetTime = ResetTime + TIMEDELTA * CLOCKS_PER_SEC;
		slideLumber();
		spinSaw();
		glutPostRedisplay();
	}
}

/* menu allows user to reset speed values, deactivate equipment,
 and exit the program */
void choiceMain(int selection){
	if (selection == 1) {
		slide = 0.0;
		spin = 0.0;
		speed = 5.0;
	}
	if (selection == 2) {
		slide = 750.0;
		spin = 180.0;
	}
	if (selection == 3) {
		exit(0);
	}
}

void reshape (int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(-10, w, 0, h);
}

void display (void){
	glClear (GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT, GL_FILL);
	glFlush ();

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
    
	//lumber translation
	glPushMatrix();
	glTranslatef(slide, 0.0, 0.0);
	lumber();
	glPopMatrix();

	//saw rotation, note translations done wrt the saw's matrix
	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 0.5);
	if(spin == 5.0)
		glTranslatef(10.0, -53.0, 0.0);
	if(spin == 10.0)
		glTranslatef(13.0, -105.0, 0.0);
	if(spin == 15.0)
		glTranslatef(13.0, -159.0, 0.0);
	if(spin == 20.0)
		glTranslatef(8.0, -212.0, 0.0);
	else
		glTranslatef(0.0, 0.0, 0.0);
	saw();
	glPopMatrix();
	
	drawFactory();
	glFlush ();
	glutSwapBuffers();

	//below draws buttons to back buffer so can be checked if picked
	glDrawBuffer (GL_BACK);
	glPushMatrix();
	  glTranslatef(100.0, 105.0, 0.0);
	  glScalef(10.0, 10.0, 1.0);
	  glColor3f(1.0, 0.0, 0.0);
	  unitSquare();
	glPopMatrix();
	
	glDrawBuffer (GL_BACK);
	glPushMatrix();
	  glTranslatef(80.0, 105.0, 0.0);
	  glScalef(10.0, 10.0, 1.0);
	  glColor3f(0.0, 1.0, 0.0);
	  unitSquare();
	glPopMatrix();
	
	glDrawBuffer (GL_BACK);
	glPushMatrix();
	  glTranslatef(60.0, 105.0, 0.0);
	  glScalef(10.0, 10.0, 1.0);
	  glColor3f(0.0, 0.0, 1.0);
	  unitSquare();
	glPopMatrix();
}

int main (int argc, char** argv){
	cout << "RIGHT CLICK TO SEE MENU, BUTTONS ON MACHINE CONTROL SPEED. \n";
	cout << "\n";
	cout << "BLUE = SLOW, GREEN = MEDIUM SPEED, RED = FAST \n";
	
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize (700, 500);
	glutInitWindowPosition (200, 240);
	glutCreateWindow (argv[0]);
	glutIdleFunc(idle);
	init ();

	//the menu
	glutCreateMenu(choiceMain);
		glutAddMenuEntry("Initialize factory", 1);
		glutAddMenuEntry("Send invisible gnome workers on a break", 2);
		glutAddMenuEntry("Head home!", 3);
		glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutReshapeFunc(reshape);
	glutCreateMenu(choiceMain);
	glutMouseFunc (mouse);
	glutDisplayFunc (display);
	Time = clock();
	ResetTime = Time + TIMEDELTA * CLOCKS_PER_SEC;
	glutMainLoop ();
	return 0;
}