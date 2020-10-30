/*
*   Lab 4
*   Logan Lipke CISS 247 Fall
*   10/19/20
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 50
#define STACK_SIZE 100
#define NUM_FIELDS 5
#define SIZE_FIELDS 6


char memory[MAX_LINES+STACK_SIZE][NUM_FIELDS][SIZE_FIELDS];
int pc = 200;
int regArray[32];
char *ptr;

void parseFile(char* fileName, int *opCount, int *memCount);
void ADD(char * dest, char * src1, char * src2);
void ADDI(char * dest, char * src1, char * src2);
void SUB(char * dest, char * src1, char * src2);
void SUBI(char * dest, char * src1, char * src2);
void LDUR(char * dest, char * src1, char * src2);
void STUR(char * dest, char * src1, char * src2);
void B(char * dest);
void BL(char * dest);
void BR(char * dest);
void CBZ(char * dest, char * src1);
int convertSrc(char *src1, char *src2);
int convertIntermed(char *intermed);
int convertReg(char *reg);

int main(int argc, char* argv[])
{
    regArray[31] = 0;
    regArray[28] = (MAX_LINES+STACK_SIZE-1) * 8;
    char *filename = "code.txt";
    int opCount = 0;
    int memCount = 0;
    if (argc == 2)
        filename = argv[1];

    parseFile(filename, &opCount, &memCount);
    int i = memCount;
    while (pc < (4 * opCount) + 200 && pc != 0)
    {
        i = ((pc - 200) /4) + memCount;
        if (strcmp(memory[i][1], "ADD") == 0)
        {
            ADD(memory[i][2], memory[i][3], memory[i][4]);
            pc += 4;
        }
        else if (strcmp(memory[i][1], "ADDI") == 0)
        {
            ADDI(memory[i][2], memory[i][3], memory[i][4]);
            pc += 4;
        }
        else if (strcmp(memory[i][1], "SUB") == 0)
        {
            SUB(memory[i][2], memory[i][3], memory[i][4]);
            pc += 4;
        }
        else if (strcmp(memory[i][1], "SUBI") == 0)
        {
            SUBI(memory[i][2], memory[i][3], memory[i][4]);
            pc += 4;
        }
        else if (strcmp(memory[i][1], "LDUR") == 0)
        {
            LDUR(memory[i][2], memory[i][3], memory[i][4]);
            pc += 4;
        }
        else if (strcmp(memory[i][1], "STUR") == 0)
        {
            STUR(memory[i][2], memory[i][3], memory[i][4]);
            pc += 4;
        }
        else if (strcmp(memory[i][1], "B") == 0)
            B(memory[i][2]);
        else if (strcmp(memory[i][1], "BR") == 0)
            BR(memory[i][2]);
        else if (strcmp(memory[i][1], "BL") == 0)
            BL(memory[i][2]);
        else if (strcmp(memory[i][1], "CBZ") == 0)
            CBZ(memory[i][2], memory[i][3]);

        printf("INSTRUCTION: %s %s, %s, %s\n", memory[i][1], memory[i][2], memory[i][3], memory[i][4]);
        puts("Registers:");
        for (int i = 0; i < 32; i++)
            if (i == 28)
                printf("SP = %d ", regArray[i]);
            else if (i == 30)
                printf("LR = %d ", regArray[i]);
            else if (regArray[i] != 0)
                printf("X%d = %d ", i, regArray[i]);

        printf("PC = %d\n", pc);
        
        if (regArray[28]/8 < MAX_LINES|| regArray[28]/8 > MAX_LINES+STACK_SIZE)
        {
            puts("\nRan out of Stack Space/Stack Overflow\n");
            exit(1);
        }

        printf("Stack:\n");
        for (int i = MAX_LINES+STACK_SIZE-1; i >= regArray[28]/8; i--)
            if (memory[i][0] != NULL)
                printf("%d : %s\n", i*8, memory[i][1]);
        
        // printf("Hit enter for next instruction");
        // getchar();
    }
    // for (int i=0; i < MAX_LINES+STACK_SIZE; i++)
    //     printf("%d : %s %s, %s, %s\n", i, memory[i][1], memory[i][2], memory[i][3], memory[i][4]);
    return 0;
}

void parseFile(char* fileName, int *opCount, int *memCount)
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
        
        if (strtol(memAddr, &ptr, 10) >= 200)
            *opCount += 1;
        else
            *memCount += 1;
    }
    fclose(fp);
}

int convertReg(char *reg)
{   
    char tmp[5];
    if (reg[1] == 'Z')  // Returns the index of XZR
        return 31;
    else if (reg[0] == 'S') // Returns the index of SP
        return 28;
    else if (reg[0] == 'L') // Returns the index of LR
        return 30;
    else
        sscanf(reg, "X%s", tmp);
    return strtol(tmp, &ptr, 10);
}

int convertSrc(char *src1, char *src2)
{
    char tmp1[5], tmp2[5];
    int tmpNum1 = 0;
    int tmpNum2 = 0;
    sscanf(src1, "[%s", tmp1);
    sscanf(src2, "%[^]]", tmp2);

    tmpNum1 = convertReg(tmp1);
    tmpNum2 = convertIntermed(tmp2);
    if (tmpNum1 == 28)
        return (regArray[tmpNum1] + tmpNum2) / 8;
    else
        return regArray[tmpNum1] + tmpNum2;
}

int convertIntermed(char *intermed)
{
    char tmp[5];
    sscanf(intermed, "#%s", tmp);
    return strtol(tmp, &ptr, 10);
}

void ADD(char * dest, char * src1, char * src2)
{
    int destIndex = convertReg(dest);
    int src1Index = convertReg(src1);
    int src2Index = convertReg(src2);
    // printf("%d + %d = %d \n", regArray[src1Index], regArray[src2Index], regArray[src1Index] + regArray[src2Index]);
    regArray[destIndex] = regArray[src1Index] + regArray[src2Index];
}

void ADDI(char * dest, char * src1, char * src2)
{
    int destIndex = convertReg(dest);
    int src1Index = convertReg(src1);
    int src2Index = convertIntermed(src2);
    // printf("%d + %d = %d \n", regArray[src1Index], src2Index, regArray[src1Index] + src2Index);
    regArray[destIndex] = regArray[src1Index] + src2Index;
}

void SUB(char * dest, char * src1, char * src2)
{
    int destIndex = convertReg(dest);
    int src1Index = convertReg(src1);
    int src2Index = convertReg(src2);
    // printf("%d - %d = %d \n", regArray[src1Index], regArray[src2Index], regArray[src1Index] - regArray[src2Index]);
    regArray[destIndex] = regArray[src1Index] - regArray[src2Index];
}

void SUBI(char * dest, char * src1, char * src2)
{
    int destIndex = convertReg(dest);
    int src1Index = convertReg(src1);
    int src2Index = convertIntermed(src2);
    // printf("%d + %d = %d \n", regArray[src1Index], src2Index, regArray[src1Index] + src2Index);
    regArray[destIndex] = regArray[src1Index] - src2Index;
}

void LDUR(char * dest, char * src1, char * src2)
{
    int destIndex = convertReg(dest);
    int srcIndex = convertSrc(src1, src2);
    // printf("Setting %s to %ld\n", dest, strtol(memory[(srcIndex - 100) / 4][1], &ptr, 10));
    if (strcmp(src1, "[SP") != 0)
        regArray[destIndex] = strtol(memory[(srcIndex - 100) / 4][1], &ptr, 10);
    else
        regArray[destIndex] = strtol(memory[srcIndex][1], &ptr, 10);
}

void STUR(char * dest, char * src1, char * src2)
{
    int destIndex = convertReg(dest);
    int srcIndex = convertSrc(src1, src2);
    char tmp[SIZE_FIELDS];
    sprintf(tmp, "%d\n", regArray[destIndex]);
    
    if (strcmp(src1, "[SP") != 0)
        strcpy(memory[(srcIndex - 100) / 4][1], tmp);
    else
        strcpy(memory[srcIndex][1], tmp);
}

void B(char * dest) 
{
    pc = strtol(dest, &ptr, 10);
    // printf("Branching to %d\n", pc);   
}

void BR(char * dest) 
{
    int destIndex = convertReg(dest);
    pc = regArray[destIndex];
    // printf("Branching to %d\n", pc);   
}

void BL(char * dest) 
{
    regArray[convertReg("LR")] = pc+4;
    pc = strtol(dest, &ptr, 10);
    // printf("Branching to %d\n", pc);   
}

void CBZ(char * dest, char * src1)
{
    int destIndex = convertReg(dest);
    if (regArray[destIndex] == 0)
        pc = strtol(src1, &ptr, 10);
    else
        pc += 4;
    // printf("Branching to %d\n", pc);
}