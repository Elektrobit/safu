// SPDX-License-Identifier: MIT
#include "safuBase64Encode_utest.h"

int main() {
    const struct CMUnitTest tests[] = {
        TEST_CASE(safuTestSafuBase64EncodeSuccessStringEncoded),
        TEST_CASE(safuTestSafuBase64EncodeError),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
