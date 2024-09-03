# SPDX-License-Identifier: MIT
find_package(cmocka_extensions 0.53.1 REQUIRED)

create_unit_test(
  NAME
  	 test_common_safuTimeSpecCompare_utest
  SOURCES
    case_success.c
    case_error_parameter.c
    safuTimeSpecCompare_utest.c
  LIBRARIES
    safu_weak
)
