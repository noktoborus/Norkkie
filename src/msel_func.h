#ifndef _MSEL_FUNC_1295024119_
#define _MSEL_FUNC_1295024119_
#include "msel.h"

/* *** Global Funcs *** */

/* return on one layer */
void msel_func_return (struct cmdnode_t*, size_t, struct _select_t*);

/* *** Root layer *** */
extern struct cmdargs_t msel_func_rsel_args[];
void msel_func_rsel (struct cmdnode_t*, size_t, struct _select_t*);

/* *** Model layer *** */
extern struct cmdargs_t msel_func_msel_args[];
extern struct cmdargs_t msel_func_mdel_args[];
extern struct cmdargs_t msel_func_mlist_args[];
extern struct cmdargs_t msel_func_mmov_args[];
extern struct cmdargs_t msel_func_mrot_args[];

void msel_func_msel (struct cmdnode_t*, size_t, struct _select_t*);
void msel_func_mdel (struct cmdnode_t*, size_t, struct _select_t*);
void msel_func_mlist (struct cmdnode_t*, size_t, struct _select_t*);
void msel_func_mmov (struct cmdnode_t*, size_t, struct _select_t*);
void msel_func_mrot (struct cmdnode_t*, size_t, struct _select_t*);

#endif /* _MSEL_FUNC_1295024119_ */
