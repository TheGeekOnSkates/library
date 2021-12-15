#ifndef _wait_
#define _wait_
#ifdef _WIN32

#include <Windows.h>

// Makes the current thread wait for x milliseconds
void wait(unsigned int x)
{
	Sleep(x);
}

#else

#include <unistd.h>

// Makes the current thread wait for x milliseconds
void wait(unsigned int x)
{
	sleep(x);
}

#endif // _WIN32
#endif // !_wait_
