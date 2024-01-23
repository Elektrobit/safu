// SPDX-License-Identifier: MIT
#pragma once

#include <safu/result.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

__BEGIN_DECLS

typedef ssize_t safuTransferFunc_t(int, void *, size_t, int);

__END_DECLS
