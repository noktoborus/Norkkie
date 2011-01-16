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
				return true;
		case FINPUT_TSINT:
			if (in == '-')
				return true;
		case FINPUT_TUINT:
			if (in == '+' || (in >= '0' && in <= '9'))
				return true;
		case FINPUT_TVOID:
			/* allways false ;3 */
	};
	return 1;
}

