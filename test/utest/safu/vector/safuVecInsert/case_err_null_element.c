// SPDX-License-Identifier: MIT
#include "safu/vector.h"
#include "safuVecInsert_utest.h"
#include "vector_utest.h"

void safuTestSafuVecInsertErrNullElement(UNUSED void **state) {
    safuVec_t vector = {0};

    safuVecCreate(&vector, 42, sizeof(safuTdata_t));
    assert_int_equal(-1, safuVecInsert(&vector, 0, NULL));
    assert_int_equal(-1, safuVecInsert(&vector, 20, NULL));
    assert_int_equal(-1, safuVecInsert(&vector, 41, NULL));
    safuVecFree(&vector);
}
