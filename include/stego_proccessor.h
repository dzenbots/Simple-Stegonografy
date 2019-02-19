#ifndef STEGO_PROCCESSOR_H
#define STEGO_PROCCESSOR_H

#include "Statuses.h"
#include "Types.h"
#include "bmpHeader.h"
#include "bitmapInfoHeader.h"

#define MODE_PACK 1
#define MODE_UNPACK 2

#define PIXELS_TO_BYTES(x) (((x)/3)/8)

Status stego_proccess(char* bmpFileName, char*targetFileName, char* outFileName, uint32 mode);

#endif