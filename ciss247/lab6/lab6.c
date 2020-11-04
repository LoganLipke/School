/*
*   Lab 6
*   Logan Lipke CISS 247 Fall
*   11/3/20
*/

#include <stdio.h>

typedef unsigned float_bits;
int float_class(float_bits *f);
float_bits float_negate(float_bits *f);
float_bits float_absval(float_bits *f);
float_bits float_twice(float_bits *f);
float_bits float_half(float_bits *f);

int main(int argc, char *argv[]) {
	float_bits fbits;
	sscanf(argv[1], "%e", (float *)&fbits);


	float *f = (float*)&fbits;
	// printf("fbits : %u\n", fbits);
	printf("Before negate: %e\n", *f);
	fbits = float_negate(&fbits);
	f = (float*)&fbits;
	printf("After negate : %e\n", *f);
	
	fbits = float_absval(&fbits);
	f = (float*)&fbits;
	printf("After abs_val: %e\n", *f);
	
	fbits = float_twice(&fbits);
	f = (float*)&fbits;
	printf("After double : %e\n", *f);

	fbits = float_half(&fbits);
	f = (float*)&fbits;
	printf("After half : %e\n", *f);


	int class = float_class(&fbits);
	if (class < 0)
		printf("float_class type: special\n");
	else if (class == 0)
		printf("float_class type: denormalized\n");
	else 
		printf("float_class type: normalized\n");
}

int float_class(float_bits *f)
{
	// p/m infinity = exp all 1, frac all 0
	// NaN = exp all 1, frac not all 0
	// leftmost fraction bit == 1; normalized else denormalized
	printf("%d\n", ~(*f ^ (0xff << 23)));
	printf("%d\n", *f & (1 << 22));
	return (*f ^ (0xff << 23)) & (*f & (1 << 22));
}

float_bits float_negate(float_bits *f)
{
	return (*f | (1 << 31));
}

float_bits float_absval(float_bits *f)
{
	return (*f & (0xff | (0xff << 8) | (0xff << 16) | (0x7f << 24)));
}

float_bits float_twice(float_bits *f)
{
	return *f + (1 << 23);
}

float_bits float_half(float_bits *f)
{
	return *f + ((~1 >> 1) << 23);	
}
