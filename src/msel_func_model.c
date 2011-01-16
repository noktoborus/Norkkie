#include "msel_func.h"

/* model layer */
struct cmdargs_t msel_func_msel_args[] =
{
	{CMDARGS_TUINT, 0, {0}},
	{CMDARGS_TVOID, 0, {0}},
};

struct cmdargs_t msel_func_msop_args[] =
{
	{CMDARGS_TUINT, 0, {0}},
	{CMDARGS_TVOID, 0, {0}},
};

struct cmdargs_t msel_func_mdel_args[] =
{
	{CMDARGS_TVOID, 0, {0}}
};

struct cmdargs_t msel_func_mmov_args[] =
{
	{CMDARGS_TFLOAT, 0, {0}},
	{CMDARGS_TVOID, 0, {0}}
};

struct cmdargs_t msel_func_mrot_args[] =
{
	{CMDARGS_TFLOAT, 0, {0}},
	{CMDARGS_TVOID, 0, {0}},
};

void
msel_func_msel (struct cmdnode_t *self, size_t layno, struct _select_t *lay)
{
}
	/* select/deselect additional model */
void
msel_func_msadd (struct cmdnode_t *self, size_t layno, struct _select_t *lay)
{
}

void
msel_func_msdel (struct cmdnode_t *self, size_t layno, struct _select_t *lay)
{
}

void
msel_func_mdel (struct cmdnode_t *self, size_t layno, struct _select_t *lay)
{
}

void
msel_func_mmov (struct cmdnode_t *self, size_t layno, struct _select_t *lay)
{
}

void
msel_func_mrot (struct cmdnode_t *self, size_t layno, struct _select_t *lay)
{
}


