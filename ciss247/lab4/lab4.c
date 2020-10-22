/*
*   Lab 4
*   Logan Lipke CISS 247 Fall
*   10/19/20
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 50
#define NUM_FIELDS 5
#define SIZE_FIELDS 6


char memory[MAX_LINES][NUM_FIELDS][SIZE_FIELDS];
int pc = 200;
enum Registers{XZR, X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10};
int regArray[12];

void parseFile(char* fileName, int *opCount, int *memCount, char memory[MAX_LINES][NUM_FIELDS][SIZE_FIELDS]);
void ADD(char * dest, char * src1, char * src2);
void ADDI(char * dest, char * src1, char * src2);
void SUB(char * dest, char * src1, char * src2);
void LDUR(char * dest, char * src1, char * src2);
void STUR(char * dest, char * src1, char * src2);
void B(char * dest, char * src1, char * src2);
void CBZ(char * dest, char * src1, char * src2);
int convertReg(char *reg);
int convertSrc(char *src1, char *src2);
int convertIntermed(char *intermed);
int convertOp(char *op);

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
        
        switch (convertOp(memory[i][1]))
        {
        case 1:
            ADD(memory[i][2], memory[i][3], memory[i][4]);
            break;
        case 2:
            ADDI(memory[i][2], memory[i][3], memory[i][4]);
            break;
        case 3:
            SUB(memory[i][2], memory[i][3], memory[i][4]);
            break;
        case 4:
            LDUR(memory[i][2], memory[i][3], memory[i][4]);
            convertSrc(memory[i][3], memory[i][4]);
            break;
        case 5:
            STUR(memory[i][2], memory[i][3], memory[i][4]);
            break;
        case 6:
            B(memory[i][2], memory[i][3], memory[i][4]);
            break;
        case 7:
            CBZ(memory[i][2], memory[i][3], memory[i][4]);
            break;
        }
        pc += 4;
    }

    printf("Ops: %d Mem: %d\n", opCount, memCount);
    return 0;
}


void parseFile(char* fileName, int *opCount, int *memCount, char memory[MAX_LINES][NUM_FIELDS][SIZE_FIELDS])
{
    char buff[255];
    FILE *fp = fopen(fileName, "r");
    while (fgets(buff, 50, (FILE *)fp))
    {
        char memAddr[SIZE_FIELDS];
        char op[SIZE_FIELDS];
        char dest[SIZE_FIELDS], src1[SIZE_FIELDS], src2[SIZE_FIELDS];
        sscanf(buff, "%s %s %[^,], %[^,], %s\n", memAddr, op, dest, src1, src2);

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

int convertSrc(char *src1, char *src2)
{
    char tmp1[5], tmp2[5];
    sscanf(src1, "[%s", tmp1);
    sscanf(src2, "%[^]]", tmp2);

    
}

int convertIntermed(char *intermed)
{
    char temp[5];
    sscanf(intermed, "#%s", temp);
    return atoi(temp);
}

int convertOp(char *op)
{
        if (strcmp(op, "ADD") == 0)
        return 1;
    else if (strcmp(op, "ADDI") == 0)
        return 2;
    else if (strcmp(op, "SUB") == 0)
        return 3;
    else if (strcmp(op, "LDUR") == 0)
        return 4;
    else if (strcmp(op, "STUR") == 0)
        return 5;
    else if (strcmp(op, "B") == 0)
        return 6;
    else if (strcmp(op, "CBZ") == 0)
        return 7;
}

void ADD(char * dest, char * src1, char * src2)
{
    return;
}

void ADDI(char * dest, char * src1, char * src2)
{
    return;
}

void SUB(char * dest, char * src1, char * src2)
{
    return;
}

void LDUR(char * dest, char * src1, char * src2)
{
    return;
}

void STUR(char * dest, char * src1, char * src2)
{
    return;
}

void B(char * dest, char * src1, char * src2)
{
    return;
}

void CBZ(char * dest, char * src1, char * src2)
{
    return;
}