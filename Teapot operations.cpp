#include <GL\glut.h>
#include<iostream>

GLfloat xRotated, yRotated, zRotated;
GLdouble size = 1;

int ch;

void processNormalKeys(unsigned char key, int x, int y) 
{

	if (key == 'q')                                 // press q to zoom in
		size += 0.3f;
	if (key == 'e')									// press e to zoom out
		size -= 0.3f;
	if (key == 'a')									// press a to rotate right in x axis
		yRotated += 3.0f;
	if (key == 'd')									// press d to rotate left in x axis
		yRotated -= 3.0f;
	if (key == 'w')									// press w  to rotate top back in y axis
		xRotated += 3.0f;
	if (key == 's')									// press s to ratate top front in y axis
		xRotated -= 3.0f;
	if (key == '1')									// press 1 to get solid frame of teapot
		ch = 0;
	if (key == '2')									// press 2 to get wireframe of teapot
		ch = 1;
	if (key == '4')									// press 4 and (1 or 2) to get red color
		ch = 2;
	if (key == '5')									// press 5 and (1 or 2) to get white color
		ch = 3;
	if (key == '6')									// press 6 and (1 or 2) to get yellow color
		ch = 4;
	if (key == '7')									// press 7 and (1 or 2) to get green color
		ch = 5;

}

void display(void)
{

	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0.0, 0.0, -4.5);
	
	//coloring
	if (ch == 2)
		glColor3f(0.8, 0.2, 0.1);  //red color
	else if (ch == 3)
		glColor3f(1.0, 1.0, 1.0);  //white color
	else if (ch == 4)
		glColor3f(0.8,0.7,0.1);		//yellow color
	else if (ch == 5)
		glColor3f(0.0, 1.0, 0.0);	//green color
	
else if (ch == 6)
		glTranslatef(0.05f, 0.10f, 0.18f);
	else if (ch == 7)
		glTranslatef(-0.1f, 0.0f, 0.0f);
	
	// rotation about X axis
	glRotatef(xRotated, 1.0, 0.0, 0.0);
	// rotation about Y axis
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	// rotation about Z axis
	glRotatef(zRotated, 0.0, 0.0, 1.0);
	// scaling transfomation 
	glScalef(1.0, 1.0, 1.0);
	// built-in (glut library) function , draw you a Teapot.	
	if(ch==0)
		glutSolidTeapot(size);//solid frame teapot
	else if (ch==1)
		glutWireTeapot(size);//wireframe teapot
	
	/*for cube 
		glutSolidCube(size);
		glutWireCube(size);		*/

	glFlush();
	// sawp buffers called because we are using double buffering 
	// glutSwapBuffers();
}

void reshapeFunc(int x, int y)
{
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
								   //Set a new projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0

	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);

	glViewport(0, 0, x, y);  //Use the whole window for rendering
}

void idleFunc(void)
{
	//yRotated += 0.01;
	display();
}


int main(int argc, char **argv)
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(400, 350);

	glutCreateWindow("Teapot Rotating Animation");
	

	glutDisplayFunc(display);
	glutReshapeFunc(reshapeFunc);
	glutIdleFunc(idleFunc);
	glutKeyboardFunc(processNormalKeys);

	glutMainLoop();
	return 0;
}