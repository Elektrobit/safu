// SPDX-License-Identifier: MIT
#ifndef SAFU_TIME_H
#define SAFU_TIME_H

#include <stdbool.h>
#include <time.h>

#include "common.h"

__BEGIN_DECLS

safuResultE_t safuTimeGetLocalTime(struct tm *localTime);

char *safuGetCurrentDateString(char *dateFormat);

/*******************************************************************
 * Function:     safuTimeSpecCompare
 *------------------------------------------------------------------
 * Description:  Compares two timespec timestamps
 *
 * Input:
 *   timeA (struct timespec):
 *     the first timestamp to compare 1 if this is bigger/newer
 *   timeB (struct timespec):
 *     the second timestamp to compare -1 if this is bigger/newer
 *
 * Return:
 *   the result of the comparison
 *     - 1 if timeA is more recent than timeB
 *     - 0 if timeA and timeB are the same
 *     - -1 if timeA is older than timeB
 ******************************************************************/
int safuTimeSpecCompare(struct timespec timeA, struct timespec timeB);

/*******************************************************************
 * Function:     safuTimeSpecInTimeRange
 *------------------------------------------------------------------
 * Description:  Checks if newestTime >= timeToCheck > olderTime
 *
 * Input:
 *   newestTime (struct timespec):
 *     the newest point in the time range to check for.
 *     ignored if it's {0,0}
 *   timeToCheck (struct timespec):
 *     the time stamp to check if it's in the time range
 *   olderTime (struct timespec):
 *     the timestamp delimiting the time range, older than everything inside the range
 *     ignored if it's {0,0}
 *
 * Return:
 *   true if newestTime >= timeToCheck > olderTime
 *   - if newestTime is {0,0}: true if timeToCheck > olderTime
 *   - if olderTime is {0,0}: true if newestTime >= timeToCheck
 *   - always true if newestTime and olderTime both are {0,0}
 ******************************************************************/
bool safuTimeSpecInTimeRange(struct timespec newestTime, struct timespec timeToCheck, struct timespec olderTime);

__END_DECLS

#endif
