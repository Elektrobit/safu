# SPDX-License-Identifier: MIT
find_package(cmocka_mocks 0.54.2 REQUIRED)

create_unit_test(
  NAME
  test_common_safuStringIsEmpty_utest
  SOURCES
    case_success_string_is_empty.c
    case_success_string_is_not_empty.c
    safuStringIsEmpty_utest.c
  LIBRARIES
    safu_static
    cmocka_mocks::mock_libc
)
