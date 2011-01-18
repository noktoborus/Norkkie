#include "msel_func.h"

/* model layer */
static struct cmdArgs_t _msel_args[] =
{
	{FINPUT_TUINT, 0, {0}},
	{FINPUT_TVOID, 0, {0}},
};

static struct cmdArgs_t _msop_args[] =
{
	{FINPUT_TUINT, 0, {0}},
	{FINPUT_TVOID, 0, {0}},
};

static struct cmdArgs_t _mmov_args[] =
{
	{FINPUT_TFLOAT, 0, {0}},
	{FINPUT_TVOID, 0, {0}}
};

static struct cmdArgs_t _mrot_args[] =
{
	{FINPUT_TFLOAT, 0, {0}},
	{FINPUT_TVOID, 0, {0}},
};

static void
_msel (struct cmdNode_t *self, size_t layno, struct select_t *lays)
{
}

static void
_msadd (struct cmdNode_t *self, size_t layno, struct select_t *lays)
{
}

static void
_msdel (struct cmdNode_t *self, size_t layno, struct select_t *lays)
{
}

static void
_mdel (struct cmdNode_t *self, size_t layno, struct select_t *lays)
{
}

static void
_mmov (struct cmdNode_t *self, size_t layno, struct select_t *lays)
{
}

static void
_mrot (struct cmdNode_t *self, size_t layno, struct select_t *lay)
{
}

/* exports */

struct cmdCall_t msel_func_msel[] =
{
	{ _msel, NULL, sizeof (_msel_args), _msel_args }
};

struct cmdCall_t msel_func_msadd[] =
{
	{ _msadd, NULL, sizeof (_msop_args), _msop_args }
};

struct cmdCall_t msel_func_msdel[] =
{
	{ _msdel, NULL, sizeof (_msop_args), _msop_args }
};

struct cmdCall_t msel_func_mmov[] =
{
	{ _mmov, NULL, sizeof (_mmov_args), _mmov_args }
};

struct cmdCall_t msel_func_mrot[] =
{
	{ _mrot, NULL, sizeof (_mrot_args), _mrot_args }
};

struct cmdCall_t msel_func_mdel[] =
{
	{ _mdel, NULL, 0, NULL }
};
