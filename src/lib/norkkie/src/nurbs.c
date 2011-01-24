#include <math.h>
#include <string.h>
#include <norkkie/nurbs.h>

inline static unsigned int
_nkkb_err (struct NKKBWire_t *wire, unsigned int errno)
{
	if (!wire) return NKKB_ERR_INPTR;
	wire->errno = errno;
	return errno;
}

void
nkkbResize (struct NKKBWire_t *wire, size_t szX, size_t szY)
{
	wire->dimension[0] = szX;
	wire->dimension[1] = szY;
}

void
nkkbWire (struct NKKBWire_t *wire, size_t sizeX, size_t sizeY)
{
	struct NKKBVertexW_t *pWire = NULL;
	size_t len = sizeX * sizeY;
	if (len != wire->len)
	{
		pWire = calloc (len, sizeof (struct NKKBVertexW_t));
		if (!pWire)
		{
			_nkkb_err (wire, NKKB_ERR_NOMEM);
			return;
		}
		free (wire->wire);
		wire->wire = pWire;
		wire->size = len;
		wire->len = sizeX;
	}
	else
	{
		memset ((void*)wire->wire, 0, len * sizeof (struct NKKBVertex_t));
	}
}

void
nkkbProc (struct NKKBWire_t *wire, NKKBOpt_t opts, size_t no)
{
	struct NKKBVertexW_t *pWire = NULL;
	size_t sz[2];
	size_t axno = 0;
	size_t len = 0;
	size_t cno = 0;
	size_t i = 0;
	sz[0] = wire->len;
	sz[1] = wire->size / wire->len;
	switch (opts & NKKB_OPT_M0)
	{
		case NKKB_OPT_X:
			axno = 0;
			break;
		case NKKB_OPT_Y:
			axno = 1;
			break;
		default:
			_nkkb_err (wire, NKKB_ERR_INKEY);
			return;
	}
	if (no >= sz[axno]) no = sz[axno] - 1;
	switch (opts & NKKB_OPT_M1)
	{
		case NKKB_OPT_AFTER:
			no++;
		case NKKB_OPT_BEFORE:
			sz[axno]++;
			break;
		case NKKB_OPT_REMOVE:
			sz[axno]--;
			break;
		default:
			_nkkb_err (wire, NKKB_ERR_INKEY);
			return;
	}
	len = sz[0] * sz[1];
	if (len)
	{
		pWire = calloc (len, sizeof (struct NKKBVertexW_t));
		if (!pWire)
		{
			_nkkb_err (wire, NKKB_ERR_NOMEM);
			return;
		}
	}
	else
	{
		free (wire->wire);
		wire->wire = NULL;
		return;
	}
	
	switch (opts & NKKB_OPT_M1)
	{
		case NKKB_OPT_AFTER:
		case NKKB_OPT_BEFORE:
			do
			{
				if ((axno == 0 && cno % sz[0] != no) ||
						(axno == 1 && (cno < (no * sz[0]) ||
						 cno >= (no * sz[0] + sz[0]))))
				{
					pWire[cno] = wire->wire[i++];
				}
			}
			while (++cno < len);
			break;
		case NKKB_OPT_REMOVE:
			do
			{
				if ((axno == 0 && cno % wire->len != no) ||
						(axno == 1 && (cno < (no * wire->len) ||
						 cno >= (no * wire->len + wire->len))))
				{
					pWire[i++] = wire->wire[cno];
				}
			}
			while (++cno < wire->len);
			break;
	}
	free (wire->wire);
	wire->wire = pWire;
	wire->len = len;
	memcpy ((void*)wire->size, (const void*)sz, sizeof (sz));
}

