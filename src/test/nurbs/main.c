#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <GL/glut.h>

#include <norkkie/nurbs.h>
void
display ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers ();
}

void
reshape(int x, int y)
{
	GLfloat aspect = x / (float)y;
	glViewport (0, 0, (GLsizei)x, (GLsizei)y);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (45.f, aspect, .1, 5000.);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void
keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
	}
	glutPostRedisplay ();
}

int
main (int argc, char *argv[])
{
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (400, 400);
	glutCreateWindow("nurbs-test");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glClearColor (0.f, 0.f, 0.f, 0.f);
	glutMainLoop ();
	return 0;
}

