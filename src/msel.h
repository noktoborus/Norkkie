#ifndef _MSEL_1295020820_
#define _MSEL_1295020820_
/*
 * Select model
 */

#define CMDARGS_TVOID	0
#define CMDARGS_TSTRING 1
#define CMDARGS_TSINT	2
#define CMDARGS_TUINT	3
#define CMDARGS_TFLOAT	4
struct cmdargs_t
{
	uint32_t key;
	/* first 3bites: indicate type
	 * last 28bites: size of value (for TSTRING)
	 */
	union
	{
		char *cstr;
		int32_t sint;
		uint32_t uint;
		float flt;
	} v;
};

struct cmdnode_t
{
	char *tag; /* string tag */
	void (*ptr) (struct cmdnode_t*); /* pointer to callback func */
	int wargc; /* want nunber of arguments */
	struct cmdargs_t *args; /* ptr to args */
};

#define SELECT_NONE		-1
#define SELECT_MODEL	0
#define SELECT_WIRE		1
#define SELECT_NODE		2
#define SELECT_COUNT_S	3
struct _select_t
{
	uint8_t xyz; // for movements
	size_t sz; // size of nums
	size_t *nums;
};

struct select_t
{
	struct _select_t sel[SELECT_COUNT_S];
	int current; /* select current (from SELECT_NONE to SELECT_COUNT_S) */
} root_sel =
{
	{
		{0, 0, NULL},
		{0, 0, NULL},
		{0, 0, NULL},
	},
	0
};


#endif /* _MSEL_1295020820_ */

