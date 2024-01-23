// SPDX-License-Identifier: MIT
#ifndef SAFU_TIME_H
#define SAFU_TIME_H

#include <time.h>

#include "common.h"

__BEGIN_DECLS

safuResultE_t safuTimeGetLocalTime(struct tm *localTime);

char *safuGetCurrentDateString(char *dateFormat);

__END_DECLS

#endif
