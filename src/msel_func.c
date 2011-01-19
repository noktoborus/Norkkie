#include "msel_func.h"
/* global layer */

static void
_return (size_t layno, struct select_t *lays, size_t argc, char **argv)
{
}

/* exports */
struct cmdCall_t msel_func_return[] =
{
	{ _return, NULL, 0, NULL }
};

/* plugs */
static void
_not_call_here (size_t layno, struct select_t *lays, size_t argc, char **argv)
{
}

/* plug export */
struct cmdCall_t msel_func_NULL[] =
{
	{
		_not_call_here,
		_not_call_here,
		0,
		NULL
	}
};

