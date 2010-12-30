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
	100.0f,
	{0.0f, 0.0f}
};

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// zero matrix
	glLoadIdentity ();
	glTranslatef (0.0f, 0.0f, scrn_change.distance);
	// rotate screen
	glRotatef (scrn_change.angle[1], 1.0, 0.0, 0.0);
	glRotatef (scrn_change.angle[0], 0.0, 1.0, 0.0);
	// draw screen
	

	glutSwapBuffers ();
}

void reshape(int x, int y)
{
	GLdouble ASP = (GLdouble)x / (GLdouble)y;
	glViewport (0, 0, (GLsizei)x, (GLsizei)y);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (45.0f, ASP, 1.0, 1000.0);

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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutCreateWindow(argv[0]);
	glutMouseFunc (mouse);
	glutMotionFunc (motion);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}

