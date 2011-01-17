#ifndef _MSEL_1295020820_
#define _MSEL_1295020820_
#include <stdint.h>
#include <stdlib.h>
#include "input.h"
/*
 * Select model
 */

#define SELECT_NONE		-1
#define SELECT_ROOT		0
#define SELECT_MODEL	1
#define SELECT_WIRE		2
#define SELECT_NODE		3
#define SELECT_COUNT_S	4

struct _select_t
{
	/* for movements */
	uint8_t xyz;
	/* size of nums */
	size_t sz;
	size_t *nums;
	size_t cmds_count;
	struct cmdnode_t *cmds;
};

struct select_t
{
	struct _select_t *sel;
	/* select current (from SELECT_NONE to SELECT_COUNT_S) */
	int cursel;
	/* global  cmds */
	size_t cmds_count;
	struct cmdnode_t *cmds;
};

struct cmdargs_t
{
	/* set to FINPUT_TVOID, FINPUT_TSTRING (from input.h), etc */
	int type;
	/* length for TSTRING */
	size_t len;
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
	/* string tag */
	char *tag;
	size_t taglen;
	/* **
	 * pointers to callback func
	 * 	struct cmdnode_t *current_node_ptr
	 * 	size_t num_of_current_layer
	 * 	struct _select_t *current_layer_ptr
	 */
	/*  merge arguments and object */
	void (*merge) (struct cmdnode_t*, size_t, struct _select_t*);
	/*  discard previous `merge call */
	void (*split) (struct cmdnode_t*, size_t, struct _select_t*);
	/* ptr to args, terminate at TVOID*/
	struct cmdargs_t *args;
};


#endif /* _MSEL_1295020820_ */

