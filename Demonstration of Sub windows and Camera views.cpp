#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLdouble size = 1;

// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 0.0f;

// XZ position of the camera
float x = 0.0f, z = 5.0f, y = 1.75f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

// variables to compute frames per second
int frame;
long time, timebase;
char s[50];

// variables to hold window identifiers
int mainWindow, subWindow1, subWindow2, subWindow3;
//border between subwindows
int border = 6;

// width and height of the window
int h, w;

float orthoSize, fov;

void setProjection(int w1, int h1)
{
	float ratio;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	ratio = 1.0f * w1 / h1;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w1, h1);

	// Set the clipping volume
	gluPerspective(45, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void changeSize(int w1, int h1) {

	if (h1 == 0)
		h1 = 1;

	// we're keeping these values cause we'll need them latter
	w = w1;
	h = h1;

	// set subwindow 1 as the active window
	glutSetWindow(subWindow1);
	// resize and reposition the sub window
	glutPositionWindow(border, border);
	glutReshapeWindow(w - 2 * border, h / 2 - border * 3 / 2);
	setProjection(w - 2 * border, h / 2 - border * 3 / 2);

	// set subwindow 2 as the active window
	glutSetWindow(subWindow2);
	// resize and reposition the sub window
	glutPositionWindow(border, (h + border) / 2);
	glutReshapeWindow(w - 2 * border, h / 2 - border * 3 / 2);
	setProjection(w - 2 * border, h / 2 - border * 3 / 2);
}

void renderScene()
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glTranslatef(0,0,-4.4f);
	glRotatef(deltaAngle, 0, 1, 0);
	glutWireTeapot(size);

	glTranslatef(0.5,0.5,0);
	glutSolidCube(size);
	
	glutSwapBuffers();
}

void renderScenes1() 
{
	glutSetWindow(subWindow1);
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	gluPerspective(fov,1,0.001f,100.0f);			//perspective view
	renderScene();
}

// Display func for sub window 2 demonstrates the orthographic view
void renderScenes2() {

	glutSetWindow(subWindow2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-orthoSize,orthoSize,-orthoSize,orthoSize,0.001f,100);
	renderScene();
}

void renderSceneAll() 
{	
	renderScenes1();
	renderScenes2();
}

void processNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27) {
		glutDestroyWindow(subWindow1);
		glutDestroyWindow(subWindow2);

		glutDestroyWindow(mainWindow);
		exit(0);
	}
	if (key == 'q')				//press q to rotate right in x axis
	{
		deltaAngle += 1.0f;
	}
	if (key == 'e')				//press e to rotate right in x axis
	{
		deltaAngle += 1.0f;
	}
}

void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_UP: deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}


void init() 
{	
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
}

int main(int argc, char **argv) {

	orthoSize = 4;
	fov = 40;

	// init GLUT and create main window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 600);
	mainWindow = glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// callbacks for main window
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderSceneAll);
	init();

	// sub windows
	subWindow1 = glutCreateSubWindow(mainWindow, 0, 0, 400, 200);
	glutDisplayFunc(renderScenes1);
	init();

	subWindow2 = glutCreateSubWindow(mainWindow, 0,200, 400,200);
	glutDisplayFunc(renderScenes2);
	init();
	glutMainLoop();

	return 1;
}