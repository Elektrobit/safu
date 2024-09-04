# SPDX-License-Identifier: MIT
find_package(cmocka_extensions 0.53.1 REQUIRED)

create_unit_test(
  NAME
  	 test_common_safuTimeSpecCompare_utest
  SOURCES
    case_selected.c
    case_exhaustive.c
    case_real_timestamps.c
    safuTimeSpecCompare_utest.c
  LIBRARIES
    safu_weak
)
