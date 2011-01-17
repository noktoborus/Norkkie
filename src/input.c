#include "input.h"

struct input_n2s_t input_n2s[] =
{
	{FINPUT_TVOID, "void"},
	{FINPUT_TSTRING, "string"},
	{FINPUT_TSINT, "signed int"},
	{FINPUT_TUINT, "unsigned int"},
	{FINPUT_TFLOAT, "float"},
};

int
input_filter (int type, unsigned char in)
{
	switch (type)
	{
		case FINPUT_TSTRING:
			/* true to all symbols ? */
			return 0;
		case FINPUT_TFLOAT:
			if (in == '.')
				return 0;
		case FINPUT_TSINT:
			if (in == '-')
				return 0;
		case FINPUT_TUINT:
			if (in == '+' || (in >= '0' && in <= '9'))
				return 0;
		case FINPUT_TVOID:
			/* allways false ;3 */
			break;
	};
	return 1;
}

