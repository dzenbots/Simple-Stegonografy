
#ifndef BITMAP_INFO_HEADER_H
#define BITMAP_INFO_HEADER_H

#include "Types.h"
#include "Statuses.h"
#include <stdio.h>
#include <stdlib.h>

#define BIT_COUNT 0x18
#ifndef ERR
#define ERR(x) printf("%d\n", (x)); return x;
#endif

#pragma pack(push,1)

typedef struct {
    uint32 biSize;
    uint32 biWidth;
    uint32 biHeight;
    uint16 biPlanes;
    uint16 biBitCount;
    uint32 biCompression;
    uint32 biSizeImage;
    uint32 biXPelsPerMeter;
    uint32 biYPelsPerMeter;
    uint32 biClrUsed;
    uint32 biClrImportant;
} BitmapInfoHeader, *pBitmapInfoHeader;

#pragma pack(pop)

Status getBitmapInfoHeader(char* filename, pBitmapInfoHeader bih);

Status checkBitmapInfoHeader(pBitmapInfoHeader bih);

#endif
