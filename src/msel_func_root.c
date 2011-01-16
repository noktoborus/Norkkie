#include "msel_func.h"
/* root layer */

struct cmdargs_t msel_func_rsel_args[] =
{
	{CMDARGS_TUINT, 0, {0}},
	{CMDARGS_TVOID, 0, {0}},
};

#include <stdio.h>
void
msel_func_rsel (struct cmdnode_t *self, size_t layno, struct _select_t *lay)
{
	printf ("Rsel[%p] -> arg0: %d\n", (void*)self, self->args[0].v.sint);
}