void
nkkbGenPolly (struct NKKBWire_t *wire, size_t gressX, size_t gressY)
{
	struct NKKBPolly_t *polly = NULL;
	struct NKKBVertex_t vx = {{0.f, 0.f, 0.f}};
	size_t x = 0;
	float direct = 1.f;
	/* base alloc */
	polly = (struct NKKBPolly_t*)calloc (1, sizeof (struct NKKBPolly_t));
	if (!polly)
	{
		_nkkb_err (wire, NKKB_ERR_NOMEM);
		return;
	}
	/*
	 * gressX = 2
	 * gressY = 3
	 *
	 * field = (gressX + 2)x(gressY + 2)
	 *
	 * -> X
	 * . . . . | Y
	 * . . . . v
	 * . . . .
	 * . . . .
	 * . . . .
	 */
	memcpy ((void*)polly->dimension,
			(void*)wire->dimension, sizeof (float) * 2);
	polly->len = (gressX + 2) * 2;
	polly->size = ((gressX + 2) * (gressY + 2)) + (gressX + 2) * gressY;
	polly->s = calloc (polly->size, sizeof (struct NKKBVertex_t));
	if (!polly->s)
	{
		_nkkb_err (wire, NKKB_ERR_NOMEM);
		free (polly);
		return;
	}
	for (x = 1; x < polly->size; x++)
	{
		if (!(x % polly->len))
		{
			if((direct = -direct) < 0.f)
			{
				vx.v[0] += 2;
			}
		}
		else
		if (x % 2)
		{
			polly->s[x].v[0] += direct;
		}
		else
		{
			vx.v[1] += direct;
		}
		polly->s[x].v[0] += vx.v[0];
		polly->s[x].v[1] += vx.v[1];
		polly->s[x].v[0] = polly->s[x].v[0] / (float)(gressX + 1) *\
						   polly->dimension[0];
		polly->s[x].v[1] = polly->s[x].v[1] / (float)(gressY + 1) *\
						   polly->dimension[1];
		polly->s[x].v[2] = 0.f;
	}
	if (wire->polly)
		free (wire->polly);
	wire->polly = polly;
}

void
nkkbGenPoints (struct NKKBWire_t *wire)
{
	struct NKKBVertex_t *point;
	register size_t s;
	register size_t x;

	point = calloc (wire->size, sizeof (struct NKKBVertex_t));
	if (!point)
	{
		free (point);
		_nkkb_err (wire, NKKB_ERR_NOMEM);
		return;
	}

	for (s = 0; s < wire->size; s++)
	{
		point[s].v[0] = (s % wire->len) / (float)(wire->len - 1) *
				wire->dimension[0];
		point[s].v[1] = (s / wire->len) / (float)(wire->size / wire->len - 1) *
				wire->dimension[1];
		for (x = 0; x < 3; x++)
		{
			point[s].v[x] += wire->wire[s].v[x];
		}
	}

	if (wire->point)
		free (wire->point);
	wire->point = point;
}

#include <stdio.h>
void
nkkbBendPolly (struct NKKBWire_t *wire)
{
	register size_t x = 0;
	register size_t xx = 0;
	struct NKKBVertex_t pollx = {{0.f, 0.f, 0.f}};
	float A = 0.f;
	float B = 0.f;
	float r = 0.f;
	if (!wire->polly || !wire->point)
		return;

	for (x = 0; x < wire->polly->size; x++)
	{
		pollx.v[0] = wire->polly->s[x].v[0];
		pollx.v[1] = wire->polly->s[x].v[1];
		pollx.v[2] = wire->polly->s[x].v[2];
		for (xx = 0; xx < wire->size; xx++)
		{
			/* calc radius */
			A = fabsf (pollx.v[0] - wire->point[xx].v[0]) + 1.f;
			B = fabsf (pollx.v[1] - wire->point[xx].v[1]) + 1.f;
			A = sqrtf (A * A + B * B);
			B = fabsf (pollx.v[2] - wire->point[xx].v[2]) + 1.f;
			r = sqrtf (A * A + B * B);
			if (r)
				wire->polly->s[x].v[2] += (1 / r);
		}
	}
}

