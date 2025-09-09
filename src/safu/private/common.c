// SPDX-License-Identifier: MIT
#include "safu/common.h"

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <safu/result.h>
#include <safu/types.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "safu/log.h"

static const char *safuB64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const unsigned char safuB64Decode[] = {
    0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0,  0,  0,  0,  62, 0,  0,  0,  63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
    0,  0,  0,  0,  0,  0,  0,  0, 1, 2, 3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
    22, 23, 24, 25, 0,  0,  0,  0, 0, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
    45, 46, 47, 48, 49, 50, 51, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
};

safuResultE_t safuStringIsEmpty(const char *stringToCheck) {
    safuResultE_t retval = SAFU_RESULT_OK;

    if (stringToCheck != NULL) {
        for (size_t i = 0; stringToCheck[i] != 0; i++) {
            if (isspace(stringToCheck[i]) == 0) {
                retval = SAFU_RESULT_FAILED;
                break;
            }
        }
    }
    return retval;
}

void *safuAllocMem(void *oldptr, size_t newlen) {
    void *newptr = NULL;

    if (oldptr && newlen == 0) {
        /*
         * IMHO the POSIX standard is ambiguous about the behavior wrt the
         * old memory when newlen is 0 and realloc returns NULL
         */
        free(oldptr);
    } else {
        newptr = realloc(oldptr, newlen);
        if (newptr == NULL && newlen > 0) {
            safuLogErrErrno("realloc");
            free(oldptr);
        }
    }
    return newptr;
}

safuResultE_t safuBase64Encode(const void *inputData, size_t ilen, char **output, size_t *olen) {
    safuResultE_t status = SAFU_RESULT_OK;
    char *buffer = NULL;

    if (inputData == NULL || ilen == 0) {
        safuLogErr("invalid parameter");
        status = SAFU_RESULT_FAILED;
    } else {
        const unsigned char *input = inputData;
        // if (ilen%3) == 2 -> padding is 1; == 1 -> padding 2; == 0 -> padding 0.
        size_t padding = (((ilen % 3) & 1) << 1) + (((ilen % 3) & 2) >> 1);

        *olen = 4 * (ilen + padding) / 3;

        buffer = safuAllocMem(NULL, *olen + 1);
        if (buffer == NULL) {
            status = SAFU_RESULT_FAILED;
        } else {
            size_t i = 0, j;
            for (j = 0; j <= ilen - 3; j += 3) {
                buffer[i++] = safuB64[SEXTET_0(input[j])];
                buffer[i++] = safuB64[SEXTET_1(input[j], input[j + 1])];
                buffer[i++] = safuB64[SEXTET_2(input[j + 1], input[j + 2])];
                buffer[i++] = safuB64[SEXTET_3(input[j + 2])];
            }
            if (padding == 1) {
                buffer[i++] = safuB64[SEXTET_0(input[j])];
                buffer[i++] = safuB64[SEXTET_1(input[j], input[j + 1])];
                buffer[i++] = safuB64[((0xf & input[j + 1]) << 2)];
                buffer[i++] = '=';
            } else if (padding == 2) {
                buffer[i++] = safuB64[SEXTET_0(input[j])];
                buffer[i++] = safuB64[((0x3 & input[j]) << 4)];
                buffer[i++] = '=';
                buffer[i++] = '=';
            }
            buffer[i] = '\0';
            *output = buffer;
        }
    }
    return status;
}

safuResultE_t safuCheckBase64Encoding(const char *input, size_t ilen) {
    safuResultE_t status = SAFU_RESULT_OK;

    if ((ilen == 0) || (ilen % 4)) {
        status = SAFU_RESULT_FAILED;
    } else {
        size_t i = 0;

        for (; i < ilen - 2; i++) {
            if (strchr(safuB64, input[i]) == NULL) {
                status = SAFU_RESULT_FAILED;
                break;
            }
        }
        if (status == SAFU_RESULT_OK) {
            if (input[i] == '=') {
                if (input[i + 1] != '=') {
                    status = SAFU_RESULT_FAILED;
                }
            } else if (strchr(safuB64, input[i]) == NULL) {
                status = SAFU_RESULT_FAILED;
            }
        }
        if (status == SAFU_RESULT_OK) {
            i++;
            if ((input[i] != '=') && (strchr(safuB64, input[i]) == NULL)) {
                status = SAFU_RESULT_FAILED;
            }
        }
    }

    return status;
}

