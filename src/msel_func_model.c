#include "msel_func.h"

/* model layer */
static int _msel_args[] =
{
	FINPUT_TUINT
};

static int _mmov_args[] =
{
	FINPUT_TFLOAT
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
	{ _msel, NULL, 1, _msel_args }
};

struct cmdCall_t msel_func_msadd[] =
{
	{ _msadd, NULL, 1, _msel_args }
};

struct cmdCall_t msel_func_msdel[] =
{
	{ _msdel, NULL, 1, _msel_args }
};

struct cmdCall_t msel_func_mmov[] =
{
	{ _mmov, NULL, 1, _mmov_args }
};

struct cmdCall_t msel_func_mrot[] =
{
	{ _mrot, NULL, 1, _mmov_args }
};

struct cmdCall_t msel_func_mdel[] =
{
	{ _mdel, NULL, 0, NULL }
};

