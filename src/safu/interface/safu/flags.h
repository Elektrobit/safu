// SPDX-License-Identifier: MIT
#pragma once

#ifdef __cplusplus
#include <atomic>
using std::atomic_uint;
#else
#include <stdatomic.h>
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * Common set of flags useful for managing component states.
 * The upper 16 bits (SAFU_FLAG_CUSTOM_MASK) will be kept free
 * and can be used for component specific custom values
 */
typedef atomic_uint safuFlags_t;

#define SAFU_FLAG_NONE             (0)
#define SAFU_FLAG_MASK             (0x0000FFFFU)
#define SAFU_FLAG_CUSTOM_MASK      (0xFFFF0000U)
#define SAFU_FLAG_CUSTOM_START_BIT (1 << 16)
#define SAFU_FLAG_INITIALIZED_BIT  (1 << 0)
#define SAFU_FLAG_ERROR_BIT        (1 << 1)
#define SAFU_FLAG_SHUTDOWN_BIT     (1 << 2)

#define SAFU_FLAG_CLEAR_ALL_BITS(__flag)      atomic_store(__flag, SAFU_FLAG_NONE)
#define SAFU_FLAG_HAS_INITIALIZED_BIT(__flag) ((atomic_load(__flag) & SAFU_FLAG_INITIALIZED_BIT) != 0)
#define SAFU_FLAG_HAS_ERROR_BIT(__flag)       ((atomic_load(__flag) & SAFU_FLAG_ERROR_BIT) != 0)
#define SAFU_FLAG_EXCHANGE_INITIALIZE_BIT(__flag) \
    ((atomic_fetch_or(__flag, SAFU_FLAG_INITIALIZED_BIT) & (SAFU_FLAG_INITIALIZED_BIT | SAFU_FLAG_SHUTDOWN_BIT)) == 0)
#define SAFU_FLAG_EXCHANGE_SHUTDOWN_BIT(__flag) \
    ((atomic_fetch_or(__flag, SAFU_FLAG_SHUTDOWN_BIT) & SAFU_FLAG_INITIALIZED_BIT) == 0)
