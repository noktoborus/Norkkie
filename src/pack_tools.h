#ifndef _PACK_TOOLS_1295596444_
#define _PACK_TOOLS_1295596444_
#include <stdlib.h>
#include <stdint.h>

/*
 * try unpack Byte Array to signed int:32
 * 	const char *input_arry
 * 	int32_t *output int
 */
void ptArray2SInt32 (const char*, int32_t*);
void ptArray2Uint32 (const char*, uint32_t*);
void ptArray2Float (const char*, float*);

#endif

