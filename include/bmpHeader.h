
#ifndef BMP_HEADER_H
#define BMP_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include "Statuses.h"
#include "Types.h"

#define BMP_HEADER_MAGIC 0x4D42
#define BMP_HEADER_NULL 0x0
#ifndef ERR
#define ERR(x) printf("%d\n", (x)); return x;
#endif
//make this struct correct in memory
#pragma pack(push, 1)

//BMP file header structure
typedef struct {
    uint16 bfType;
    uint32 bfSize;
    uint32 bfReserved;
    uint32 bfOffBits;
} BMPHeader, *pBMPHeader;
#pragma pack(pop)

Status checkBMPFileHeader(pBMPHeader BmpHeader);

Status getBMPHeader(char* filename, pBMPHeader BmpHeader);

#endif