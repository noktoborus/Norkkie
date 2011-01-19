#include "msel_func.h"
/* root layer */

static void
_radd (struct cmdCall_t *self, size_t layno, struct select_t *lays)
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

static void
_rsel (struct cmdCall_t *self, size_t layno, struct select_t *lays)
{
}

static struct cmdArgs_t _rsel_args[] =
{
	{FINPUT_TUINT, 0, {0}},
	{FINPUT_TVOID, 0, {0}},
};

/* exported structs */
struct cmdCall_t msel_func_radd[] =
{
	{ _radd, NULL, 0, NULL }
};

struct cmdCall_t msel_func_rsel[] =
{
	{ _rsel, NULL, sizeof (_rsel_args), _rsel_args }
};

