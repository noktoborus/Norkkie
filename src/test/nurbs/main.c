#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <norkkie/nurbs.h>

GLfloat rot[3];
GLfloat dist = -100.f;

struct NKKBWire_t wire_struct;
struct NKKBWire_t *wire;

void
display ()
{
	register size_t x = 0;
	char buf[1024];
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	for (x = 0; x < 3; x++)
	{
		while (rot[x] >= 360.f) rot[x] = rot[x] - 360.f;
		while (rot[x] < 0.f) rot[x] = rot[x] + 360.f;
	}
	glTranslatef (0.f, 0.f, dist);
	glRotatef (rot[0], 1.f, 0.f, 0.f);
	glRotatef (rot[1], 0.f, 1.f, 0.f);
	glRotatef (rot[2], 0.f, 0.f, 1.f);
	glTranslatef (-(wire->dimension[0] / 2.f),
			-(wire->dimension[1] / 2.f), 0.f);
	/* draw */
	glPolygonMode (GL_FRONT, GL_LINE);
	if (wire->polly && wire->polly->size)
	{
		glColor3f (0.2f, 0.2f, 0.2f);
		glBegin (GL_TRIANGLE_STRIP);
		for (x = 0; x < wire->polly->size; x++)
		{
			glVertex3fv (wire->polly->s[x].v);
		}
		glEnd ();
	}

	if (wire->point && wire->size)
	{
		/* draw control points */
		glBegin (GL_POINTS);
		glColor3f (1.f, 0.f, 0.f);
		for (x = 0; x < wire->size; x++)
		{
			glVertex3fv (wire->point[x].v);
		}
		glEnd ();
	}

	glLoadIdentity ();
	glTranslatef (0.f, 0.f, -100.f);
	glColor3f (0.4f, 0.f, 0.f);
	snprintf (buf, 1024, "rot (%.2f, %.2f, %.2f) dist (%.2f)",
			rot[0], rot[1], rot[2], dist);
	glRasterPos2f (-20.f, -10.f);
	for (x = 0; x < 1024 && buf[x]; x++)
		glutBitmapCharacter (GLUT_BITMAP_9_BY_15, buf[x]);
#if 0
	snprintf (buf, 1024, "size: (%.2f, %.2f)", wire->dimension[0],
			wire->dimension[1]);
	glRasterPos2f (-20.f, -20.f);
	for (x = 0; x < 1024 && buf[x]; x++)
		glutBitmapCharacter (GLUT_BITMAP_9_BY_15, buf[x]);
#endif
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
	//printf ("%d\n", key);
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
			rot[1] += 2.f;
			break;
		case 'h':
			rot[1] -= 2.f;
			break;
		case 'i':
			rot[2] += 2.f;
			break;
		case 'm':
			rot[2] -= 2.f;
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

	wire = &wire_struct;
	nkkbWire (wire, 5, 5);
	nkkbResize (wire, 10, 10);
	nkkbGenPoints (wire);
	nkkbGenPolly (wire, 10, 10);
	glClearColor (0.f, 0.f, 0.f, 0.f);
	glutMainLoop ();
	return 0;
}

