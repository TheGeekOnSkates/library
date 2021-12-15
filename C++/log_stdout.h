#include <windows.h>
#include <sstream>
#include <iostream>
#include <cstdio>

#pragma once

/**
 * Redirects standard output (stdout) to a log file with the current date (i.e. 2017-04-29.log)
 */
void log_stdout()
{
    // Get the system time
    SYSTEMTIME time;
    GetSystemTime(&time);

    // Format it like a date in an SQL database (YYYY-MM-DD)
    CreateDirectory("logs", NULL);
    std::stringstream ss;
    ss << "logs\\";
    ss << time.wYear;
    if (time.wMonth < 10)
        ss << "-0" << time.wMonth;
    else
        ss << "-" << time.wMonth;
    if (time.wDay < 10)
        ss << "-0" << time.wDay;
    else
        ss << "-" << time.wDay;
    ss << ".log";
    std::string temp = ss.str();
    freopen(temp.c_str(),"a",stdout);
}
