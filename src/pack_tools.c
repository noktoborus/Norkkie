#include "pack_tools.h"

void ptArray2SInt32 (const char *array, int32_t *number)
{
	uint32_t temp = 0;
	if (!array | !number)
		return;
	for (temp = 0; *array; array++)
	{
		if (*array >= '0' && *array <= '9')
			temp = ((*array) - '0') + temp * 10;
	}
	*number = temp;
}

void ptArray2UInt32 (char const *array, uint32_t *number)
{
	uint32_t temp = 0;
	if (!array | !number)
		return;
	for (temp = 0; *array; array++)
	{
		if (*array >= '0' && *array <= '9')
			temp = ((*array) - '0') + temp * 10;
	}
	*number = temp;
}

void ptArray2Float (const char *array, float *number)
{
	if (!array | !number)
		return;
}

