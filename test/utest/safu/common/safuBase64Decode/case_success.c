// SPDX-License-Identifier: MIT

#include <string.h>

#include "safuBase64Decode_utest.h"

int safuTestSafuBase64DecodeSuccessStringDecodedSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuBase64DecodeSuccessStringDecodedTeardown(UNUSED void **state) {
    return 0;
}

void safuTestSafuBase64DecodeSuccessStringDecoded(UNUSED void **state) {
    const char *testStrings[] = {
        "U2VyaW91cyBpbnNpZGUgZWxzZSBtZW1vcnkgaWYgc2l4LiBXaG9zZSBncm91cCB0aHJvdWdoIGRlc3BpdGUgY2F1c2Uu",
        "VG90YWwgZmluYW5jaWFsIHJvbGUgdG9nZXRoZXIgcmFuZ2UgbGluZSBiZXlvbmQgaXRzLg==",
        "UmVzdCBodW1hbiBzdGF0aW9uIHByb3BlcnR5LiBQYXJ0bmVyIHN0b2NrIGZvdXIu",
        "TGFuZ3VhZ2UgYmFsbCBmbG9vciBtZWV0IHVzdWFsbHkgYm9hcmQgbmVjZXNzYXJ5LiBOYXR1cmFsIHNwb3J0IG11c2ljIHdoaXRlLg==",
        "UGFydHkgcHJldmVudCBsaXZlLiBRdWlja2x5IGNhbmRpZGF0ZSBjaGFuZ2UgYWx0aG91Z2gu"};

    const char *testDecodedOutput[] = {"Serious inside else memory if six. Whose group through despite cause.",
                                       "Total financial role together range line beyond its.",
                                       "Rest human station property. Partner stock four.",
                                       "Language ball floor meet usually board necessary. Natural sport music white.",
                                       "Party prevent live. Quickly candidate change although."};

    unsigned char *testOutput = NULL;
    size_t testOutputLen = 0;
    safuResultE_t result = SAFU_RESULT_FAILED;

    TEST("safuBase64Decode");
    SHOULD("%s", "return SAFU_RESULT_OK and correctly decoded string");

    for (size_t i = 0; i < ARRAY_SIZE(testStrings); i++) {
        result = safuBase64Decode(testStrings[i], strlen(testStrings[i]), &testOutput, &testOutputLen);
        assert_int_equal(result, SAFU_RESULT_OK);
        assert_int_equal(testOutputLen, strlen(testDecodedOutput[i]));
        for (size_t j = 0; j < testOutputLen; j++) {
            assert_int_equal(testOutput[j], testDecodedOutput[i][j]);
        }
        free(testOutput);
    }
}
