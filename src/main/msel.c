#include <stdlib.h>
#include <string.h>
#include "msel.h"


int
msel_nums_append (struct _select_t *sel, size_t num)
{
	size_t x = 0;
	size_t *tmp = NULL;
	if (!sel)
		return 1;
	if (!sel->sz)
	{
		if (sel->nums)
			free (sel->nums);
		sel->nums = calloc (SELECT_BLKSZ, sizeof (size_t));
		if (!sel->nums)
			return 1;
		sel->nums[sel->sz++] = num;
	}
	else
	{
		for (x = 0; x < sel->sz; x++)
		{
			/* num in arrays, return ok */
			if (sel->nums[x] == num)
				return 0;
		}
		/* resize array and put new num */
		if ((sel->sz + 1) % SELECT_BLKSZ < sel->sz % SELECT_BLKSZ)
		{
			/* resize */
			tmp = calloc (sel->sz + 1, sizeof (size_t));
			if (!tmp)
				return 1;
			memcpy (tmp, (const void*)sel->nums, sel->sz * sizeof (size_t));
			free (sel->nums);
			sel->nums = tmp;
		}
		/* put */
		sel->nums[sel->sz++] = num;
	}
	return 0;
}

int
msel_nums_remove (struct _select_t *sel, size_t num)
{
	return 1;
}

