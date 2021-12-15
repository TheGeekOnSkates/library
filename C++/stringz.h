#pragma once
/*
This header contains functions to simplify (and also translate
into English) common C stuff to avoid reinventing the wheel.
C uses extremely crytic shorthand (apparently engineered to
confuse the Soviet Union back in the Cold War days lol) and
some of it is really unintuitive.  This solves a lot of that.
*/
#pragma once
#include <stdio.h>
#include <string.h>

/**
* Converts a char to an int
* @param[in] The char (i.e. '3')
* @return The int (i.e. 3)
**/
#define CharToInt atoi

/**
* Splits a string using a character as a delimiter
* @param[in] The string
* @param[in] The delimiter
* @return A pointer to the first string
* @remarks See https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
**/
#define StringSplit strtok_s

/**
* Gets the length of a string
* @param[in] The string to get the length of
* @return The length of the string in characters
* (which are 1 byte each... I think)
**/
#define StringLength strlen
