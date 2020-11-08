/*
 * Lab1.c
 * CISS 247, Lab asssignment 2 11/6/20
 * 
 * Logan Lipke
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 40
#define MAX_WORDS 110000
char wordlist[MAX_WORDS][MAX_WORD_LEN];

void toLower(char *word);
int getHamming(char *word, char *word2);
int isVowel(char c);
void getWord(char *word);
int checkSubstring(char* word, char*word2);


int main(int argc, char *argv[])
{
    char word[MAX_WORD_LEN];
    FILE *input = fopen(argv[1], "r");
    int i = 0;
    
    if (argc != 2)
    {
        puts("Please supply a filename");
        puts("Ex: ./assgn2 wordsEn.txt");
        exit(1);
    }

    while (fgets(wordlist[i], MAX_WORD_LEN, (FILE *)input))
    {
        char test[MAX_WORD_LEN];
        sscanf(wordlist[i], "%s\n", test);
        toLower(test);
        strcpy(wordlist[i], test);
        i++;
    }

    getWord(word);
    while (strlen(word) > 1)
    {            
        int wordCount = 0;
        int subCount = 0;
        int minHamming = 100;
        char closest[MAX_WORD_LEN];
        printf("Your word: \n\t%s\n", word);
        for (int j = 0; j < i; j++)
        {
            if ((getHamming(word, wordlist[j]) < minHamming) && (strlen(word) == strlen(wordlist[j]))) // Gets lowest hamming score to find closest word
            {
                minHamming = getHamming(word, wordlist[j]);
                strcpy(closest, wordlist[j]);
            }
            
            if ((wordCount < 5) && (strlen(word) == strlen(wordlist[j])) && (getHamming(word, wordlist[j]) <= 4) && (strcmp(word, wordlist[j]) != 0))
            {   // Finds 5 alternatives to chosen word
                if (wordCount == 0)
                    printf("Potential alternatives: \n");
                wordCount++;
                printf("HD: %d\t%s \n", getHamming(word, wordlist[j]), wordlist[j]);
            }
        }
        for (int j = 0; j < i; j++)
        {
            if ((subCount < 5) && (checkSubstring(closest, wordlist[j])))
            {
                if (subCount == 0)
                    printf("\nWord found in: \n");
                subCount++;
                printf("\t%s \n", wordlist[j]);
            }
        }
        printf("\nClosest word found : \nHD: %d\t%s\n", minHamming, closest);
        getWord(word);
    }
}

void toLower(char *word)
{   // Changes given word to lowercase
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
            word[i] = word[i] + 32;

        if (word[i] == '\n')
            word[i] = '\0';
    }
}

int getHamming(char *word, char *word2)
{   // Determines Hamming Distance for two words
    int hamming = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] != word2[i])
        {
            if (i == 0 && (word[i] != word2[i])) // Gives lower score to words starting with the same letter
                hamming += 5;

            if (word[i] - word2[i] > 10 || word2[i] - word[i] > 10) // Gives lower score to words whose letters are closer in the alphabet
                hamming += 3;

            if ((isVowel(word[i]) && isVowel(word2[i])) || (!isVowel(word[i]) && !isVowel(word2[i]))) // Gives lower score to letters that are both consonants or vowels
                hamming++;
            else
                hamming += 2;
        }
    }
    return hamming;
}

void getWord(char *word)
{   // Gets input as word
    printf("Word to check: ");
    fgets(word, MAX_WORD_LEN, stdin);
    toLower(word);
}

int isVowel(char c)
{
    // Checks if a character is a vowel
    const char *vowels = "aeiou";
    for (int i = 0; i < 5; i++)
        if (c == vowels[i])
            return 1;
    return 0;
}

int checkSubstring(char *word, char *word2)
{   
    // Checks for the existence of word in word2; rest exists in resting or forest, if found will return 1
    int wordLen = strlen(word);
    int word2Len = strlen(word2);
    int count = 0;
    if (wordLen < word2Len && wordLen > 2)
        for (int i=0; i < word2Len - wordLen; i++)
        {
            for (int j=0; j < wordLen; j++)
            {
                if (word[j] == word2[i+j])
                    count++;
                else
                    count = 0;
            }
            if (count == wordLen)
                return 1;
        }
    return 0;
}                    