# SPDX-License-Identifier: MIT
include(weak_library.cmake)
include(static_from_shared.cmake)

set(SAFU_HARDWAREID_FILE "/etc/machine-id")
set(SAFU_HARDWAREID_MAX_LENGTH 2048)
set(SAFU_HARDWAREID_DEFAULT_VALUE "INVALID")
set(SAFU_HARDWAREID_ENVIRONMENT_PREFIX "SAFU_HARDWAREID_")

if (SAFU_LOG)
  target_compile_definitions(safu PRIVATE SAFU_LOG=1)
endif (SAFU_LOG)
set(SAFU_LOG_PREFIX "[SAFU] ")

add_subdirectory(safu)
