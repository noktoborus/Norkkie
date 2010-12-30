#include <string.h>
#include "nurbs.h"
struct NKKBWire_t NKKBWire_d = 
{
	0,
	{0, 0},
	0,
	NULL,
};


inline static unsigned int
_nkkb_err (struct NKKBWire_t *wire, unsigned int errno)
{
	if (!wire) return NKKB_ERR_INVAL;
	wire->errno = errno;
	return errno;
}

void
nkkbWire (struct NKKBWire_t *wire, size_t sizeX, size_t sizeY)
{
	struct NKKBVertex_t *pWire = NULL;
	size_t len = sizeX * sizeY;
	if (len != wire->len)
	{
		pWire = calloc (len, sizeof (struct NKKBVertex_t));
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
	struct NKKBVertex_t *pWire = NULL;
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