safuResultE_t safuBase64Decode(const char *input, size_t ilen, unsigned char **output, size_t *olen) {
    safuResultE_t status = SAFU_RESULT_OK;
    unsigned char *buffer = NULL;

    if (input == NULL || ilen == 0) {
        safuLogErr("invalid parameter");
        status = SAFU_RESULT_FAILED;
    } else {
        status = safuCheckBase64Encoding(input, ilen);
        if (status == SAFU_RESULT_OK) {
            const unsigned char *safeInput = (const unsigned char *)input;
            size_t padding = 0;
            if (ilen > 1) {
                if (safeInput[ilen - 1] == '=') ++padding;
                if (safeInput[ilen - 2] == '=') ++padding;
            }
            *olen = (3 * (ilen / 4)) - padding;
            if (*olen != 0) {
                buffer = safuAllocMem(NULL, *olen);
                if (buffer == NULL) {
                    status = SAFU_RESULT_FAILED;
                } else {
                    size_t i = 0, j;
                    for (j = 0; j <= ilen - 4 - padding; j += 4) {
                        int chunkA = safuB64Decode[safeInput[j]];
                        int chunkB = safuB64Decode[safeInput[j + 1]];
                        int chunkC = safuB64Decode[safeInput[j + 2]];
                        int chunkD = safuB64Decode[safeInput[j + 3]];

                        buffer[i++] = (chunkA << 2) | (chunkB >> 4);
                        buffer[i++] = (chunkB << 4) | (chunkC >> 2);
                        buffer[i++] = (chunkC << 6) | (chunkD);
                    }
                    if (!(ilen % 4)) {
                        if (padding == 1) {
                            int chunkA = safuB64Decode[safeInput[j]];
                            int chunkB = safuB64Decode[safeInput[j + 1]];
                            int chunkC = safuB64Decode[safeInput[j + 2]];

                            buffer[i++] = (chunkA << 2) | (chunkB >> 4);
                            buffer[i++] = (chunkB << 4) | (chunkC >> 2);
                        } else if (padding == 2) {
                            int chunkA = safuB64Decode[safeInput[j]];
                            int chunkB = safuB64Decode[safeInput[j + 1]];

                            buffer[i++] = (chunkA << 2) | (chunkB >> 4);
                        }
                    }
                    *output = buffer;
                }
            }
        }
    }

    return status;
}

safuResultE_t safuTransferExactly(int fd, void *buf, size_t len, int flags,
                                  ssize_t (*transferFunc)(int, void *, size_t, int), size_t *transferred) {
    safuResultE_t status = SAFU_RESULT_OK;
    size_t initialLen = len;

    if ((fd < 0) || (buf == NULL) || (len < 1) || (transferred == NULL)) {
        status = SAFU_RESULT_FAILED;
    } else {
        char *msgBuffer = buf;
        *transferred = 0;

        while (*transferred < initialLen) {
            int bytes;
            bytes = transferFunc(fd, &msgBuffer[*transferred], len, flags);
            if (bytes < 0) {
                switch (errno) {
                    case EINTR:
                    case EAGAIN:
// POSIX.1-2001 allows either EAGAIN or EWOULDBLOCK to be returned on blocking socket,
// which might have the same value on some platforms.
#if EAGAIN != EWOULDBLOCK
                    case EWOULDBLOCK:
#endif
                        continue;
                    default:
                        status = SAFU_RESULT_FAILED;
                        break;
                }
            } else if (bytes == 0) {
                status = SAFU_RESULT_CLOSED;
                break;
            }

            if (status != SAFU_RESULT_OK) {
                break;
            } else {
                len -= bytes;
                *transferred += bytes;
            }
        }
    }
    return status;
}

// Find a way to avoid duplicated code
ssize_t safuReadExactly(int fd, void *buf, size_t len) {
    ssize_t status;
    size_t initialLen = len;

    if ((fd < 0) || (buf == NULL) || (len < 1)) {
        errno = EINVAL;
        status = -1;
    } else {
        size_t bytesTransferred = 0;
        char *msgBuffer = buf;

        while (bytesTransferred < initialLen) {
            int bytes;
            bytes = read(fd, &msgBuffer[bytesTransferred], len);
            if (bytes < 0) {
                switch (errno) {
                    case EINTR:
                    case EAGAIN:
                        continue;
                    default:
                        break;
                }
            } else if (bytes == 0) {
                break;
            }
            len -= bytes;
            bytesTransferred += bytes;
        }
        status = bytesTransferred;
    }
    return status;
}

ssize_t safuWriteExactly(int fd, const void *buf, size_t len) {
    ssize_t status;
    size_t initialLen = len;

    if ((fd < 0) || (buf == NULL) || (len < 1)) {
        errno = EINVAL;
        status = -1;
    } else {
        size_t bytesTransferred = 0;
        const char *msgBuffer = buf;

        while (bytesTransferred < initialLen) {
            int bytes;
            bytes = write(fd, &msgBuffer[bytesTransferred], len);
            if (bytes < 0) {
                switch (errno) {
                    case EINTR:
                    case EAGAIN:
                        continue;
                    default:
                        break;
                }
            } else if (bytes == 0) {
                break;
            }
            len -= bytes;
            bytesTransferred += bytes;
        }
        status = bytesTransferred;
    }
    return status;
}

safuResultE_t safuRecvExactly(int fd, void *buf, size_t len, size_t *transferred) {
    return safuTransferExactly(fd, buf, len, 0, recv, transferred);
}

safuResultE_t safuSendExactly(int fd, const void *buf, size_t len, size_t *transferred) {
    // We ensure by tests and guarantee that transferExactly will not modify buf
    return safuTransferExactly(fd, (void *)buf, len, MSG_NOSIGNAL, (safuTransferFunc_t *)send, transferred);
}

