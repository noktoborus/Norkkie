#include "msel_func.h"
#include "pack_tools.h"
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
{ FINPUT_TUINT, FINPUT_TVOID };

static void
_rsel (size_t layno, struct select_t *lays, size_t argc, char **argv)
{
	uint32_t no = 0;
	struct listModel_t *model = NULL;
	if (!lays->model || argc < 2)
		return;
	ptArray2UInt32 (argv[1], &no);
	if ((model = lays->model))
	{
		do
		{
			if (model->model.idno == no)
				break;
		}
		while ((model = model->next) != lays->model);
	}
	else
		return;

	if (model->model.idno == no)
	{
		if (!msel_nums_append (&lays->sel[SELECT_MODEL], no))
		{
			model->model.selected = true;
			lays->cursel = SELECT_MODEL;
		}
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

