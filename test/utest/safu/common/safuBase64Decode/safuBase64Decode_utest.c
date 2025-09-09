// SPDX-License-Identifier: MIT
#include "safuBase64Decode_utest.h"

int main() {
    const struct CMUnitTest tests[] = {
        TEST_CASE(safuTestSafuBase64DecodeSuccessStringDecoded),
        TEST_CASE(safuTestSafuBase64DecodeError),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
