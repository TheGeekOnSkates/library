#ifndef _FORMAT_STRING_H_
#define _FORMAT_STRING_H_

#include <ctype.h>

/**
 * Converts a string to uppercase (i.e. "GEEKY C")
 * @param[in] The string (changes will be made to this variable)
*/
void uppercase(char *str) {
    for(int i = 0; str[i]; i++)
        str[i] = toupper(str[i]);
}

/**
 * Converts a string to lowercase (i.e. "geeky c")
 * @param[in] The string (changes will be made to this variable)
*/
void lowercase(char *str) {
    for(int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
    return;
}

/**
 * Converts a string to "title case" (i.e. "Geeky C")
 * @param[in] The string (changes will be made to this variable)
*/
void titlecase(char *str) {
    for(int i = 0; str[i]; i++)
        if (i == 0 || str[i - 1] == ' ')
            str[i] = toupper(str[i]);
        else str[i] = tolower(str[i]);
}

#endif
