/*
*   Lab3
*   Logan Lipke CISS 247 Fall
*   10/15/20
*/

#include <stdio.h>

int func1(int x, int y); // Computes the bit-wise AND of two integers, using only the ~ and |
int func2(int x, int y); // Computes the bit-wise exclusive-or of two integers, using only the ~ and & operators
int func3(int x); // Returns 1 if any odd-numbered bit in an integer is set to 1, and 0 otherwise
int func4(int x); // Returns 1 if all the odd-numbered bits in an integer are set to 1, and 0 otherwise
int func5(int highbit, int lowbit); // Returns a bit-mask with all 1's between lowbit and highbit, inclusive
int func6(int x, int m, int n); // swaps the mth byte and the nth byte of an integer

int main()
{
    printf("func1(5,6) should return %x. Result = %x \n", func1(5,6), 5 & 6);

    printf("func2(4,5) should return %x. Result = %x \n", func2(4,5), 4 ^ 5);

    printf("func3(0x5) should return 0. Result = %x\n", func3(0x5));
    printf("func3(0x7) should return 1. Result = %x\n", func3(0x7));

    printf("func4(0xFFFFFFFD) should return 0. Result = %x\n", func4(0xFFFFFFFD));
    printf("func4(0xAAAAAAAA) should return 1. Result = %x\n", func4(0xAAAAAAAA));

    printf("func5(5,3) should return 56 (0x38). Result = %x\n", func5(5,3));

    printf("func6(0x12345678, 1, 3) should return 0x56341278. Result = %x\n", func6(0x12345678, 1, 3));
    printf("func6(0xDEADBEEF, 0, 2) should return 0xDEEFBEAD. Result = %x\n", func6(0xDEADBEEF, 0, 2));

    return 0;
}

int func1(int x, int y)
{
    // Computes the bit-wise AND of two integers, using only the ~ and |
    return ~((~x | ~y));
}

int func2(int x, int y)
{
    // Computes the bit-wise exclusive-or of two integers, using only the ~ and & operators
    return ~(~(~x & y) & ~(x & ~y));
}

int func3(int x)
{
    // Returns 1 if any odd-numbered bit in an integer is set to 1, and 0 otherwise
    int tempBits = ((x >> 24) & 0xaa) | ((x >> 16) & 0xaa) | ((x >> 8) & 0xaa) | (x & 0xaa);
    return ((tempBits >> 1) & 1) | ((tempBits >> 3) & 1) | ((tempBits >> 5) & 1) | ((tempBits >> 7) & 1);
    return 0;
}

int func4(int x)
{
    // Returns 1 if all the odd-numbered bits in an integer are set to 1, and 0 otherwise
    int tempBits = ((x >> 24) & 0xaa) & ((x >> 16) & 0xaa) & ((x >> 8) & 0xaa) & (x & 0xaa);
    return ((tempBits >> 1) & 1) & ((tempBits >> 3) & 1) & ((tempBits >> 5) & 1) & ((tempBits >> 7) & 1);
}

int func5(int highbit, int lowbit)
{
    // Returns a bit-mask with all 1's between lowbit and highbit, inclusive
    return 0;
}

int func6(int x, int m, int n)
{
    // swaps the mth byte and the nth byte of an integer
    return 0;
}
