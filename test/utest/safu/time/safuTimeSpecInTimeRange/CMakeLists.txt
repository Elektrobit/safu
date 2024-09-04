# SPDX-License-Identifier: MIT
find_package(cmocka_extensions 0.53.1 REQUIRED)

create_unit_test(
  NAME
    test_common_safuTimeSpecInTimeRange_utest
  SOURCES
    case_real_timestamps.c
    safuTimeSpecInTimeRange_utest.c
  LIBRARIES
    safu_weak
)
