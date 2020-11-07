/*
 * Lab1.c
 * CISS 247, Lab asssignment 2 11/6/20
 * 
 * Logan Lipke
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LEN 40
#define MAX_WORDS 110000
char wordlist[MAX_WORDS][MAX_WORD_LEN];

char* toLower(char *word);
int getHamming(char *word, char *word2);


int main(int argc, char *argv[])
{
    char word[MAX_WORD_LEN];
    FILE *input = fopen(argv[1], "r");
    int i = 0;
    
    fgets(word, MAX_WORD_LEN, stdin);

    while (fgets(wordlist[i], MAX_WORD_LEN, (FILE *)input))
        i++;  
}


char* toLower(char *word)
{
    char output[MAX_WORD_LEN];
    
}

int getHamming(char *word, char *word2)
{

}