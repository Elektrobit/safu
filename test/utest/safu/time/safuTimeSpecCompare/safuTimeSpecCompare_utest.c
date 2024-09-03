// SPDX-License-Identifier: MIT
#include "safuTimeSpecCompare_utest.h"

int main() {
    const struct CMUnitTest tests[] = {
        TEST_CASE(safuTestSafuTimeSpecCompareSuccess),
        TEST_CASE(safuTestSafuTimeSpecCompareErrorParameter),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
