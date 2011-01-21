#include "msel_func.h"
/* root layer */

static void
_rcre (size_t layno, struct select_t *lays, size_t argc, char **argv)
{
	struct listModel_t *m = NULL;
	if (!lays->model)
	{
		m = calloc (1, sizeof (struct listModel_t));
		if (!m)
			return;
		lays->model = m;
		lays->model->next = lays->model;
		lays->model->prev = lays->model;
		lays->model->model.idno = 1;

	}
	else
	{
		m = calloc (1, sizeof (struct listModel_t));
		if (!m)
			return;
		m->next = lays->model;
		m->prev = lays->model->prev;
		lays->model->prev->next = m;
		lays->model->prev = m;
		m->model.idno = m->prev->model.idno + 1;
	}
	if (m)
	{
		nkkbWire (&m->model.wire, 5, 5);
		nkkbResize (&m->model.wire, 10, 10);
		nkkbGenPolly (&m->model.wire, 10, 10);
		nkkbGenPoints (&m->model.wire);
	}
}

static int _rsel_args[]=
{
	FINPUT_TUINT, FINPUT_TVOID
};
#include <stdio.h>
static void
_rsel (size_t layno, struct select_t *lays, size_t argc, char **argv)
{
	printf ("call[%s]: %d\n", argv[0], argc);
	while (argc--)
	{
		printf ("  %2d\t%s\n", argc, argv[argc]);
	}
}


/* exported structs */
struct cmdCall_t msel_func_rcre[] =
{
	{ _rcre, NULL, NULL }
};

struct cmdCall_t msel_func_rsel[] =
{
	{ _rsel, NULL, _rsel_args }
};

