#include <windows.h>
#include <stdio.h>
#include <string>

#ifndef SINGLE_INSTANCE_H
#define SINGLE_INSTANCE_H

#define PROGRAM_ALREADY_RUNNING 1

/**
 * Similar to #SingleInstance in AHK
 */
class SingleInstance
{
public:
    static bool AlreadyRunning;
    static HANDLE Handle;
    static void Start(std::string appName)
    {
        SingleInstance::Handle = CreateMutex(NULL, TRUE, appName.c_str());
        if (ERROR_ALREADY_EXISTS == GetLastError())
            exit(PROGRAM_ALREADY_RUNNING);
    }
    static void Finish()
    {
        ReleaseMutex(SingleInstance::Handle);   // Explicitly release mutex
        CloseHandle(SingleInstance::Handle);    // close handle before terminating
    }
};

// Define static properties to prevent Whiney Compiler issues :P
bool SingleInstance::AlreadyRunning = false;
HANDLE SingleInstance::Handle = NULL;

#endif
