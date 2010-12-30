#ifndef _NURBS_H_1293390403 
#define _NURBS_H_1293390403 
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t NKKBOpt_t;
#define NKKB_OPT_S0	0
#define NKKB_OPT_X	(1 << NKKB_OPT_S0)
#define NKKB_OPT_Y	(2 << NKKB_OPT_S0)
#define NKKB_OPT_M0 (NKKB_OPT_X | NKKB_OPT_Y)

#define NKKB_OPT_S1	2
#define NKKB_OPT_BEFORE	(1 << NKKB_OPT_S1)
#define NKKB_OPT_AFTER	(2 << NKKB_OPT_S1)
#define NKKB_OPT_REMOVE	(3 << NKKB_OPT_S1)
#define NKKB_OPT_M1 (NKKB_OPT_BEFORE | NKKB_OPT_AFTER | NKKB_OPT_REMOVE)

#define NKKB_ERR_NOMEM	1
#define NKKB_ERR_INKEY	2
#define NKKB_ERR_INVAL	3

struct NKKBVertex_t
{
	float v[3];
};

extern struct NKKBWire_t
{
	unsigned int errno;
	size_t size[2];
	size_t len;
	struct NKKBVertex_t *wire;
} NLLBWire_d;

void nkkbWire (struct NKKBWire_t *wire, size_t sizeX, size_t sizeY);
/*
 * Execec selected operation on selected row/col
 */
void nkkbProc (struct NKKBWire_t *wire, NKKBOpt_t opts, size_t no);

#endif // define _NURBS_H_1293390403

