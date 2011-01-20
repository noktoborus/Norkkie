#include "msel_func.h"

/* model layer */
static int _msel_args[] =
{
	FINPUT_TUINT, FINPUT_TVOID
};

static int _mmov_args[] =
{
	FINPUT_TFLOAT, FINPUT_TVOID
};

static void
_msel (size_t layno, struct select_t *lays, size_t argc, char **argv)
{
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

