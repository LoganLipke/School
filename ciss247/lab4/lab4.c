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
    char op[10];
    int dest;
    char src1[10], src2[10];
};

struct Memory
{
    int memAddr;
    int value1, value2, value3, value4;
};

enum Registers{X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, XZR=0};
int regArray[10];

void parseFile(char* fileName, int *opCount, int *memCount, struct Operation opStorage[50], struct Memory memoryStorage[50]);
void ADD(struct Operation *op);
void ADDI(struct Operation *op);
void SUB(struct Operation *op);
void LDUR(struct Operation *op);
void STUR(struct Operation *op);
int B(struct Operation *op);
int CBZ(struct Operation *op);
int convertReg(char *reg);

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
        // printf("%p + %lu\n", &opStorage[i], sizeof(opStorage[i]));
        printf("%d %s %d %s %s", opStorage[i].memAddr, opStorage[i].op, opStorage[i].dest, opStorage[i].src1, opStorage[i].src2);
    }

    // printf("%d %s \n%s \n%s \n%s\n", opStorage[1].memAddr, opStorage[1].op, opStorage[1].dest, opStorage[1].src1, opStorage[1].src2);
    puts("\n");
    for (int i = 0; i < memCount; i++)
    {
        printf("%d %d %d %d %d\n", memoryStorage[i].memAddr, memoryStorage[i].value1, memoryStorage[i].value2, memoryStorage[i].value3, memoryStorage[i].value4);
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
        sscanf(buff, "%d %s %[^,], %[^,], %[^,]", &memAddr, op, dest, src1, src2);
        if (memAddr >= 200)
        {
            // printf("%d %d %x %x %x %x\n", *opCount, memAddr, op, dest, src1, src2);
            opStorage[*opCount].memAddr = memAddr;
            strcpy(opStorage[*opCount].op, op);
            printf("TEST %s %d\n", dest, convertReg(dest));
            opStorage[*opCount].dest = convertReg(dest);
            strcpy(opStorage[*opCount].src1, src1);
            strcpy(opStorage[*opCount].src2, src2);
            *opCount += 1;
        }
        else
        {
            memoryStorage[*memCount].memAddr = memAddr;
            memoryStorage[*memCount].value1 = atoi(op);
            memoryStorage[*memCount].value2 = atoi(dest);
            memoryStorage[*memCount].value3 = atoi(src1);
            memoryStorage[*memCount].value4 = atoi(src2);
            *memCount += 1;
        }
        
    }
    fclose(fp);
}

int convertOp(char *reg) // TODO Change to convert ops to decimal values?
{   
    if (strcmp(reg, "X0") == 0)
        return X0;
    else if (strcmp(reg, "X1") == 0)
        return X1;
    else if (strcmp(reg, "X2") == 0)
        return X2;
    else if (strcmp(reg, "X3") == 0)
        return X3;
    else if (strcmp(reg, "X4") == 0)
        return X4;
    else if (strcmp(reg, "X5") == 0)
        return X5;
    else if (strcmp(reg, "X6") == 0)
        return X6;
    else if (strcmp(reg, "X7") == 0)
        return X7;
    else if (strcmp(reg, "X8") == 0)
        return X8;
    else if (strcmp(reg, "X9") == 0)
        return X9;
    else if (strcmp(reg, "X10") == 0)
        return X10;
    else if (strcmp(reg, "XZR") == 0)
        return XZR;
    else
        return -1;
}

void ADD(struct Operation *op)
{

}

void ADDI(struct Operation *op)
{

}

void SUB(struct Operation *op)
{

}

void LDUR(struct Operation *op)
{

}

void STUR(struct Operation *op)
{

}

int B(struct Operation *op)
{

}

int CBZ(struct Operation *op)
{

}