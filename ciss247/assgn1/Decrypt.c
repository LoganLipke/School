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
void char_convert(char *cleartext, int *count, unsigned bits);

int main (int argc, char *argv[])
{
    char line[8];
    unsigned int bits;
    unsigned key1, key2;
    int *count = 0;
    char *cleartext;
    // Step 1 Convert to integer
    if (argc == 2)
        get_keys(argv[1], &key1, &key2);
    else
    {
        puts("Correct usage: ./decrypt {key} < {ciphertext}");
        exit(1);
    }
    while (fgets(line, 8, stdin))
    {
        // printf("Keys: %x %x\n", key1, key2);
        sscanf(line, "%x", &bits);
        // printf("Unmodified bits: %x\n", bits);
        // Step 2 XOR with key2
        bits ^= key2;
        // printf("XORed w/ Key2: %x\n", bits);
        // Step 3 Shuffle nibbles
        shuffle_nibbles(&bits);
        // printf("Shuffled: %x\n", bits);
        // Step 4 XOR with key1
        bits ^= key1;
        // printf("XORed w/ Key1: %x\n", bits);
        // Rotate each septet left 3
        bits = rotate_left3(bits);
        // printf("Rotated: %x\n", bits);
        // Convert septets to chars
        char_convert(&cleartext, &count, bits);
    }

    printf("%c\n", cleartext[0]);
    return 0;
}


void get_keys (char *twokeys, unsigned *key1, unsigned *key2)
{
	//extracts two 28-bit keys from 4 bytes
    unsigned int temp1 = 0;
    unsigned int temp2 = 0;
    for (int i = 0; i < 8; i++)
    {
        if (i < 4)
            temp1 |= twokeys[i] << 7 * (3-i);
        else
            temp2 |= twokeys[i] << 7 * (7-i);
    }
    *key1 = temp1;
    *key2 = temp2;
} 

unsigned int rotate_left3(unsigned bits)
{    
    // given a sequence of 7 bits, rotate 3 bits to the left
    unsigned rotBits = 0; 
    unsigned bitHolder = 0;
    unsigned topBits = 0;

    // Rotate nibble 3
    bitHolder = ((bits & 0xfe00000) >> 21);
    topBits = ((bitHolder | 0x80) & 0xf0) >> 4;
    bitHolder &= 0x0f;
    bitHolder <<= 4;
    bitHolder = (bitHolder | ((topBits & 0x7) << 1)) >> 1;
    rotBits |= bitHolder << 21;

    // Rotate nibble 2
    bitHolder = (bits & 0x1fc000) >> 14;
    topBits = ((bitHolder | 0x80) & 0xf0) >> 4;
    bitHolder &= 0x0f;
    bitHolder <<= 4;
    bitHolder = (bitHolder | ((topBits & 0x7) << 1)) >> 1;
    rotBits |= bitHolder << 14;
    
    // Rotate nibble 1
    bitHolder = ((bits & 0x3f80) >> 7);
    topBits = ((bitHolder | 0x80) & 0xf0) >> 4;
    bitHolder &= 0x0f;
    bitHolder <<= 4;
    bitHolder = (bitHolder | ((topBits & 0x7) << 1)) >> 1;
    rotBits |= bitHolder << 7;

    // Rotate nibble 0
    bitHolder = ((bits & 0x7f));
    topBits = ((bitHolder | 0x80) & 0xf0) >> 4;
    bitHolder &= 0x0f;
    bitHolder <<= 4;
    bitHolder = (bitHolder | ((topBits & 0x7) << 1)) >> 1;
    rotBits |= bitHolder;

    return rotBits;
}

void shuffle_nibbles (unsigned *bits)
{	
    //shuffle the 7 nibbles according to the pattern
    // printf("%x\n", bits);
    unsigned temp = *bits;
    unsigned temp2 = 0;
    temp2 |= (temp & 0x000000f) << 24; // Shuffle nibble 0 to nibble 6
    temp2 |= (temp & 0x00000f0) << 16; // Shuffle nibble 1 to nibble 5
    temp2 |= (temp & 0x0000f00) << 8;  // Shuffle nibble 2 to nibble 4
    temp2 |= (temp & 0x000f000) >> 12; // Shuffle nibble 3 to nibble 0
    temp2 |= (temp & 0x00f0000) >> 8;  // Shuffle nibble 4 to nibble 2
    temp2 |= (temp & 0x0f00000) >> 16; // Shuffle nibble 5 to nibble 1
    temp2 |= (temp & 0xf000000) >> 12; // Shuffle nibble 6 to nibble 3
    *bits = temp2;// >> 4;
}

void char_convert(char *cleartext, int *count, unsigned bits)
{
    char tempChar;
    int spaceCount = 0;

    tempChar = (bits & 0xfe00000) >> 21;
    if (tempChar == 0x20 )
        spaceCount++;
    if (spaceCount > 2)
    {
        printf("Spaces: %d\n", spaceCount);
        cleartext[*count] = '\0';
        return;
    }
    cleartext[*count] = tempChar;
    *count += 1;

    tempChar = (bits & 0x1fc000) >> 14;
    if (tempChar == 0x20 )
        spaceCount++;
    if (spaceCount > 2)
    {
        printf("%d\n", *count);
        cleartext[*count] = '\0';
        return;
    }
    cleartext[*count] = tempChar;
    *count += 1;


    tempChar = (bits & 0x3f80) >> 7;
    if (tempChar == 0x20 )
        spaceCount++;
    if (spaceCount > 2)
    {
        printf("%d\n", *count);
        cleartext[*count] = '\0';
        return;
    }
    cleartext[*count] = tempChar;
    *count += 1;
    
    tempChar = (bits & 0x7f);
    if (tempChar == 0x20 )
        spaceCount++;
    if (spaceCount > 2)
    {
        printf("%d\n", *count);
        cleartext[*count] = '\0';
        return;
    }
    cleartext[*count] = tempChar;
    *count += 1;
    

    // printf("Spaces: %d\n", spaceCount);
}
