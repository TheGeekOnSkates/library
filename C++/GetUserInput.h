#ifndef _GET_USER_INPUT
#define _GET_USER_INPUT

#include <stdio.h>
#include <stdlib.h>

char *GetUserInput() {
    char *str;
    int ch;
    size_t len = 0;
    size_t size = 10;
    str = realloc(NULL, sizeof(char) * size);
    if(!str) return str;
    while(EOF != (ch = fgetc(stdin)) && ch != '\n'){
        str[len++] = ch;
        if(len == size) {
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++] = '\0';
    return realloc(str, sizeof(char)*len);
}

#endif
