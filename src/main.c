#define _BSD_SOURCE 1
#define _POSIX_SOURCE 1
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
	struct cmdNode_t *cmd;
	/* num of current arg in cmd */
	size_t argn;
	char **argv;
	/* * next/prev node */
	/* ptr to next node */
	struct input_node_t *next;
	/* ptr to last (previous) node */
	struct input_node_t *prev;
};

#define INPUT_SZ 256
struct input_cmds_t
{
	/* want type to input */
	int type;
	/* input string len */
	size_t strlen;
	/* input string offset */
	size_t offset;
	/* current input string (not parsed) */
	char *input;
	/* out if place char in input */
	char failch;
	/* * */
	struct input_node_t *i;
	struct input_node_t *c;
} inputs =
{
	FINPUT_TSTRING,
	0,
	0,
	NULL,
	'\0',
	NULL,
	NULL,
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

/* *** feel select's structs *** */
struct cmdNode_t __cmdnodes_root[] =
{
	{ "a", 1, "/* TODO a */", msel_func_radd },
	{ "s", 1, "/* TODO s */", msel_func_rsel },
	{ NULL, 0, NULL, NULL }
};

struct cmdNode_t __cmdnodes_model[] =
{
	{ "s", 1, "/* TODO s */", msel_func_msel },
	{ "+", 1, "/* TODO + */", msel_func_msadd },
	{ "-", 1, "/* TODO - */", msel_func_msdel },
	{ "m", 1, "/* TODO m */", msel_func_mmov },
	{ "r", 1, "/* TODO r */", msel_func_mrot },
	{ "d", 1, "/* TODO d */", msel_func_mdel },
	{ NULL, 0, NULL, NULL }
};

struct cmdNode_t __cmdnodes_wire[] =
{
	{ NULL, 0, NULL, NULL }
};

struct cmdNode_t __cmdnodes_node[] =
{
	{ NULL, 0, NULL, NULL }
};

struct cmdNode_t _cmdnodes_global[] =
{
	{ "r", 1, "/* TODO r*/", msel_func_return },
	{ NULL, 0, NULL, NULL }
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
	struct listModel_t *model_ptr;
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
	/* rotate screen */
	glRotatef (scrn_change.angle[1], 1.0, 0.0, 0.0);
	glRotatef (scrn_change.angle[0], 0.0, 1.0, 0.0);
	/* draw screen */
	//glPolygonMode (GL_FRONT, GL_LINE);
	if ((model_ptr = root_sel.model))
	{
		do
		{
		/* TODO */
			/* draw control */
			glPointSize (3);
			glColor3f (1.f, 0.f, 0.f);
			glBegin (GL_POINTS);
			for (x = 0; x < model_ptr->model.wire.size; x++)
			{
				glVertex3fv (model_ptr->model.wire.point[x].v);
			}
			glEnd ();
		}
		while ((model_ptr = model_ptr->next) != root_sel.model);
	}
	/* draw interface */
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0., scrn_info.width, -scrn_info.height, 0., 1.0, -1.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glColor3f (1.f, 0.f, 0.f);
	scale2[0] = scrn_info.width * 0.02f;
	scale2[1] = scrn_info.height * 0.02f * scrn_info.aspect;
	if (scale2[0] < 10.f)
	{
		scale2[0] = 10.f;
		scale2[1] = 10.f;
	}

	glTranslatef (0.f, -scale2[1], 0.f);
	glPushMatrix ();
	glBegin (GL_QUADS);
		glVertex2f (-3.f, -3.f);
		glVertex2f (scrn_info.width, -3.f);
		glVertex2f (scrn_info.width, scale2[1]);
		glVertex2f (-3.f, scale2[1]);
	glEnd ();

	glScalef (scale2[0], scale2[1], 0.f);
	glColor3f (1.f, 1.f, 1.f);
	if (inputs.input)
	{
		inputs.input[inputs.strlen] = '\0';
		glcRenderString (&inputs.input[inputs.offset]);
	}
	if (inputs.failch)
	{
		glColor3f (1.0f, 1.f, 0.f);
		glcRenderChar (inputs.failch);
	}
	glPopMatrix ();

	glTranslatef (0.f, -scale2[1], 0.f);
	glPushMatrix ();
	glScalef (scale2[0], scale2[1], 0.f);
	if (inputs.c && inputs.c->cmd)
	{
		glColor3f (1.f, 1.f, 1.f);
		glcRenderString (inputs.c->cmd->tag);
		glcRenderString ("(");
		for (x = 0; x < inputs.c->cmd->call->wargc; x++)
		{
			if (x < inputs.c->argn)
			{
				glcRenderString ("ok, ");
			}
			else
			{
				glcRenderString (input_n2s[inputs.c->cmd->\
							call->wargk[x]].string);
				glcRenderString (", ");
			}
		}
		glcRenderString ("void)");
	}
	else
	{
		glcRenderString ("wait command");
	}
	glPopMatrix ();
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

void
subkey (unsigned char key)
{
	char *tmp;
	struct cmdNode_t *cmd;
	size_t sz;

	/* test control symbols */
	if (key == 127)
	{
		/* its <DEL> */
		if (inputs.failch)
		{
			inputs.failch = '\0';
		}
		else
		if (inputs.strlen)
		{
			inputs.strlen--;
		}
		else
		if (inputs.c)
		{
			/* TODO: raise from args last line before remove call ptr */
			/* remove current call pointer */
			inputs.c->argn = 0;
			inputs.c->cmd = NULL;
			/* TODO: call split */
		}
		return;
	}
	else
	/* remove all data in input */
	if (key == 8)
	{
		inputs.strlen = 0;
		return;
	}

	/* ignore ',' in start of line and over characters */
	if ((!inputs.strlen && key == ',') ||
			(key != ',' && input_filter (inputs.type, key)))
	{
		inputs.failch = key;
		return;
	}

	/* test struct input_cmds_t */
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
			if (inputs.i->prev)
				inputs.i->prev->next = inputs.c;
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

	/* add new char */
	inputs.input[inputs.strlen] = key;
	inputs.strlen++;
	/* free error */
	inputs.failch = '\0';

	/** current command not set **/
	if (!(cmd = inputs.c->cmd))
	{
		/* try find in layer space */
		if ((cmd = root_sel.sel[root_sel.cursel].cmds))
		{
			do
			{
				/* skip smallest or biggest tags */
				if (cmd->taglen != inputs.strlen)
					continue;
				/* set current tag to find :3 */
				if (!strncmp (cmd->tag, inputs.input, inputs.strlen))
					break;
			}
			while ((++cmd)->tag);
		}
		/* try find in global space */
		if (cmd && !(cmd->tag) && (cmd = root_sel.cmds))
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
		/* continues input */
		if (cmd && cmd->tag)
		{
			if (!cmd->call)
				cmd->call = msel_func_NULL;
			else
			if (!cmd->call->merge)
				cmd->call->merge = msel_func_NULL->merge;
			else
			if (!cmd->call->split)
				cmd->call->split = msel_func_NULL->split;

			inputs.offset = cmd->taglen;
			inputs.input[inputs.offset] = '\0';

			/* try alloc memory */
			inputs.c->argv = calloc (1 + cmd->call->wargc, sizeof (char**));
			if (!inputs.c->argv)
				return;
			inputs.c->cmd = cmd;
			inputs.c->argn = 0;
		}
	}

	/* test current command */
	if (inputs.c->cmd)
	{
		if (inputs.input[inputs.strlen - 1] == ',')
		{
			inputs.input[inputs.strlen] = '\0';
			inputs.c->argn++;
			inputs.offset = inputs.strlen - inputs.offset;
		}

		/* %( */
		if (inputs.c->argn > inputs.c->cmd->call->wargc)
			inputs.c->argn = inputs.c->cmd->call->wargc;

		/* test for call */
		if (inputs.c->argn == inputs.c->cmd->call->wargc)
		{
			inputs.c->argv[0] = calloc (inputs.strlen, sizeof (char));
			if (!inputs.c->argv[0])
			{
				free (inputs.c->argv);
				inputs.c = NULL;
				return;
			}
			memcpy (inputs.c->argv[0], inputs.input, inputs.strlen);

			/* ptr to over data */
			if (inputs.c->argn)
			{
				do
				{
					inputs.c->argv[inputs.c->argn] =
						&inputs.input[--inputs.offset];
				}
				while (--inputs.c->argn);
			}
			inputs.c->cmd->call->merge (root_sel.cursel, &root_sel,
					inputs.c->cmd->call->wargc, inputs.c->argv);
			inputs.c = NULL;
			inputs.strlen = 0;
			inputs.offset = 0;
			inputs.type = FINPUT_TSTRING;
		}
		else
		{
			/* set input type */
			inputs.type = inputs.c->cmd->call->wargk[inputs.c->argn];
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

	glutMainLoop();
	return 0;
}

