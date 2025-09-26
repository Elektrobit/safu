# SPDX-License-Identifier: MIT
find_package(cmocka_mocks 0.54.2 REQUIRED)

create_unit_test(
  NAME
  test_common_safuCheckBase64Encoding_utest
  SOURCES
    case_success.c
    case_error.c
    safuCheckBase64Encoding_utest.c
  LIBRARIES
    safu_static
)
