// SPDX-License-Identifier: MIT
#ifndef SAFU_TIME_H
#define SAFU_TIME_H

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

__END_DECLS

#endif
