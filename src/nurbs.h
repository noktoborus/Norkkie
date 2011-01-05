#ifndef _NURBS_H_1293390403 
#define _NURBS_H_1293390403 
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t NKKBOpt_t;
#define NKKB_OPT_S0	0
#define NKKB_OPT_X	(1 << NKKB_OPT_S0)
#define NKKB_OPT_Y	(2 << NKKB_OPT_S0)
#define NKKB_OPT_M0 (NKKB_OPT_X | NKKB_OPT_Y)

#define NKKB_OPT_S1	(NKKB_OPT_S0 + 2)
#define NKKB_OPT_BEFORE	(1 << NKKB_OPT_S1)
#define NKKB_OPT_AFTER	(2 << NKKB_OPT_S1)
#define NKKB_OPT_REMOVE	(3 << NKKB_OPT_S1)
#define NKKB_OPT_M1 (NKKB_OPT_BEFORE | NKKB_OPT_AFTER | NKKB_OPT_REMOVE)

#define NKKB_ERR_NOMEM	1
#define NKKB_ERR_INPTR	2
#define NKKB_ERR_INKEY	3
#define NKKB_ERR_INVAL	4

struct NKKBVertex_t
{
	float v[3]; // = {x, y, z}
};

struct NKKBVertexW_t
{
	float v[3]; // = {x, y, z}
	float w; // weight
};

struct NKKBPolly_t
{
	float dimension[2]; // width and height
	size_t size; // size of array
	size_t len; // count of points in one line
	struct NKKBVertex_t *s;
};

struct NKKBWire_t
{
	unsigned int errno;
	float dimension[2]; // width and height
	size_t size; // overall points count in array
	size_t len; // len of line (count point in one line)
	struct NKKBPolly_t *polly;
	struct NKKBVertexW_t *wire;
};

/*
 * Init/reInit(purge) exists NKKBWire structure
 */
void nkkbWire (struct NKKBWire_t *wire, size_t sizeX, size_t sizeY);
/*
 * resize field
 */
void nkkbXY (struct NKKBWire_t *wire, size_t X, size_t Y);
/*
 * Execec selected operation on selected row/col
 */
void nkkbProc (struct NKKBWire_t *wire, NKKBOpt_t opts, size_t no);
/*
 * Create a polyginal model
 */
void nkkbPolly (struct NKKBWire_t *wire, size_t gressX, size_t gressY);
#endif // define _NURBS_H_1293390403

