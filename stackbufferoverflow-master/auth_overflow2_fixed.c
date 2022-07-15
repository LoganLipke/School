#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Random function goes here
int isint(char s[]) {
    int i = 0, kezd;
    while(s[i] == ' ' || s[i] == '\n' || s[i] == '\t') ++i;
    if(s[i] == '+' || s[i] == '-') ++i;
    kezd = i;
    while(s[i] >= '0' && s[i] <= '9' && i - kezd < 255) ++i;
    if(kezd == i || (s[i] != '\n' && s[i] != '\t' && s[i] != ' ' && s[i] != 0)) return 0;
    else return 1;
}

int check_authentication(char *password) {
 char password_buffer[16];

 strncpy(password_buffer, password, 15);

 if(strcmp(password_buffer, "michael") == 0)
 return 1;
 else if(strcmp(password_buffer, "tsikerdekis") == 0)
 return 1;
 else
 return 0;
}

int main(int argc, char *argv[]) {
 if(argc < 2) {
 printf("Usage: %s <password>\n", argv[0]);
 exit(0);
 }
 if(check_authentication(argv[1])) {
 printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
 printf(" Access Granted.\n");
 printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
 } else {
 printf("\nAccess Denied.\n");
 }
}
