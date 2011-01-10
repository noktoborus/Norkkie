#define _BSD_SOURCE 1
#define _POSIX_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/glc.h>
#include <math.h>
#include "nurbs.h"

struct colorRGBA_t
{
	float R;
	float G;
	float B;
	float A;
} colorBackground = 
{
	0.0f, 0.0f, 0.0f, 0.0f
};

struct scrn_change_t
{
	char calc;
	float distance;
	float pos_begin[2];
	float angle[2];
	float angle_old[2];
} scrn_change =
{
	0,
	-70.0f,
	{0.0f, 0.0f}
};

struct NKKBWire_t wire;

void display(void)
{
	size_t x;
	float cpos[3] = {0.f, 0.f, 0.f};
	float npos[3] = {0.f, 0.f, 0.f};
	cpos[0] = 0.f;
	npos[0] = 0.f;
	x = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// zero matrix
	glLoadIdentity ();
	glTranslatef (0.0f, 0.0f, scrn_change.distance);
	// rotate screen
	glRotatef (scrn_change.angle[1], 1.0, 0.0, 0.0);
	glRotatef (scrn_change.angle[0], 0.0, 1.0, 0.0);
	// draw screen
	glPolygonMode (GL_FRONT, GL_LINE);
#if 0
	/*
	glBegin (GL_TRIANGLE_STRIP);
	glColor3f (1.f, 0.f, 0.f);
	glVertex2f (0.f, 0.f);	// 0
	glColor3f (0.f, 1.f, 0.f);
	glVertex2f (0.f, 10.f);	// 1
	glColor3f (0.f, 0.f, 1.f);
	glVertex2f (10.f, 10.f);	// 2

	glColor3f (1.f, 1.f, 1.f);
	glVertex2f (0.f, 20.f);	// 3
	glColor3f (1.f, 0.f, 0.f);
	glVertex2f (10.f, 20.f);	// 4

	// reset to 2 line
	glVertex2f (10.f, 20.f);	// 5
	// new line from 5..6 node
	glColor3f (0.f, 1.f, 0.f);
	glVertex2f (20.f, 10.f);	// 6

	glVertex2f (20.f, 20.f);
	glEnd ();
	*/
#endif
#if 1
	glBegin (GL_TRIANGLE_STRIP);
	for (x = 0; wire.polly && x < wire.polly->size; x++)
	{
		switch (x % 3)
		{
			case 0:
				glColor3f (1.f, 0.f, 0.f);
				break;
			case 1:
				glColor3f (0.f, 1.f, 0.f);
				break;
			case 2:
				glColor3f (0.f, 0.f, 1.f);
				break;
		}
		glVertex3fv (wire.polly->s[x].v);
	}
	glEnd ();
#endif
#if 1
	// draw control
	//glTranslatef (0.f, 0.f, 1.f);
	glColor3f (1.f, 0.f, 0.f);
	glPointSize (3);
	glBegin (GL_POINTS);
	for (x = 0; x < wire.size; x++)
	{
		glVertex3fv (wire.point[x].v);
	}
	glEnd ();
#endif 
#if 0
	glBegin (GL_TRIANGLES);
		glColor3f (1.f, 1.f, 1.f);
		glVertex3f (0.f, 0.f, 0.f);
		glColor3f (0.f, 0.f, 0.f);
		glVertex3f (10.f, 10.f, 0.f);
		glVertex3f (10.f, 0.f, 0.f);
	glEnd ();
#endif
		glBegin(GL_TRIANGLES);						// Drawing Using Triangles
		glVertex3f( 0.0f, 1.0f, 0.0f);				// Top
		glVertex3f(-1.0f,-1.0f, 0.0f);				// Bottom Left
		glVertex3f( 1.0f,-1.0f, 0.0f);				// Bottom Right
	glEnd();							// Finished Drawing The Triangle
	glLoadIdentity ();
	glTranslatef (0.f, 0.f, -1.f);
	//glScalef (-0.5f, -0.5f, -0.5f);
	glColor3f (1.f, 1.f, 1.f);
	glcScale (10.f, 10.f);
	glcRenderString ("Hello");


 	glutSwapBuffers ();
}

void reshape(int x, int y)
{
	GLdouble ASP = (GLdouble)x / (GLdouble)y;
	glViewport (0, 0, (GLsizei)x, (GLsizei)y);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (45.f, ASP, 0.1, 100.);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
	}
	glutPostRedisplay ();
}

void
mouse (int but, int state, int x, int y)
{
	if (but == 3 || but == 4)
	{
		if (state == 1)
		{
			switch (but)
			{
				case 3:
					scrn_change.distance += 10;
					break;
				case 4:
					scrn_change.distance -= 10;
					break;
			}
		}
	}
	else
	{
		scrn_change.calc ^= 1;
		scrn_change.pos_begin[0] = (float)x;
		scrn_change.pos_begin[1] = (float)y;
		memcpy ((void*)&(scrn_change.angle_old), (void*)&(scrn_change.angle),\
				sizeof (float) * 2);
	}
	glutPostRedisplay ();
}


void
set_rotate (int val, int axis)
{
	float dist0 = val - scrn_change.pos_begin[axis];
	//dist0 = (dist0 > scrn_change.distance) ?
	//	scrn_change.distance / dist0 : dist0 / scrn_change.distance;
	dist0 = dist0 / scrn_change.distance;
	if (val != scrn_change.pos_begin[axis])
	{
		scrn_change.angle[axis] = 180/M_PI * atan (dist0);
		scrn_change.angle[axis] += scrn_change.angle_old[axis];
		while (scrn_change.angle[axis] > 360.0f)
			scrn_change.angle[axis] -= 360.0f;
		while (scrn_change.angle[axis] < 0.0f)
			scrn_change.angle[axis] += 360.0f;
	}
}

void
motion (int x, int y)
{
	if ((float)x != scrn_change.pos_begin[0]) set_rotate (x, 0);
	if ((float)y != scrn_change.pos_begin[1]) set_rotate (y, 1);
	glutPostRedisplay ();
}

int main(int argc, char **argv)
{
	GLint glc_ctx;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutCreateWindow(argv[0]);
	glutMouseFunc (mouse);
	glutMotionFunc (motion);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	
	glc_ctx = glcGenContext ();
	glcContext (glc_ctx);
	glcRenderStyle (GLC_TRIANGLE);

	nkkbWire (&wire, 5, 5);
	nkkbResize (&wire, 10, 10);
	nkkbGenPolly (&wire, 10, 10);
	nkkbGenPoints (&wire);
	glutMainLoop();
	return 0;
}

