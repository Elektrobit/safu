# SPDX-License-Identifier: MIT
find_package(cmocka_mocks 0.54.2 REQUIRED)

create_unit_test(
  NAME
    test_common_safuJsonGetBool_utest
  SOURCES
    case_err_get_type_failed_array.c
    case_err_get_type_failed_object.c
    case_err_get_object_failed_array.c
    case_err_get_object_failed_object.c
    case_success_array.c
    case_success_object.c
    safuJsonGetBool_utest.c
  LIBRARIES
    safu_weak
    cmocka_mocks::mock_jsonc
)
