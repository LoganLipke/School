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
    unsigned key1, key2;
    // Step 1 Convert to integer
    if (argc == 2)
        get_keys(argv[1], key1, key2);
    else
    {
        puts("Correct usage: ./decrypt {key} {ciphertext}");
        exit(1);
    }
    
    while (fgets(line, 8, stdin))
    {
        sscanf(line, "%x", &bits);
        shuffle_nibbles(&bits);
    }
    printf("\n%x %x\n", key1, key2);

    // Step 3 XOR with key2
    // Shuffle nibbles
    // XOR with key1
    // Rotate each septet left 3
    // Convert septets to chars

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
   return bits;
}   

unsigned int rotate_left3(unsigned bits)
{    
    // given a sequence of 7 bits, rotate 3 bits to the left
    
    return bits;
}

void shuffle_nibbles (unsigned *bits)
{	
    //shuffle the 7 nibbles according to the pattern
    printf("%x\n", *bits % 16);
}

void decode_28bits (unsigned cipher, char *plain, unsigned key1, unsigned key2)
{
    return;
}
