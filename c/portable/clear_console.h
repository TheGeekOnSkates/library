#ifndef _clear_console_
#define _clear_console_

#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#endif

// Clears the console
void clear_console()
{
#ifdef _WIN32
	system("cls");
#else
	// Assume POSIX
	system("clear");
#endif
}

#endif
