#ifndef _MSEL_1295020820_
#define _MSEL_1295020820_
#include <stdint.h>
#include <stdlib.h>
#include "input.h"
#include "model.h"

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
	struct cmdNode_t *cmds;
};

struct select_t
{
	struct _select_t *sel;
	/* select current (from SELECT_NONE to SELECT_COUNT_S) */
	int cursel;
	/* global  cmds */
	size_t cmds_count;
	struct cmdNode_t *cmds;
	/* ptr to models */
	struct listModel_t *model;
};

struct cmdArgs_t
{
	/* set to FINPUT_TVOID, FINPUT_TSTRING (from input.h), etc */
	int type;
	/* length for TSTRING */
};

union cmdVar_t
{
	char *cstr;
	int32_t sint;
	uint32_t uint;
	float flt;
};

struct cmdNode_t
{
	/* string tag */
	char *tag;
	size_t taglen;
	/* description */
	char *info;
	struct cmdCall_t *call;
};

struct cmdCall_t
{
	/* **
	 * pointers to callback func
	 * 	size_t number_of_current_layer
	 * 	struct select_t *layers_stack
	 * 	size_t argc
	 * 	char **argv
	 */
	/*  merge arguments and object */
	void (*merge) (size_t, struct select_t*, size_t, char**);
	/*  discard previous `merge call */
	void (*split) (size_t, struct select_t*, size_t, char**);
	/* size args structure for malloc */
	size_t wargc;
	/* ptr to args, terminate at TVOID*/
	int *wargk;
};

#endif /* _MSEL_1295020820_ */

