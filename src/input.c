#include "input.h"

int
input_filter (char type, unsigned char in)
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

