// SPDX-License-Identifier: MIT
#pragma once

#define SEXTET_0(byte0)        ((byte0) >> 2)
#define SEXTET_1(byte0, byte1) (((0x3 & (byte0)) << 4) | ((byte1) >> 4))
#define SEXTET_2(byte1, byte2) (((0xf & (byte1)) << 2) | ((byte2) >> 6))
#define SEXTET_3(byte2)        (0x3f & (byte2))
