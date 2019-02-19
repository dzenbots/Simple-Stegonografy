
#ifndef SECRETHIDER_H
#define SECRETHIDER_H

#include "Statuses.h"
#include "Types.h"
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push,1)
typedef struct {
    byte R;
    byte G;
    byte B;
} BMPColor, *pBMPColor;
#pragma pack(pop)

Status hideInfo(FILE* bmpinputFile, FILE* bmpoutputFile, byte* secretBuffer, uint32 secretSize, uint32 sizeImage);

Status extractInfo(FILE* bmpinputFile, FILE* outputfile);

#endif
