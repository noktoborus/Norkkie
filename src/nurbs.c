#include <string.h>
#include "nurbs.h"

inline static unsigned int
_nkkb_err (struct NKKBWire_t *wire, unsigned int errno)
{
	if (!wire) return NKKB_ERR_INPTR;
	wire->errno = errno;
	return errno;
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
		wire->size[0] = sizeX;
		wire->size[1] = sizeY;
		wire->len = len;
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
	size_t sz[] = { wire->size[0], wire->size[1] };
	size_t axno = 0;
	size_t cno = 0;
	size_t i = 0;
	size_t len = 0;
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
	if (no >= wire->size[axno]) no = wire->size[axno] - 1;
	switch (opts & NKKB_OPT_M1)
	{
		case NKKB_OPT_AFTER:
			no++;
		case NKKB_OPT_BEFORE:
			sz[axno]++;
			break;
		case NKKB_OPT_REMOVE:
			sz[axno]--;
			if (no >= wire->size[axno])
			{
				_nkkb_err (wire, NKKB_ERR_INVAL);
				return;
			}
			break;
		default:
			_nkkb_err (wire, NKKB_ERR_INKEY);
			return;
	}
	len = sz[0] * sz[1];
	if (len)
	{
		pWire = calloc (len, sizeof (struct NKKBVertex_t));
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
				if ((axno == 0 && cno % wire->size[0] != no) ||
						(axno == 1 && (cno < (no * wire->size[0]) ||
						 cno >= (no * wire->size[0] + wire->size[0]))))
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
nkkbPoly (struct NKKBWire_t *wire, size_t gress, size_t scale)
{
	struct NKKBVertex_t *vxes = NULL;
	struct NKKBVertex_t vx = {{0.f, 0.f, 0.f}};
	float direct = 1.f;
	size_t x = 0;
	size_t line = (gress + 2) * 2;
	size_t x_ = line * (1 + gress);
	// alloc field
	vxes = calloc (x_, sizeof (struct NKKBVertex_t));
	if (!vxes)
	{
		_nkkb_err (wire, NKKB_ERR_NOMEM);
		return;
	}
	// place field
	for (x = 0; x < x_; x++)
	{
		if (x && !(x % line))
		{
			// invert step
			if ((direct = -direct) < 0.f)
				// and fix start point position
				vx.v[0] += 2;
			vxes[x].v[0] = vx.v[0];
			vxes[x].v[1] = vx.v[1];
		}
		else
		if (x % 2)
		{
			vxes[x].v[0] = vx.v[0] + direct;
			vxes[x].v[1] = vx.v[1];
		}
		else
		{
			vxes[x].v[0] = vx.v[0];
			vxes[x].v[1] = (vx.v[1] += direct);
		}
	}
	//
	//
	wire->polys = vxes;
	wire->polys_len = line;
	wire->polys_size = x_;
	wire->polys_gress = gress;
	wire->polys_scale = scale;
}

