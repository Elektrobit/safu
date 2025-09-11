// SPDX-License-Identifier: MIT

#include <stdio.h>

#include "safuBase64Encode_utest.h"

int safuTestSafuBase64EncodeSuccessStringEncodedSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuBase64EncodeSuccessStringEncodedTeardown(UNUSED void **state) {
    return 0;
}

void safuTestSafuBase64EncodeSuccessStringEncoded(UNUSED void **state) {
    const char *testStrings[] = {"Serious inside else memory if six. Whose group through despite cause.",
                                 "Total financial role together range line beyond its.",
                                 "Rest human station property. Partner stock four.",
                                 "Language ball floor meet usually board necessary. Natural sport music white.",
                                 "Party prevent live. Quickly candidate change although."};

    char *testEncodedOutput[] = {
        "U2VyaW91cyBpbnNpZGUgZWxzZSBtZW1vcnkgaWYgc2l4LiBXaG9zZSBncm91cCB0aHJvdWdoIGRlc3BpdGUgY2F1c2Uu",
        "VG90YWwgZmluYW5jaWFsIHJvbGUgdG9nZXRoZXIgcmFuZ2UgbGluZSBiZXlvbmQgaXRzLg==",
        "UmVzdCBodW1hbiBzdGF0aW9uIHByb3BlcnR5LiBQYXJ0bmVyIHN0b2NrIGZvdXIu",
        "TGFuZ3VhZ2UgYmFsbCBmbG9vciBtZWV0IHVzdWFsbHkgYm9hcmQgbmVjZXNzYXJ5LiBOYXR1cmFsIHNwb3J0IG11c2ljIHdoaXRlLg==",
        "UGFydHkgcHJldmVudCBsaXZlLiBRdWlja2x5IGNhbmRpZGF0ZSBjaGFuZ2UgYWx0aG91Z2gu"};

    char *testOutput = NULL;
    size_t testOutputLen = 0;
    safuResultE_t result = SAFU_RESULT_FAILED;

    TEST("safuBase64Encode");
    SHOULD("%s", "return SAFU_RESULT_OK and correctly encoded string");

    for (size_t i = 0; i < ARRAY_SIZE(testStrings); i++) {
        result = safuBase64Encode(testStrings[i], strlen(testStrings[i]), &testOutput, &testOutputLen);
        assert_int_equal(result, SAFU_RESULT_OK);
        assert_string_equal(testOutput, testEncodedOutput[i]);
        free(testOutput);
    }
}
