#include "msel_func.h"
/* root layer */

static void
_radd (struct cmdNode_t *self, size_t layno, struct select_t *lays)
{
	if (!lays->model)
	{
		lays->model = calloc (1, sizeof (struct listModel_t));
		if (!lays->model)
			return;
		nkkbWire (&lays->model->model.wire, 5, 5);
		nkkbResize (&lays->model->model.wire, 10, 10);
		nkkbGenPolly (&lays->model->model.wire, 10, 10);
		nkkbGenPoints (&lays->model->model.wire);
	}
}

static void
_rsel (struct cmdNode_t *self, size_t layno, struct select_t *lays)
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

