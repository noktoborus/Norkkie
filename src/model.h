#ifndef _MODEL_H_1295361343_
#define _MODEL_H_1295361343_
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "nurbs.h"

/* models lists and structs */
struct model_t
{
	size_t idno;
	bool selected;
	struct NKKBVertex_t pos;
	struct NKKBWire_t wire;
};

struct listModel_t
{
	struct model_t model;
	struct listModel_t *prev;
	struct listModel_t *next;
};


#endif /* _MODEL_H_1295361343_ */

