# SPDX-License-Identifier: MIT
find_package(cmocka_mocks 0.54.2 REQUIRED)

create_unit_test(
  NAME
    test_common_safuJsonGetObject_utest
  SOURCES
    case_success_array.c
    case_success_object.c
    case_err_array.c
    case_err_object.c
    case_err_null_key_object.c
    case_err_string_index_array.c
    safuJsonGetObject_utest.c
  LIBRARIES
    safu_static
    cmocka_mocks::mock_jsonc
)
