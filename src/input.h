#ifndef _INPUT_H_1295176378_
#define _INPUT_H_1295176378_

#define FINPUT_TVOID	0 /* none (voids) */
#define FINPUT_TSTRING	1 /* strings */
#define FINPUT_TSINT	2 /* signed int */
#define FINPUT_TUINT	3 /* unsigned int */
#define FINPUT_TFLOAT	4 /* float */

/*
 * test input char:
 * 	0 is ok
 * 	!0 not ok
 */
int input_filter (char type, unsigned char in);

#endif /* _INPUT_H_1295176378_ */

