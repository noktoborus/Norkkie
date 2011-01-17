#include "msel_func.h"
/* global layer */

static void
_return (struct cmdNode_t *self, size_t layno, struct select_t *lays)
{
}

/* exports */
struct cmdCall_t msel_func_return[] =
{
	{ _return, NULL, NULL }
};

/* plugs */
static void
_do_not_call_here (struct cmdNode_t *self, size_t layno, struct select_t *lays)
{
}

static struct cmdArgs_t _nobody_here[] =
{
	{ FINPUT_TVOID, 0, {0}}
};

/* plug export */
struct cmdCall_t msel_func_NULL[] =
{
	{ _do_not_call_here, _do_not_call_here, _nobody_here }
};

