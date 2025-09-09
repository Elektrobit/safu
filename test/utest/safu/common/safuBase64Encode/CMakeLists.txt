# SPDX-License-Identifier: MIT
find_package(cmocka_mocks 0.54.2 REQUIRED)

create_unit_test(
  NAME
  test_common_safuBase64Encode_utest
  SOURCES
    case_success.c
    case_error.c
    safuBase64Encode_utest.c
  LIBRARIES
    safu_static
)
