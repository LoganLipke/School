/*
*   Assignment 3
*   Logan Lipke CISS 247 Fall
*   11/24/20
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayAllTop(char *numString, int negative);
void displayAllBot(char *numString, int negative);
void displayAllMid(char *numString, int negative);

void displayCharTop(char num);
void displayCharBot(char num);
void displayCharMid(char num);

//      _   _       _   _  _    _   _   _
//  |   _|  _| |_| |_  |_   |  |_| |_| | |
//  |  |_   _|   |  _| |_|  |  |_|  _| |_|

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (argv[1][0] == '-')
        {
            displayAllTop(argv[1], 1);
            displayAllMid(argv[1], 1);
            displayAllBot(argv[1], 1);
        }
        else
        {
            displayAllTop(argv[1], 0);
            displayAllMid(argv[1], 0);
            displayAllBot(argv[1], 0);
        }
        
    }
}


void displayAllTop(char *numString, int negative)
{
    int i = 0;
    if (negative)
    {
        printf(" ");
        i++;
    }
    for (;i < strlen(numString); i++)
    {
        displayCharTop(numString[i]);
    }
    printf("\n");
}

void displayAllBot(char *numString, int negative)
{
    int i = 0;
    if (negative)
    {
        printf(" ");
        i++;
    }
    for (;i < strlen(numString); i++)
    {
        displayCharBot(numString[i]);
    }
    printf("\n");
}

void displayAllMid(char *numString, int negative)
{
    int i = 0;
    if (negative)
    {
        printf("_");
        i++;
    }
    for (;i < strlen(numString); i++)
    {
        displayCharMid(numString[i]);
    }
    printf("\n");
}   


void displayCharTop(char num)
{
    switch (num)
    {
    case '1':
    case '4':
        printf("   ");
        break;
    default:
        printf(" _ ");
        break;
    }
    // printf("\n");
}

void displayCharBot(char num)
{
    switch (num)
    {
    case '1':
    case '7':
    case '4':
        printf("  |");
        break;
    case '6':
    case '8':
    case '0':
        printf("|_|");
        break;
    case '3':
    case '5':
    case '9':
        printf(" _|");
        break;
    default: // Handles 2
        printf("|_ ");
        break;
    }
}

void displayCharMid(char num)
{
    switch (num)
    {
    case '1':
    case '7':
        printf("  |");
        break;
    case '2':
    case '3':
        printf(" _|");
        break;
    case '5':
    case '6':
        printf("|_ ");
        break;
    case '0':
        printf("| |");
        break;
    default: // Handles 4,8,9
        printf("|_|");
        break;
    }
}