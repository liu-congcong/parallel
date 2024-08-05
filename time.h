#ifndef __TIME_H__
#define __TIME_H__

#include <assert.h>
#include <stdio.h>
#include <time.h>

char *getTime(int type)
{
    time_t currentTime;
    char *timeString = malloc(sizeof(char) * 128);
    currentTime = time(NULL);
    assert(currentTime != -1);
    struct tm *localTime = localtime(&currentTime);
    assert(localTime);
    if (type == 1)
    {
        assert(strftime(timeString, 128, "%Y%m%d-%H%M%S", localTime));
    }
    if (type == 2)
    {
        assert(strftime(timeString, 128, "%Y/%m/%d %H:%M:%S", localTime));
    }
    return timeString;
}

#endif
