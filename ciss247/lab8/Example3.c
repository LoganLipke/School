/*
*   Lab 8
*   Logan Lipke CISS 247 Fall
*   11/10/20
*/

int main()
{
    int test[7] = {0x17, 0x13, 0xc, 0x2, 0x3, 0x1, 0x0};
    test[6] = (test[0] * test[3]) + (test[1] * test[4]) + (test[2] * test[5]);
    return 0;
}