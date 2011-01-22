#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <norkkie/nurbs.h>

GLfloat rot[3];
GLfloat dist = -100.f;

void
display ()
{
	register unsigned int x = 0;
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	for (x = 0; x < 3; x++)
	{
		if (rot[x] > 360.f) rot[x] = 0.f;
		if (rot[x] < 0.f) rot[x] = 360.f;
	}
	glTranslatef (0.f, 0.f, dist);
	glRotatef (rot[0], 1.f, 0.f, 0.f);
	glRotatef (rot[1], 0.f, 1.f, 0.f);
	glRotatef (rot[2], 0.f, 0.f, 1.f);


	glutSwapBuffers ();
	printf ("rot (%.2f, %.2f, %.2f) dist (%.2f)\n", rot[0], rot[1], rot[2], dist);
	printf ("\n");
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
	printf ("%d\n", key);
	switch (key)
	{
		case 27: /* <Esc> */
			exit(0);
			break;
		case 'k':
			dist += 5.f;
			break;
		case 'j':
			dist -= 5.f;
			break;
		case 'l':
			rot[2] += 2.f;
			break;
		case 'h':
			rot[2] -= 2.f;
			break;
		case 'i':
			rot[1] += 2.f;
			break;
		case 'm':
			rot[1] -= 2.f;
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

