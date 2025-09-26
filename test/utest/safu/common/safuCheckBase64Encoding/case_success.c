// SPDX-License-Identifier: MIT

#include "safuCheckBase64Encoding_utest.h"

int safuTestSafuCheckBase64EncodingSuccessStringEncodedSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuCheckBase64EncodingSuccessStringEncodedTeardown(UNUSED void **state) {
    return 0;
}

void safuTestSafuCheckBase64EncodingSuccessStringEncoded(UNUSED void **state) {
    const char *testStrings[] = {
        "U2VyaW91cyBpbnNpZGUgZWxzZSBtZW1vcnkgaWYgc2l4LiBXaG9zZSBncm91cCB0aHJvdWdoIGRlc3BpdGUgY2F1c2Uu",
        "VG90YWwgZmluYW5jaWFsIHJvbGUgdG9nZXRoZXIgcmFuZ2UgbGluZSBiZXlvbmQgaXRzLg==",
        "UmVzdCBodW1hbiBzdGF0aW9uIHByb3BlcnR5LiBQYXJ0bmVyIHN0b2NrIGZvdXIu",
        "TGFuZ3VhZ2UgYmFsbCBmbG9vciBtZWV0IHVzdWFsbHkgYm9hcmQgbmVjZXNzYXJ5LiBOYXR1cmFsIHNwb3J0IG11c2ljIHdoaXRlLg==",
        "UGFydHkgcHJldmVudCBsaXZlLiBRdWlja2x5IGNhbmRpZGF0ZSBjaGFuZ2UgYWx0aG91Z2gu"};

    safuResultE_t result = SAFU_RESULT_FAILED;

    TEST("safuCheckBase64Encoding");
    SHOULD("%s", "return SAFU_RESULT_OK since data is valid");

    for (size_t i = 0; i < ARRAY_SIZE(testStrings); i++) {
        result = safuCheckBase64Encoding(testStrings[i], strlen(testStrings[i]));
        assert_int_equal(result, SAFU_RESULT_OK);
    }
}
