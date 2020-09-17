#include <stdio.h>

typedef unsigned float_bits;


int main(int argc, char *argv[]) {
	float_bits fbits;
	sscanf(argv[1], "%f", (float *)&fbits);


	float *f = (float*)&fbits;

	printf("%e\n", *f);
}
