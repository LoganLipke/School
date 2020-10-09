/*
 * Lab1.c
 * CISS 247, Lab asssignment 1, Fall, 2020
 * 
 * Logan Lipke
 */

#include <stdio.h>

void get_keys (char *twokeys, unsigned *key1, unsigned *key2);
unsigned int get_n_bits (unsigned bits, int width, int index);	
unsigned int rotate_left3(unsigned bits);
void shuffle_nibbles (unsigned *bits);
void decode_28bits (unsigned cipher, char *plain, unsigned key1, unsigned key2);

int main (int argc, char *argv[])
{
    char line[8];
    unsigned int bits;

    while (fgets(line, 8, stdin))
    {
        sscanf(line, "%x", &bits);
        printf("%x", bits);
    }
    return 0;
}


void get_keys (char *twokeys, unsigned *key1, unsigned *key2)
{
	//extracts two 28-bit keys from 4 bytes
    return;
}

unsigned int get_n_bits (unsigned bits, int width, int index)
{    
    /*
    * returns the integer value of a specified subsequence of 32 bits
    * width is the number of bits to be extracted
    * index * width is the index of the rightmost bit to extract
    */
   return 0;
}   

unsigned int rotate_left3(unsigned bits)
{    
    // given a sequence of 7 bits, rotate 3 bits to the left
    return 0;
}

void shuffle_nibbles (unsigned *bits)
{	
    //shuffle the 7 nibbles according to the pattern
}

void decode_28bits (unsigned cipher, char *plain, unsigned key1, unsigned key2)
{
    return;
}
