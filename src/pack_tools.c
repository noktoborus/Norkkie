#include "pack_tools.h"


void ptArray2SInt32 (const char *array, int32_t *number)
{
	int32_t temp = 0;
	size_t s = 0;
	if (!array | !number)
		return;
	for (s = 0; *array; array++, s++)
	{
		if (*array >= '0' && *array <= '9')
		{
			temp += (*array - '0') * (10 * s);
		}
		else
		if (*array == '-')
		{
			temp *= -1;
		}
	}
	*number = temp;
}

void ptArray2Uint32 (char const *array, uint32_t *number)
{
	uint32_t temp;
	size_t s = 0;
	if (!array | !number)
		return;
	for (s = 0; *array; array++, s++)
	{
		if (*array >= '0' && *array <= '9')
		{
			temp += (*array - '0') * (10 * s);
		}
	}
	*number = 0;
}

void ptArray2Float (const char *array, float *number)
{
	if (!array | !number)
		return;
}

