/*
*   Lab 4
*   Logan Lipke CISS 247 Fall
*   10/19/20
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ADDR 50
#define NUM_FIELDS 5
#define SIZE_FIELDS 10


char memory[MAX_ADDR][NUM_FIELDS][SIZE_FIELDS];
int pc = 200;
enum Registers{X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, XZR=0};
int regArray[11];

void parseFile(char* fileName, int *opCount, int *memCount, char memory[MAX_ADDR][NUM_FIELDS][SIZE_FIELDS]);
// void ADD(struct Operation *op);
// void ADDI(struct Operation *op);
// void SUB(struct Operation *op);
// void LDUR(struct Operation *op);
// void STUR(struct Operation *op);
// int B(struct Operation *op);
// int CBZ(struct Operation *op);
int convertReg(char *reg);
int convertSrc(char *src1, char *src2);

int main(int argc, char* argv[])
{
    char *filename = "code.txt";
    int opCount = 0;
    int memCount = 0;

    parseFile(filename, &opCount, &memCount, memory);
    int i = memCount;
    while (pc < (4*opCount)+200)
    {
        i = ((pc - 200) /4) + memCount;
        printf("%d : %s %s, %s, %s\n", pc, memory[i][1], memory[i][2], memory[i][3], memory[i][4]);
        pc += 4;
    }

    printf("Ops: %d Mem: %d\n", opCount, memCount);
    return 0;
}


void parseFile(char* fileName, int *opCount, int *memCount, char memory[MAX_ADDR][NUM_FIELDS][SIZE_FIELDS])
{
    char buff[255];
    FILE *fp = fopen(fileName, "r");
    while (fgets(buff, 50, (FILE *)fp))
    {
        char memAddr[8];
        char op[8];
        char dest[8], src1[8], src2[8];
        sscanf(buff, "%s %s %[^,], %[^,], %s\n", memAddr, op, dest, src1, src2);
        
        // convertSrc(src1, src2);
        strcpy(memory[*opCount+*memCount][0], memAddr);
        strcpy(memory[*opCount+*memCount][1], op);
        strcpy(memory[*opCount+*memCount][2], dest);
        strcpy(memory[*opCount+*memCount][3], src1);
        strcpy(memory[*opCount+*memCount][4], src2);
        if (atoi(memAddr) >= 200)
            *opCount +=1;
        else
            *memCount += 1;
    }
    fclose(fp);
}

int convertReg(char *reg)
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

// int convertSrc(char *src1, char *src2)
// {
    
//     printf("TEST %s %s\n", src1, src2);
//     sscanf(src1, "", );
// }

// void ADD(struct Operation *op)
// {

// }

// void ADDI(struct Operation *op)
// {

// }

// void SUB(struct Operation *op)
// {

// }

// void LDUR(struct Operation *op)
// {

// }

// void STUR(struct Operation *op)
// {

// }

// int B(struct Operation *op)
// {

// }

// int CBZ(struct Operation *op)
// {

// }