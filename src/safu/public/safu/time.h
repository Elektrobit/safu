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
 * Return:
 *   the result of the comparison
 *     - 1 if a is more recent than b
 *     - 0 if a and be are the same
 *     - -1 if a is older than b
 ******************************************************************/
int safuTimeSpecCompare(struct timespec a, struct timespec b);

__END_DECLS

#endif
