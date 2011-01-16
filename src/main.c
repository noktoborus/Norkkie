#define _BSD_SOURCE 1
#define _POSIX_SOURCE 1
#define _XOPEN_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/glc.h>
#include <math.h>
#include "nurbs.h"
#include "msel.h"
#include "msel_func.h"

struct input_node_t
{
	/* pointer to finded func */
	struct cmdnode_t *cmd;
	/* num of current arg in cmd */
	size_t argn;
	/* * next/prev node */
	/* ptr to next node */
	struct input_node_t *next;
	/* ptr to last (previous) node */
	struct input_node_t *prev;
};

#define INPUT_SZ 256
struct input_cmds_t
{
	/* input string len */
	size_t strlen;
	/* current input string (not parsed) */
	char *input;
	/* * */
	struct input_node_t *i;
	struct input_node_t *c;
	char *cache;
} inputs =
{
	0,
	NULL,
	NULL,
	NULL,
	NULL
};

/* old */
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

struct scrn_info_t
{
	float width;
	float height;
	float aspect;
} scrn_info =
{
	0.f, 0.f, 0.f
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

struct model_t
{
	struct NKKBVertex_t pos;
	struct NKKBWire_t wire;
};

/* *** feel select's structs *** */
struct cmdnode_t __cmdnodes_root[] =
{
	{ "s", 1, msel_func_rsel, NULL, msel_func_rsel_args },
	{ NULL, 0, NULL, NULL, NULL }
};

struct cmdnode_t __cmdnodes_model[] =
{
	{ "s", 1, msel_func_msel, NULL, msel_func_msel_args },
	{ "m", 1, msel_func_mmov, NULL, msel_func_mmov_args },
	{ "r", 1, msel_func_mrot, NULL, msel_func_mrot_args },
	{ "+", 1, msel_func_mlist, NULL, msel_func_mlist_args },
	{ "-", 1, msel_func_mlist, NULL, msel_func_mlist_args },
	{ NULL, 0, NULL, NULL }
};

struct cmdnode_t __cmdnodes_wire[] =
{
	{ NULL, 0, NULL, NULL, NULL }
};

struct cmdnode_t __cmdnodes_node[] =
{
	{ NULL, 0, NULL, NULL, NULL }
};

struct cmdnode_t _cmdnodes_global[] =
{
	{ "r", 1, msel_func_return, NULL, NULL },
	{ NULL, 0, NULL, NULL, NULL }
};

struct _select_t _root_sel_s[SELECT_COUNT_S] =
{
	{0, 0, NULL, 0, __cmdnodes_root},
	{0, 0, NULL, 0, __cmdnodes_model},
	{0, 0, NULL, 0, __cmdnodes_wire},
	{0, 0, NULL, 0, __cmdnodes_node},
};

struct select_t root_sel =
{
	_root_sel_s,
	0,
	1,
	_cmdnodes_global
};

/* *** code *** */
struct NKKBWire_t wire;

uint64_t glpe_inters = 0;
uint64_t glcpe_inters = 0;
inline static void
glpe ()
{
	GLenum er = glGetError ();
	if (er != GL_NO_ERROR)
	{
		fprintf (stderr, "OpenGL: %d -> %s (%lld)\n", er, gluErrorString (er),
				glpe_inters);
	}
	glpe_inters++;
}
inline static void
glcpe ()
{
	GLenum er = glcGetError ();
	char *s = "uncow";
	if (er != GLC_NONE)
	{
		switch (er)
		{
			case GLC_PARAMETER_ERROR:
				s = "error in parameter";
				break;
			case GLC_RESOURCE_ERROR:
				s = "defect resource";
				break;
			case GLC_STATE_ERROR:
				s = "state error";
				break;
		}
		fprintf (stderr, "GLC: %0*x -> %s (%lld)\n", 4, er, s, glcpe_inters);
	}
	glcpe_inters++;
}

void
display(void)
{
	size_t x;
	float cpos[3] = {0.f, 0.f, 0.f};
	float npos[3] = {0.f, 0.f, 0.f};
	float scale2[2] = {0.f, 0.f};
	if (!scrn_info.width || !scrn_info.height) return;
	cpos[0] = 0.f;
	npos[0] = 0.f;
	x = 0;
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (45.f, scrn_info.aspect, .1, 5000.);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

	glTranslatef (0.0f, 0.0f, scrn_change.distance);
	// rotate screen
	glRotatef (scrn_change.angle[1], 1.0, 0.0, 0.0);
	glRotatef (scrn_change.angle[0], 0.0, 1.0, 0.0);
	// draw screen
	//glPolygonMode (GL_FRONT, GL_LINE);
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
		glVertex3f(0.0f, 1.0f, 0.0f);				// Top
		glVertex3f(-1.0f, -1.0f, 0.0f);				// Bottom Left
		glVertex3f(1.0f, -1.0f, 0.0f);				// Bottom Right
	glEnd();							// Finished Drawing The Triangle

	// draw interface
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0., scrn_info.width, -scrn_info.height, 0., 1.0, -1.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

	scale2[0] = scrn_info.width * 0.02f;
	scale2[1] = scrn_info.height * 0.02f * scrn_info.aspect;
	if (scale2[0] < 10.f)
	{
		scale2[0] = 10.f;
		scale2[1] = 10.f;
	}

	glTranslatef (0.f, -scale2[1], 0.f);
	
	glBegin (GL_QUADS);
		glVertex2f (-3.f, -3.f);
		glVertex2f (scrn_info.width, -3.f);
		glVertex2f (scrn_info.width, scale2[1]);
		glVertex2f (-3.f, scale2[1]);
	glEnd ();

	glScalef (scale2[0], scale2[1], 0.f);
	//glTranslatef (0.f, 0.f, -1.f);
	//glTranslatef (-20.f, -20.f, -50.f);
	//glScalef (-0.5f, -0.5f, -0.5f);
	glColor3f (1.f, 1.f, 1.f);
	if (inputs.input)
	{
		inputs.input[inputs.strlen] = '\0';
		glcRenderString (inputs.input);
	}

 	glutSwapBuffers ();
	glpe ();
}

void reshape(int x, int y)
{
	scrn_info.aspect = x / (float)y;
	scrn_info.width = (float)x;
	scrn_info.height = (float)y;
	glViewport (0, 0, (GLsizei)x, (GLsizei)y);
}

int
unpack_cmdarg (struct cmdargs_t *dst, char *in, size_t len)
{
	/* prepare argument for call from
	 * 	string *in with length len in struct *dst
	 */
	size_t shift = 0;
	printf ("prepare[%d]: (%d) %s\n", dst->type, len, in);
	switch (dst->type)
	{
		case CMDARGS_TVOID:
			break;
		case CMDARGS_TSTRING:
			/* free old value */
			if (dst->v.cstr)
				free (dst->v.cstr);
			/* copy new */
			dst->v.cstr = strdup (in);
			if (!dst->v.cstr)
				return 1;
			dst->len = len;
			break;
		case CMDARGS_TSINT:
			dst->v.sint = 0;
			while (len--)
			{
				if (in[len] == '-')
					dst->v.sint *= -1;
				else
				if (in[len] >= '0' && in[len] <= '9')
					dst->v.sint += (in[len] - '0') * pow (10, shift++);
			}
			break;
		case CMDARGS_TUINT:
			dst->v.uint = 0;
			while (len--)
			{
				if (in[len] >= '0' && in[len] <= '9')
				{
					dst->v.uint += (in[len] - '0') * pow (10, shift++);
					printf ("S#%d -> [%c] %u\n", len, in[len], dst->v.uint);
				}
			}
			break;
		case CMDARGS_TFLOAT:
			dst->v.flt = 0;
			break;
		default:
			return 1;
	};
	return 0;
}

void
subkey (unsigned char key)
{
	char *tmp;
	struct cmdnode_t *cmd;
	if (!inputs.c)
	{
		if (!inputs.i)
		{
			inputs.i = calloc (1, sizeof (struct input_node_t));
			if (!inputs.i)
				return;
			inputs.c = inputs.i;
		}
		else
		{
			inputs.c = calloc (1, sizeof (struct input_node_t));
			if (!inputs.c)
				return;
			inputs.c->prev = inputs.i->prev;
			inputs.i->prev = inputs.c;
		}
	}
	/* alloc input string */
	if (!inputs.input)
	{
		inputs.input = calloc (INPUT_SZ, sizeof (char));
		if (!inputs.input)
			return;
		inputs.strlen = 0;
	}
	else
	/* fix line then DEL is used */
	if (key == 127)
	{
		if (inputs.strlen)
		{
			inputs.strlen--;
		}
		else
		{
			/* remove current call ptr */
			inputs.c->argn = 0;
			inputs.c->cmd = NULL;
			/* TODO: call split */
		}
		return;
	}
	else
	/* ignore ',' in start of line and all not-printable chars*/
	if ((!inputs.strlen && key == ','))
	{
		return;
	}
	else
	/* resize string */
	if ((inputs.strlen + 1) % INPUT_SZ < inputs.strlen % INPUT_SZ)
	{
		tmp = calloc (inputs.strlen + INPUT_SZ, sizeof (char));
		if (!tmp)
			return;
		memcpy (tmp, (const void*)inputs.input, inputs.strlen);
		free (inputs.input);
		inputs.input = tmp;
	}
	inputs.input[inputs.strlen] = key;
	inputs.strlen++;
	/** current command not set **/
	if (!inputs.c->cmd)
	{
		/* try find in layer space */
		if ((cmd = root_sel.sel[root_sel.cursel].cmds))
		{
			do
			{
				/* skip smallest tags */
				if (cmd->taglen != inputs.strlen)
					continue;
				/* set current tag to find :3 */
				if (!strncmp (cmd->tag, inputs.input, inputs.strlen))
					break;
			}
			while ((++cmd)->tag);
		}
		/* try find in global space */
		if (!(cmd->tag) && (cmd = root_sel.cmds))
		{
			do
			{
				if (cmd->taglen != inputs.strlen)
					continue;
				if (!strncmp (cmd->tag, inputs.input, inputs.strlen))
					break;
			}
			while ((++cmd)->tag);
		}
		if (cmd->tag)
		{
			/* set current func */
			inputs.c->cmd = cmd;
			/* avoid possible errors :3 */
			inputs.c->argn = 0;
			/* rewind input */
			inputs.strlen = 0;
		}
	}
	/* test current command */
	if (inputs.c->cmd)
	{
		/* if it end of args */
		if(inputs.input[inputs.strlen - 1] == ',')
		{
			/* remove ',' from string */
			inputs.input[--inputs.strlen] = '\0';
			/* unpack args */
			if (!unpack_cmdarg (&inputs.c->cmd->args[inputs.c->argn],
					inputs.input, inputs.strlen))
			{
				/* if unpack is ok */
				inputs.c->argn++;
				/* rewind */
				inputs.strlen = 0;
			}
		}

		/* null args count or complite: exec now */
		if (!inputs.c->cmd->args ||
				inputs.c->cmd->args[inputs.c->argn].type == CMDARGS_TVOID)
		{
			/* call */
			if (inputs.c->cmd->merge)
			{
				inputs.c->cmd->merge (inputs.c->cmd, root_sel.cursel,
						&root_sel.sel[root_sel.cursel]);
			}
			/* change ptr */
			inputs.c = NULL;
		}
	}
}

void
keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
		default:
			subkey (key);
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
	GLint glc_font;
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
	glc_font = glcGenFontID ();
	glc_font = glcNewFontFromFamily (glc_font, "DejaVu Sans Mono");
	glcFont (glc_font);
	glcpe ();

#if 0
	glcRenderStyle (GLC_LINE); /* not work on mesa-gallium? */
#else
	glcRenderStyle (GLC_TEXTURE);
#endif
	glEnable (GL_TEXTURE_2D); /* for GLC_TEXTURE */

	nkkbWire (&wire, 5, 5);
	nkkbResize (&wire, 10, 10);
	nkkbGenPolly (&wire, 10, 10);
	nkkbGenPoints (&wire);
	glutMainLoop();
	return 0;
}

