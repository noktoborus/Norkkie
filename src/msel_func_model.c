#include "msel_func.h"
#include "pack_tools.h"
/* model layer */
static int _msel_args[] =
{ FINPUT_TUINT, FINPUT_TVOID };

static void
_msel (size_t layno, struct select_t *lays, size_t argc, char **argv)
{
	uint32_t no = 0;
	struct listModel_t *model = lays->model;
	if (!model || argc < 2)
		return;
	ptArray2UInt32 (argv[1], &no);
	do
	{
		if (model->model.selected && no < model->model.wire.size)
		{
			/* ok, append the node */
			if (!msel_nums_append (&lays->sel[SELECT_WIRE], no))
				lays->cursel = SELECT_WIRE;
			/* and exit */
			return;
		}

	}
	while ((model = model->next) != lays->model);
}

static void
_msadd (size_t layno, struct select_t *lays, size_t argc, char **argv)
{
}

static void
_msdel (size_t layno, struct select_t *lays, size_t argc, char **argv)
{
}

static void
_mdel (size_t layno, struct select_t *lays, size_t argc, char **argv)
{
}

static int _mmov_args[] =
{ FINPUT_TFLOAT, FINPUT_TVOID };

static void
_mmov (size_t layno, struct select_t *lays, size_t argc, char **argv)
{
}

static void
_mrot (size_t layno, struct select_t *lay, size_t argc, char **argv)
{
}

/* exports */

struct cmdCall_t msel_func_msel[] =
{
	{ _msel, NULL, _msel_args }
};

struct cmdCall_t msel_func_msadd[] =
{
	{ _msadd, NULL, _msel_args }
};

struct cmdCall_t msel_func_msdel[] =
{
	{ _msdel, NULL, _msel_args }
};

struct cmdCall_t msel_func_mmov[] =
{
	{ _mmov, NULL, _mmov_args }
};

struct cmdCall_t msel_func_mrot[] =
{
	{ _mrot, NULL, _mmov_args }
};

struct cmdCall_t msel_func_mdel[] =
{
	{ _mdel, NULL, NULL }
};

