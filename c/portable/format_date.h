#ifndef _FORMAT_H_
#define _FORMAT_H_

#include <time.h>

#define DATE_FORMAT_DB_DATE         0   // 2020-01-05 (as used for the "DATE" type in *SQL* databases)
#define DATE_FORMAT_DB_TIMESTAMP    1   // 2020-01-05 13:00:00 (as used for the "TIMESTAMP" type in *SQL* databases)
#define DATE_FORMAT_US_SHORT        2   // 1/5/20
#define DATE_FORMAT_US_FULL         3   // 01/05/2020

/**
 * Creates a formatted date string
 * @param[in] A numeric timestamp
 * @param[in] One of the format constants defined above
 * @return The formatted string, or NULL if something goes wrong.
 * @remarks The returned string is allocated on teh heap, so you'll
 *      have to free it when you're done.
 * @todo Add some more formats.  Times (without dates), long strings
 *      like the one returned by ctime, etc.  Another idea I had was
 *      to add custom formatting (like PHP, C# and others have), but
 *      that would probably be a separate function or an overload.
 *      When coding in those other languages, I've always found I
 *      want the same 4-5 formats all the time, so this works for now.
 */
char *format_date(time_t timestamp, unsigned char format) {
    struct tm *date = localtime(&timestamp);
    if (format == DATE_FORMAT_DB_DATE) {
        char *buffer = malloc(11);
        if (buffer == NULL) return NULL;
        memset(buffer, 0, 11);
        snprintf(buffer, 11, "%d-%02d-%02d", date->tm_year + 1900, date->tm_mon, date->tm_mday);
        return buffer;
    }
    if (format == DATE_FORMAT_DB_TIMESTAMP) {
        char *buffer = malloc(20);
        if (buffer == NULL) return NULL;
        memset(buffer, 0, 20);
        snprintf(buffer, 20, "%d-%02d-%02d %02d:%02d:%02d", date->tm_year + 1900, date->tm_mon, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec);
        return buffer;
    }
    if (format == DATE_FORMAT_US_SHORT) {
        char *buffer = malloc(11);
        if (buffer == NULL) return NULL;
        memset(buffer, 0, 11);
        int year = date->tm_year;
        while(year > 100) year -= 100;
        snprintf(buffer, 11, "%d/%d/%d", date->tm_mon, date->tm_mday, year);
        return buffer;
    }
    if (format == DATE_FORMAT_US_FULL) {
        char *buffer = malloc(11);
        if (buffer == NULL) return NULL;
        memset(buffer, 0, 11);
        snprintf(buffer, 11, "%02d/%02d/%d", date->tm_mon, date->tm_mday, date->tm_year + 1900);
        return buffer;
    }
    return NULL;
}

#endif
