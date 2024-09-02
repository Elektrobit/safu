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
 * Result:
 *   value (int *):
 *     the result of the comparison
 *       - 1 if a is more recent than b
 *       - 0 if a and be are the same
 *       - -1 if a is older than b
 *
 * Return:
 *  - SAFU_RESTULT_OK successful comparison,
 *  - SAFU_RESULT_FAILED one of the timestamps was a NULL pointer
 ******************************************************************/
safuResultE_t safuTimeSpecCompare(struct timespec const *a, struct timespec const *b, int *value);

__END_DECLS

#endif