ssize_t safuGetFileSize(int fd) {
    struct stat fdStat;
    ssize_t result = -1;

    if (fd < 0) {
        safuLogErr("invalid parameter");
    } else {
        result = fstat(fd, &fdStat);
        if (result < 0) {
            safuLogErrErrno("fstat failed");
        } else if (S_ISREG(fdStat.st_mode) == 0) {
            safuLogErr("S_ISREG failed");
        } else {
            result = fdStat.st_size;
        }
    }

    return result;
}

ssize_t safuReadFileToString(const char *fileName, ssize_t maxLength, char **string) {
    char *buffer = NULL;
    off_t size = 0;
    ssize_t result = 0;
    int fd = -1;

    if ((fileName == NULL) || (maxLength == 0) || (maxLength < -1) || (string == NULL)) {
        safuLogErr("invalid parameter");
        result = -1;
    }

    if (result == 0) {
        fd = open(fileName, O_RDONLY);
        if (fd < 0) {
            safuLogErrErrno("open");
            result = -1;
        }
    }

    size = safuGetFileSize(fd);
    if (size < 0) {
        safuLogErr("safuGetFileSize failed");
        result = -1;
    } else if (size == 0) {
        safuLogErr("file is empty");
        result = -1;
    } else if ((maxLength > 0) && (size > maxLength)) {
        safuLogErrF("file is bigger (%ld) than the specified maximum length (%ld)", size, maxLength);
        result = -1;
    }

    if (result == 0) {
        buffer = safuAllocMem(NULL, size + 1);
        if (buffer == NULL) {
            safuLogErr("safuAllocMem failed");
            result = -1;
        }
    }

    if (result == 0) {
        result = safuReadExactly(fd, buffer, size);
        if (result < 0) {
            safuLogErrErrno("safuRecvExactly failed");
            result = -1;
        } else if (result != size) {
            safuLogErrF("safuRecvExactly incomplete (%ld of %ld bytes)", result, size);
            result = -1;
        } else {
            buffer[size] = '\0';
        }
    }

    if (fd >= 0) {
        int retval;
        retval = close(fd);
        if (retval < 0) {
            safuLogWarnF("close failed - %s", strerror(errno));
            result = -1;
        }
    }

    if (result < 0) {
        free(buffer);
    } else {
        *string = buffer;
        result = size;
    }

    return result;
}

const char *safuGetHardwareId(void) {
    static char hardwareIdString[SAFU_HARDWAREID_MAX_LENGTH];
    static bool initialized = false;
    const ssize_t maxLength = SAFU_HARDWAREID_MAX_LENGTH - 1;
    const ssize_t minLength = 1;

    if (initialized == false) {
        char *hardwareIdFile;
        char *envValue;
        char *buffer = NULL;
        bool useCache = true;
        ssize_t bytes;

        // These getenv() calls are a temporary solution until safu_config_t is implemented,
        // which will come with an ability to ignore environment variables completely

        envValue = getenv(SAFU_HARDWAREID_ENVIRONMENT_PREFIX "CACHE");
        if ((envValue != NULL) && (strncmp(envValue, "0", 2) == 0)) {
            useCache = false;
        }

        envValue = getenv(SAFU_HARDWAREID_ENVIRONMENT_PREFIX "FILE");
        if ((envValue == NULL) || (strlen(envValue) == 0)) {
            hardwareIdFile = SAFU_HARDWAREID_FILE;
        } else {
            hardwareIdFile = envValue;
        }

        bytes = safuReadFileToString(hardwareIdFile, maxLength, &buffer);
        if (bytes < minLength) {
            if (bytes < 0) {
                safuLogErrF("safuReadFileToString failed, using default value '%s' (file: '%s')",
                            SAFU_HARDWAREID_DEFAULT_VALUE, hardwareIdFile);
            } else {
                safuLogErrF("hardwareId too short (%ld), using default value '%s' (file: '%s')", bytes,
                            SAFU_HARDWAREID_DEFAULT_VALUE, hardwareIdFile);
            }
            strcpy(hardwareIdString, SAFU_HARDWAREID_DEFAULT_VALUE);
        } else {
            int i = 0;
            while (i < bytes) {
                // Get rid of unwanted characters, like the LF at the end of the file
                switch (buffer[i]) {
                    case '\r':
                    case '\n':
                        buffer[i] = 0;
                        break;
                    case '\0':
                        i = bytes;
                        break;
                    default:
                        break;
                }
                i += 1;
            }
            strncpy(hardwareIdString, buffer, bytes);
            hardwareIdString[bytes] = '\0';
        }

        free(buffer);

        if (useCache == true) {
            initialized = true;
        }
    }

    return hardwareIdString;
}

const char *safuGetEnvOr(const char *key, const char *defaultValue) {
    const char *envValue = defaultValue;
    if (key != NULL) {
        envValue = getenv(key);
        if (envValue == NULL) {
            envValue = defaultValue;
        }
    }
    return envValue;
}
