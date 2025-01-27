// SPDX-License-Identifier: MIT

#include "cmocka_mocks/mock_libc.h"
#include "safuAllocMem_utest.h"

void safuTestSafuAllocMemExterrRealloc(UNUSED void **state) {
    void *oldptr = (void *)0xdeadbeef, *newptr;
    const size_t newlen = 123;

    TEST("safuAllocMem");
    SHOULD("%s", "receive error while reallocating memory");

    MOCK_FUNC_AFTER_CALL(realloc, 0);
    expect_value(__wrap_realloc, ptr, oldptr);
    expect_value(__wrap_realloc, newSize, newlen);
    will_return(__wrap_realloc, NULL);

    MOCK_FUNC_AFTER_CALL(free, 0);
    expect_value(__wrap_free, ptr, oldptr);

    newptr = safuAllocMem(oldptr, newlen);

    assert_null(newptr);
}
