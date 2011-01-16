#ifndef _MSEL_FUNC_1295024119_
#define _MSEL_FUNC_1295024119_
#include "msel.h"

/* *** Global Funcs *** */

/* return on one layer */
void msel_func_return (struct cmdnode_t*, size_t, struct _select_t*);

/* *** Root layer *** */
extern struct cmdargs_t msel_func_radd_args[];
extern struct cmdargs_t msel_func_rsel_args[];
	/* add and select new model to root */
void msel_func_radd (struct cmdnode_t*, size_t, struct _select_t*);
	/* select model in root */
void msel_func_rsel (struct cmdnode_t*, size_t, struct _select_t*);

/* *** Model layer *** */
extern struct cmdargs_t msel_func_msel_args[];	/* msel */
extern struct cmdargs_t msel_func_msop_args[];	/* msadd/msdel */
extern struct cmdargs_t msel_func_mdel_args[];	/* mdel */
extern struct cmdargs_t msel_func_mmov_args[];	/* mmov */
extern struct cmdargs_t msel_func_mrot_args[];	/* mrot */

	/* select wire in models */
void msel_func_msel (struct cmdnode_t*, size_t, struct _select_t*);
	/* select/deselect additional model */
void msel_func_msadd (struct cmdnode_t*, size_t, struct _select_t*);
void msel_func_msdel (struct cmdnode_t*, size_t, struct _select_t*);
	/* remove model */
void msel_func_mdel (struct cmdnode_t*, size_t, struct _select_t*);
	/* move model on xyz-axis */
void msel_func_mmov (struct cmdnode_t*, size_t, struct _select_t*);
	/* rotate model on xyz-axis */
void msel_func_mrot (struct cmdnode_t*, size_t, struct _select_t*);

#endif /* _MSEL_FUNC_1295024119_ */
