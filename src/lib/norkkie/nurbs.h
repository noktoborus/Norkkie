#ifndef _NURBS_H_1293390403 
#define _NURBS_H_1293390403 
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t NKKBOpt_t;
#define NKKB_OPT_S0	0
/* select X-axis for `no */
#define NKKB_OPT_X	(1 << NKKB_OPT_S0)
/* select Y-axis for `no */
#define NKKB_OPT_Y	(2 << NKKB_OPT_S0)
#define NKKB_OPT_M0 (NKKB_OPT_X | NKKB_OPT_Y)

#define NKKB_OPT_S1	(NKKB_OPT_S0 + 2)
/* insert before selected `no */
#define NKKB_OPT_BEFORE	(1 << NKKB_OPT_S1)
/* insert after selected `no */
#define NKKB_OPT_AFTER	(2 << NKKB_OPT_S1)
/* remove selected `no */
#define NKKB_OPT_REMOVE	(3 << NKKB_OPT_S1)
#define NKKB_OPT_M1 (NKKB_OPT_BEFORE | NKKB_OPT_AFTER | NKKB_OPT_REMOVE)

#define NKKB_ERR_NOMEM	1
#define NKKB_ERR_INPTR	2
#define NKKB_ERR_INKEY	3
#define NKKB_ERR_INVAL	4

struct NKKBVertex_t
{
	/* {x, y, z} */
	float v[3];
};

struct NKKBVertexW_t
{
	/* {x, y, z} */
	float v[3];
	/* weight */
	float w;
};

struct NKKBPolly_t
{
	/* width and height */
	float dimension[2];
	/* size of array */
	size_t size;
	/* count of points in one line */
	size_t len;
	/* point to vertex array */
	struct NKKBVertex_t *s;
};

struct NKKBWire_t
{
	unsigned int errno;
	/* width and height */
	float dimension[2];
	/* overall points count in array */
	size_t size;
	/* len of line (count point in one line) */
	size_t len;
	/* point to polly structure */
	struct NKKBPolly_t *polly;
	/* point to points array */
	struct NKKBVertex_t *point;
	/* point to points+weight array */
	struct NKKBVertexW_t *wire;
};

/*
 * Init/reInit(purge) exists NKKBWire structure
 */
void nkkbWire (struct NKKBWire_t *wire, size_t sizeX, size_t sizeY);
/*
 * resize field
 */
void nkkbResize (struct NKKBWire_t *wire, size_t X, size_t Y);
/*
 * Execec selected operation on selected row/col
 */
void nkkbProc (struct NKKBWire_t *wire, NKKBOpt_t opts, size_t no);
/*
 * Create a polyginal model
 */
void nkkbGenPolly (struct NKKBWire_t *wire, size_t gressX, size_t gressY);
void nkkbGenPoints (struct NKKBWire_t *wire);
/* not a real NURBS curves */
void nkkbBendPolly (struct NKKBWire_t *wire);

#endif // define _NURBS_H_1293390403

