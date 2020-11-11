/*
*   Lab 8
*   Logan Lipke CISS 247 Fall
*   11/10/20
*/

int main()
{
    int a = 0x13;
    int b = 0x22;
    int c = 0xc;
    return a + a + a + (b << 2) + c + c;
}