#ifndef _MSEL_FUNC_1295024119_
#define _MSEL_FUNC_1295024119_
#include "msel.h"

/* *** Global Funcs *** */
extern struct cmdCall_t msel_func_NULL[];
	/* return on one layer */
extern struct cmdCall_t msel_func_return[];

/* *** Root layer *** */
	/* create new model */
extern struct cmdCall_t msel_func_radd[];
	/* select model */
extern struct cmdCall_t msel_func_rsel[];

/* *** Model layer *** */
	/* select wire in models */
extern struct cmdCall_t msel_func_msel[];
	/* select/deselect additional model */
extern struct cmdCall_t msel_func_msadd[];
	/* remove model */
extern struct cmdCall_t msel_func_msdel[];
	/* move model on xyz-axis */
extern struct cmdCall_t msel_func_mmov[];
	/* rotate model on xyz-axis */
extern struct cmdCall_t msel_func_mrot[];
	/* delete selected models */
extern struct cmdCall_t msel_func_mdel[];

#endif /* _MSEL_FUNC_1295024119_ */

