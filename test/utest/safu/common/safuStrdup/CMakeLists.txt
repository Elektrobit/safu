# SPDX-License-Identifier: MIT
find_package(cmocka_mocks 0.54.2 REQUIRED)

create_unit_test(
  NAME
  test_common_safuStrdup_utest
  SOURCES
    case_err_input_null.c
    case_success_string_duplicated.c
    case_exterr_strdup.c
    safuStrdup_utest.c
  LIBRARIES
    mock_safu_static
    cmocka_mocks::mock_libc
)
