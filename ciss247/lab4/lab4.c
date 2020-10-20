/*
*   Lab 4
*   Logan Lipke CISS 247 Fall
*   10/19/20
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Operation
{
    int memAddr;
    char *op;
    char *dest, *src1, *src2;
};

struct Memory
{
    int memAddr;
    int value;
};

enum registers{X1, X2, X3, X4, X5, X6, X7, X8, X9, X10};
int regArray[10];

void parseFile(char* fileName, int *opCount, int *memCount, struct Operation opStorage[50], struct Memory memoryStorage[50]);
void ADD(struct Operation);
void ADDI(struct Operation);
void SUB(struct Operation);
void LDUR(struct Operation);
void STUR(struct Operation);
int B(struct Operation);
int CBZ(struct Operation);

struct Memory memoryStorage[50];
struct Operation opStorage[50];


int main(int argc, char* argv[])
{
    char *filename = "code.txt";
    int opCount = 0;
    int memCount = 0;

    parseFile(filename, &opCount, &memCount, opStorage, memoryStorage);
    for (int i = 0; i < opCount; i++)
    {
        printf("%d %s %s %s %s\n", opStorage[i].memAddr, opStorage[i].op, opStorage[i].dest, opStorage[i].src1, opStorage[i].src2);
    }

    for (int i = 0; i < memCount; i++)
    {
        printf("%d %d\n", memoryStorage[i].memAddr, memoryStorage[i].value);
    }
    return 0;
}


void parseFile(char* fileName, int *opCount, int *memCount, struct Operation opStorage[50], struct Memory memoryStorage[50])
{
    char buff[255];
    FILE *fp = fopen(fileName, "r");
    while (fgets(buff, 50, (FILE *)fp))
    {
        int memAddr = 0;
        char op[10];
        char dest[10], src1[10], src2[10];
        sscanf(buff, "%d %s %s %s %s", &memAddr, op, dest, src1, src2);
        if (memAddr >= 200)
        {
            // printf("%s\n", buff);
            opStorage[*opCount].memAddr = memAddr;
            opStorage[*opCount].op = op;
            opStorage[*opCount].dest = dest;
            opStorage[*opCount].src1 = src1;
            opStorage[*opCount].src2 = src2;
            *opCount += 1;
        }
        else
        {
            memoryStorage[*memCount].memAddr = memAddr;
            memoryStorage[*memCount].value = atoi(op);
            *memCount += 1;
        }
        
    }
    fclose(fp);
}

void ADD(struct Operation op)
{

}

void ADDI(struct Operation op)
{

}

void SUB(struct Operation op)
{

}

void LDUR(struct Operation op)
{

}

void STUR(struct Operation op)
{

}

int B(struct Operation op)
{

}

int CBZ(struct Operation op)
{

}