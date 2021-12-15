#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Reads a line of text from standard input (stdin)
 * @param[out] The user's input will be stored here.
 * @param[in] The length of the string, in bytes
 * @remarks This basically wraps fgets, and strips
 * off the trailing newline character.
 * @todo Test this to make sure it works - I haven't
 * used it in years. :)'
 */
void ReadLine(char *buffer, size_t length) {
	size_t i;
	memset(buffer, 0, length);
	fgets(buffer, length, stdin);
	for (i=length - 2; i>=0; i--) {     /* start at length - 2, because - 1 would be the last character, which should always be zero ()a NULL-terminator)  */
		if (buffer[i] != '\n') continue;
		buffer[i] = 0;
		break;
	}
}
